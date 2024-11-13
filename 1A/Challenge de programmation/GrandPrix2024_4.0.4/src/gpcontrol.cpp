/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include "gpcontrol.h"
#include <QFile>
#include <QMessageBox>
#include <QProcess>
#include <QtDebug>
#include <QtGlobal>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include "logger.h"

void line(int x1, int y1, int x2, int y2, infoLine * data)
{
  data->posStart.x = x1;
  data->posStart.y = y1;
  data->posActual.x = x1 + 0.5f;
  data->posActual.y = y1 + 0.5f;
  data->posEnd.x = x2;
  data->posEnd.y = y2;
  int adxi, adyi, dxi, dyi;
  adxi = dxi = x2 - x1;
  adyi = dyi = y2 - y1;
  if (adxi < 0)
    adxi = -dxi;
  if (adyi < 0)
    adyi = -dyi;
  data->pos = 0;
  data->len = adxi;
  if (adyi > adxi)
    data->len = adyi;
  data->delta.x = ((float)dxi) / data->len;
  data->delta.y = ((float)dyi) / data->len;
}

int nextPoint(infoLine * data, Pos2Dint * point, int sens)
{
  if (sens > 0) {
    if (data->pos == data->len) {
      point->x = data->posEnd.x;
      point->y = data->posEnd.y;
      return -1; // La fin de la ligne est atteinte
    }
    data->posActual.x += data->delta.x;
    data->posActual.y += data->delta.y;
    point->x = ((int)data->posActual.x);
    point->y = ((int)data->posActual.y);
    data->pos++;
    return 1; // un nouveau point est déterminé.
  }
  if (sens < 0) {
    if (data->pos == 0) {
      point->x = data->posStart.x;
      point->y = data->posStart.y;
      return -1; // La fin de la ligne est atteinte
    }
    data->posActual.x -= data->delta.x;
    data->posActual.y -= data->delta.y;
    point->x = ((int)data->posActual.x);
    point->y = ((int)data->posActual.y);
    data->pos--;

    return 1; // un nouveau point est déterminé.
  }
  return 1; // Avec sens==0, il n'y a pas de déplacement
}

GPControl::GPControl(QObject * parent) : QObject(parent), tiles(QVector<GPControl::Tile>()), cars(QVector<Car>(3)), nextCarMode(RANDOM), nbCars(0), delay(1)
{
  QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
  finishPosition = 1;
  currentCarIndex = 0;
  _driverEnabled[0] = true;
  _driverEnabled[1] = true;
  _driverEnabled[2] = true;
  _carSequence[0] = 0;
  _carSequence[1] = 1;
  _carSequence[2] = 2;
  _steps = -1;
}

GPControl::~GPControl()
{
  timer.stop();
}

bool GPControl::driverEnabled(int car) const
{
  return _driverEnabled[car];
}

bool GPControl::driverDisabled(int car) const
{
  return not _driverEnabled[car];
}

void GPControl::disableDriver(int car)
{
  _driverEnabled[car] = false;
}

void GPControl::enableDriver(int car)
{
  _driverEnabled[car] = true;
}

void GPControl::closeCarStderr(int noCar)
{
  if (_logFiles[noCar] && _logFiles[noCar]->isOpen()) {
    _logFiles[noCar]->close();
  }
  _logFiles[noCar].reset();
}

bool GPControl::setMap(const QString & mapPath)
{
  QFile file(mapPath);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return false;
  }
  QTextStream stream(&file);
  stream >> this->sizeX >> this->sizeY >> this->gasLevelAtStart;

  tiles.clear();
  tiles.reserve(sizeX * sizeY);
  nbCars = 0;
  currentCarIndex = 0;
  /* Pour vérification de la bonne lecture du carburant de départ */
  /* std::cerr << "Carburant de départ : " << this->carburantAuDepart <<
   * std::endl; */

  int x = 0;
  int y = 0;
  while (!stream.atEnd()) {
    bool ignoreCh = false;
    char ch;
    stream >> ch;
    switch (ch) {
    case GPControl::START1_CHAR:
      cars[0].reset(x, y, nbrMaxBoost, 1, QColor(Qt::red));
      cars[0].fillTank(this->gasLevelAtStart);
      nbCars++;
      tiles.append(GPControl::NORMAL);
      break;
    case GPControl::START2_CHAR:
      cars[1].reset(x, y, nbrMaxBoost, 2, QColor(0, 200, 0, 255));
      cars[1].fillTank(this->gasLevelAtStart);
      nbCars++;
      tiles.append(GPControl::NORMAL);
      break;
    case GPControl::START3_CHAR:
      cars[2].reset(x, y, nbrMaxBoost, 3, QColor(Qt::blue));
      cars[2].fillTank(this->gasLevelAtStart);
      nbCars++;
      tiles.append(GPControl::NORMAL);
      break;
    case GPControl::NORMAL_CHAR:
      tiles.append(GPControl::NORMAL);
      break;
    case GPControl::OUT_CHAR:
      tiles.append(GPControl::OUT);
      break;
    case GPControl::SAND_CHAR:
      tiles.append(GPControl::SAND);
      break;
    case GPControl::GOAL_CHAR:
      tiles.append(GPControl::GOAL);
      break;
    default:
      ignoreCh = true;
    }
    // qWarning("%i", ignoreCh);
    if (!ignoreCh) {
      x++;
      if (x == this->sizeX) {
        y++;
        x = 0;
      }
    }
  }
  file.close();
  if (tiles.size() != sizeX * sizeY) {
    tiles.clear();
    return false;
  } else {
    return true;
  }
}

int GPControl::getSizeX()
{
  return sizeX;
}
int GPControl::getSizeY()
{
  return sizeY;
}

GPControl::Tile GPControl::getTile(Position position) const
{
  if (position.x() >= 0 && position.x() < sizeX && position.y() >= 0 && position.y() < sizeY) {
    return tiles.at(position.x() + position.y() * sizeX);
  } else {
    return GPControl::OUT;
  }
}

char GPControl::getTileChar(int x, int y)
{
  if (x >= 0 && x < sizeX && y >= 0 && y < sizeY) {
    switch (tiles.at(x + y * sizeX)) {
    case GPControl::OUT:
      return GPControl::OUT_CHAR;
    case GPControl::NORMAL:
      return GPControl::NORMAL_CHAR;
    case GPControl::SAND:
      return GPControl::SAND_CHAR;
    case GPControl::GOAL:
      return GPControl::GOAL_CHAR;
    default:
      return GPControl::OUT_CHAR;
    }
  } else {
    return GPControl::OUT_CHAR;
  }
}

int GPControl::getNbCars()
{
  return nbCars;
}

const QList<Position> & GPControl::getCarPositions(int car) const
{
  return cars[car].positions;
}

const QList<Position> & GPControl::getCarAccRequests(int car) const
{
  return cars[car].accelerationRequests;
}

const QList<int> & GPControl::getCarGasLevels(int car) const
{
  return cars[car].gasLevels;
}

Position GPControl::getCarPosition(int noCar) const
{
  return cars[noCar].positions.last();
}

Acceleration GPControl::getCarLastAccelerationRequest(int noCar) const
{
  return cars[noCar].lastAccelerationRequest;
}

Speed GPControl::getCarSpeed(int noCar) const
{
  return cars[noCar].speed;
}

int GPControl::getCarburant(int noCar)
{
  return cars[noCar].gasLevel;
}

Position GPControl::getOldCarPosition(int noCar, int numPos) const
{
  return cars[noCar].positions.at(numPos);
}

int GPControl::getBoost(int noCar)
{
  return cars[noCar].boostLevel;
  ;
}
int GPControl::getNbBoostUsed(int noCar)
{
  return cars[noCar].boostUsage.size();
}
int GPControl::getIndexBoostUsed(int noCar, int numBoost)
{
  return cars[noCar].boostUsage.at(numBoost);
}
int GPControl::getNbMoves(int noCar)
{
  return cars[noCar].moveCount;
}
int GPControl::getNbFailures(int noCar)
{
  return cars[noCar].failureCount;
}
int GPControl::getNbPositions(int noCar)
{
  return cars[noCar].positions.size();
}
int GPControl::startPosition(int noCar)
{
  return cars[noCar].startPosition;
}
QColor GPControl::getColor(int noCar)
{
  return cars[noCar].color;
}
int GPControl::getCurrentCar()
{
  return currentCarIndex;
}
void GPControl::setCarDebug(int car, bool debug)
{
  cars[car].debug = debug;
}
bool GPControl::getCarDebug(int car)
{
  return cars[car].debug;
}
QString GPControl::getDriverName(int car)
{
  return cars[car].name;
}

void GPControl::startDriver(int noCar, const QString & driverPath)
{
  // drivers[noCar].setReadChannel(QProcess::StandardOutput|QProcess::StandardError);
  // qWarning() << "Starting driver : " <<driverPath;

  if (driverPath.isEmpty()) {
    QFile(logFilename(noCar)).remove();
    cars[noCar].name = "";
    disableDriver(noCar);
    return;
  }
  enableDriver(noCar);

  closeCarStderr(noCar);
  _logFiles[noCar] = std::make_shared<QFile>(logFilename(noCar));
  _logFiles[noCar]->open(QFile::WriteOnly | QFile::Truncate | QFile::Text | QFile::Unbuffered);

  cars[noCar].name = driverPath.split("/").last();
  QProcess * driver = cars[noCar].driver;

  QObject::connect(driver, &QProcess::readyReadStandardError, this, //
                   [this, noCar] {                                  //
                     onReadyReadStandardError(noCar);
                   });
  connect(driver,                                                                    //
          QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),             //
          [noCar, this](int /* exitCode */, QProcess::ExitStatus /* exitStatus */) { //
            disableDriver(noCar);
            closeCarStderr(noCar);
            emit driverStopped(noCar);
          });

#if (QT_VERSION > QT_VERSION_CHECK(5, 5, 0))
  connect(driver,                                                  //
          &QProcess::errorOccurred,                                //
          [this, noCar](QProcess::ProcessError /* exitStatus */) { //
            disableDriver(noCar);
            closeCarStderr(noCar);
            emit driverCrashed(noCar);
          });
#else
  connect(driver,                                                                    //
          static_cast<void (QProcess::*)(QProcess::ProcessError)>(&QProcess::error), //
          [this, noCar](QProcess::ProcessError /* exitStatus */) {                   //
            disableDriver(noCar);
            closeCarStderr(noCar);
            emit driverCrashed(noCar);
          });
#endif

  driver->start(driverPath, QStringList(), QIODevice::Unbuffered | QIODevice::Text | QIODevice::ReadWrite);
  driver->waitForStarted();
  driver->write(mapData());
}

void GPControl::setDelay(int value)
{
  delay = value;
}

QByteArray GPControl::mapData()
{ /* indique également le carburant de départ
     en plus de la taille de la carte */
  QByteArray res;
  res.append(QString("%1 %2 %3\n").arg(sizeX).arg(sizeY).arg(gasLevelAtStart).toLocal8Bit());
  for (int y = 0; y < sizeY; y++) {
    for (int x = 0; x < sizeX; x++) {
      res.append(getTileChar(x, y));
    }
    res.append("\n");
  }

  return res;
}

QByteArray GPControl::positionsData()
{
  QByteArray res;
  for (int i = 0; i < nbCars; i++) {
    Car & car = cars[(currentCarIndex + i) % nbCars];
    res.append(QString("%1 %2").arg(car.positions.last().x()).arg(car.positions.last().y()).toLocal8Bit());
    if (i != nbCars - 1) {
      res.append("\t");
    }
  }
  res.append("\n");
  return res;
}

int GPControl::gasolineAtStart() const
{
  return gasLevelAtStart;
}

void GPControl::nextMove()
{
  if (!_started) {
    _started = true;
  }
  Car & car = cars[currentCarIndex];
  if (!car.previousTimeout) {
    // qWarning() << "GDC WRITES TO car " << (currentCarIndex + 1) << positionsData();
    car.driver->write(positionsData());
  }
  if (car.driver->bytesAvailable() >= 4) {
    QTimer::singleShot(0, this, SLOT(readyReadStandardOutput()));
  } else {
    QObject::connect(car.driver, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    timer.start(1000);
  }
  ++car.moveCount;
}

void GPControl::setSteps(int steps)
{
  _steps = steps;
}

int GPControl::gasolineConsumption(Acceleration acceleration, Speed speed)
{
  return acceleration.x() * acceleration.x() + acceleration.y() * acceleration.y() //
         + (int)(sqrt(speed.x() * speed.x() + speed.y() * speed.y()) * 3.0 / 2.0);
}

QString GPControl::logFilename(int noCar)
{
  return QString("stderr_driver_%1.txt").arg(noCar + 1);
}

bool GPControl::started() const
{
  return _started;
}

int GPControl::enabledDrivers() const
{
  return driverEnabled(0) + driverEnabled(1) + driverEnabled(2);
}

void GPControl::setFirstCar()
{
  currentCarIndex = 0;
  _positionInCarSequence = 0;
  nextCar();
}

void GPControl::moveCurrentCar(Acceleration acceleration)
{
  Car & car = cars[currentCarIndex];

  car.lastAccelerationRequest = acceleration;

  if (Logger::enabled()) {
    car.accelerationRequests.push_back(acceleration);
    car.gasLevels.push_back(car.gasLevel);
  }

  /* Attention, il y a consommation meme si le mouvement n'est pas autorisé */
  int gasUsed = gasolineConsumption(acceleration, car.speed);
  if (getTile(car.positions.last()) == GPControl::SAND) {
    gasUsed += 1;
  }
  car.useGasoline(gasUsed);
  /* Pour la verification de la bonne consomation du carburant */
  /* std::cerr << "Voiture : " << currentCarIndex << ", carburant :  " <<
   * car.carburant << " (" << deltaCarburant << ") " << std::endl; */

  // && noCollision(currentCarIndex, accX, accY)
  if (availableAccelerations(currentCarIndex).contains(acceleration) && noCollision(currentCarIndex, acceleration) && (car.gasLevel > 0)) {
    car.positions.append(car.positions.last());
    car.speed += acceleration;
    car.positions.last() += car.speed;
    if (isABoost(acceleration)) {
      car.boostLevel--;
      car.boostUsage.append(car.positions.size() - 2);
      emit carMovedWithBoost(currentCarIndex);
    } else {
      emit carMoved(currentCarIndex);
    }

    // Set finish position if arrived at goal
    if ((getTile(car.positions.last()) == GPControl::GOAL) && car.finishPosition == 4) {
      car.finishPosition = finishPosition;
      ++finishPosition;
      if (finishPosition == 4) {
        finishPosition = 1;
      }
    }
  } else {
    // qWarning() << "Invalid move !" << availableMoves(currentCar);
    car.positions.append(car.positions.last());
    car.stop();
    if (car.gasLevel > 0) {
      car.failureCount++;
    }
    emit invalidMove(acceleration);
  }
}

bool GPControl::noCollision(int noCar, Acceleration acceleration)
{
  bool res = true;
  // printf("noCar= %d, accX = %d, accY= %d\n", noCar, accX, accY);
  Car & car = cars[noCar];
  Position pos0 = car.positions.last();
  Speed speed = car.speed;
  speed += acceleration;
  Position pos1 = pos0 + speed;
  infoLine vline;
  // printf("posX0= %d, posY0$= %d, posX1= %d, posY1$= %d\n", posX0, posY0,
  // posX1, posY1);
  line(pos0.x(), pos0.y(), pos1.x(), pos1.y(), &vline);
  Pos2Dint p;
  while (nextPoint(&vline, &p, +1) > 0) {
    if (p.x == pos0.x() && p.y == pos0.y()) {
      continue;
    }
    if (!isFree(Position(p.x, p.y))) {
      res = false;
      break;
    }
  }
  return res;
}

QSet<Acceleration> GPControl::availableAccelerations(int noCar) const
{
  QSet<Acceleration> result;
  const Car & car = cars[noCar];
  Position position = car.positions.last();
  Speed speed = car.speed;
  int maxAcc = 1;
  if (car.boostLevel > 0) {
    maxAcc = 2;
  }
  for (int accX = -maxAcc; accX <= maxAcc; accX++) {
    for (int accY = -maxAcc; accY <= maxAcc; accY++) {
      Acceleration acceleration(accX, accY);
      if (getTile(position) == GPControl::NORMAL) {
        if (isFree(position + speed + acceleration) && validSpeed(speed + acceleration)) {
          result.insert(acceleration);
        }
      } else if (getTile(position) == GPControl::SAND) {
        if (isFree(position + speed + acceleration) && validSpeedInSand(speed + acceleration)) {
          result.insert(acceleration);
        }
      }
    }
  }
  return result;
}

bool GPControl::isFree(Position position) const
{
  // Hors map
  if (position.x() < 0 || position.x() >= sizeX || position.y() < 0 || position.y() >= sizeY) {
    return false;
  }

  // Collision
  for (int i = 1; i < nbCars; i++) {
    const Car & car = cars[(currentCarIndex + i) % nbCars];
    if (car.positions.last() == position) {
      return false;
    }
  }

  // Hors-piste
  return getTile(position) != GPControl::OUT;
}

void GPControl::timeout()
{
  timer.stop();
  // qWarning() << "Driver " << currentCar << " timeout!";
  if (driverEnabled(currentCarIndex)) {
    emit driverTimeout();
  }
  Car & car = cars[currentCarIndex];
  car.previousTimeout = true;
  car.driver->disconnect(SIGNAL(readyReadStandardOutput()));
  if (!isAtEnd()) {
    nextCar();
    if (_steps > 0) {
      --_steps;
    }
    if (_steps) {
      QTimer::singleShot(delay * 20, this, &GPControl::nextMove);
    }
  } else {
    emit end(results());
  }
}

void GPControl::setNextCarMode(NextCarMode mode)
{
  this->nextCarMode = mode;
}

void GPControl::nextCar()
{
  Position position;
  if (nextCarMode == RANDOM) {
    // Generate a new sequence after 3 steps.
    if (!_positionInCarSequence) {
      _carSequence[0] = (int)(rand() % 3);
      do {
        _carSequence[1] = (int)(rand() % 3);
      } while (_carSequence[0] == _carSequence[1]);
      do {
        _carSequence[2] = (int)(rand() % 3);
      } while (_carSequence[0] == _carSequence[2] || _carSequence[1] == _carSequence[2]);
    }
    do {
      currentCarIndex = _carSequence[_positionInCarSequence];
      position = cars[currentCarIndex].positions.last();
      _positionInCarSequence = (_positionInCarSequence + 1) % 3;
    } while (getTile(position) == GPControl::GOAL || cars[currentCarIndex].isOutOfGas() || driverDisabled(currentCarIndex));
  } else if (nextCarMode == SEQUENTIAL) {
    do {
      currentCarIndex = (currentCarIndex + 1) % nbCars;
      position = cars[currentCarIndex].positions.last();
    } while (getTile(position) == GPControl::GOAL || cars[currentCarIndex].isOutOfGas() || driverDisabled(currentCarIndex));
  }
}

const QByteArray & GPControl::logArray(int car) const
{
  return _logArrays[car];
}

void GPControl::clearLogArray(int car)
{
  _logArrays[car].clear();
}

void GPControl::onReadyReadStandardError(int car)
{
  if (driverEnabled(car)) {
    QByteArray data = cars[car].driver->readAllStandardError();
    if (!data.isEmpty() && _logFiles[car]->isOpen()) {
      _logFiles[car]->write(data);
      _logArrays[car].append(data);
      emit newStderrData(car);
    }
  }
}

bool GPControl::isAtEnd() const
{
  for (int noCar = 0; noCar < nbCars; noCar++) {
    Position position = cars[noCar].positions.last();
    if ((getTile(position) != GPControl::GOAL) && (cars[noCar].gasLevel > 0) && driverEnabled(noCar)) {
      return false;
    }
  }
  return true;
}

void GPControl::readyReadStandardOutput()
{
  timer.stop();
  // qWarning() << "readyReadStandardOutput";
  Car & car = cars[currentCarIndex];
  car.driver->disconnect(SIGNAL(readyReadStandardOutput()));
  car.previousTimeout = false;

  QByteArray ligne = car.driver->readAllStandardOutput();
  // qInfo() << "GDC READS from car " << currentCarIndex << ligne;

  // qWarning() << "res:" << ligne;
  QList<QByteArray> list = ligne.trimmed().split(' ');

  Acceleration acceleration;
  bool syntax_error = false;

  if (list.size() >= 2) {
    bool ok;
    acceleration.rx() = list[0].toInt(&ok);
    if (ok) {
      acceleration.ry() = list[1].toInt(&ok);
      if (!ok) {
        // qWarning("accY not int");
        acceleration = Acceleration(0, 0);
        syntax_error = true;
      }
    } else {
      // qWarning("accX not int");
      acceleration = Acceleration(0, 0);
      syntax_error = true;
    }

  } else {
    // qWarning("syntax error");
    acceleration = Acceleration(0, 0);
    syntax_error = true;
  }
  if (syntax_error) {
    emit syntaxError();
  } else {
    moveCurrentCar(acceleration);
  }

  if (!isAtEnd()) {
    nextCar();
    if (_steps > 0) {
      --_steps;
    }
    if (_steps) {
      QTimer::singleShot(delay * 20, this, &GPControl::nextMove);
    }
  } else {
    emit end(results());
  }
}

bool carMovesComparator(const Car * c1, const Car * c2)
{
  return ((c1->finishPosition < c2->finishPosition) || //
          (c1->finishPosition == c2->finishPosition && c1->moveCount < c2->moveCount));
}

QString GPControl::results()
{
  QString res;
  QVector<Car *> sortedCars(nbCars);

  for (int i = 0; i < nbCars; i++) {
    sortedCars[i] = &cars[i];
  }
  std::sort(sortedCars.begin(), sortedCars.end(), carMovesComparator);

  for (int i = 0; i < nbCars; i++) {
    const Car & car = *(sortedCars[i]);
    res.append(tr("%1\t%2 (%3)\t%4\t%5\t%6\n").arg(i + 1).arg(car.name).arg(car.startPosition).arg(car.moveCount).arg(car.gasLevel).arg(car.boostLevel));
  }
  return res;
}

QString GPControl::csvResults()
{
  QString res;
  QVector<Car *> sortedCars(nbCars);
  for (int i = 0; i < nbCars; i++) {
    sortedCars[i] = &cars[i];
  }
  std::sort(sortedCars.begin(), sortedCars.end(), carMovesComparator);

  res = "FINISH";
  for (int i = 0; i < nbCars; i++) {
    const Car & car = *(sortedCars[i]);
    res.append(QString(";%1").arg(car.startPosition));
  }
  return res;
}
