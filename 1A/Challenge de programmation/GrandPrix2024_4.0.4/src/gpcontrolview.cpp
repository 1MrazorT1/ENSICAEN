/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include <QCryptographicHash>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include <QTime>
#include <QTimer>
#include <QtDebug>
#include <stdlib.h>

#include "car.h"
#include "finishdialog.h"
#include "gpcontrol.h"
#include "gpcontrolview.h"
#include "logger.h"
#include "ui_gpcontrolview.h"

GPControlView::GPControlView(QWidget * parent) : QWidget(parent), ui(new Ui::GPControlView), gpControl(nullptr)
{
  ui->setupUi(this);
  ui->tbStep->setToolTip("Go for 1 step");
  ui->tbTenSteps->setToolTip("Go for 10 steps");
  ui->pbRun->setToolTip("Launch full race");
  ui->tbStderr->setToolTip("Open/close standard error dialog");

  ui->delaySlider->setRange(0, 20);
  ui->delaySlider->setValue(20 - QSettings().value("Config/Speed", 2).toInt());

  QObject::connect(ui->gpMapSelector, SIGNAL(mapSelected(QString)), this, SLOT(on_gpMapSelector_mapSelected(QString)));
  for (int noCar = 0; noCar < 3; noCar++) {
    driverSelectorsLayout.addWidget(driverSelectors + noCar);
    driverSelectors[noCar].setNoCar(noCar);
    QObject::connect(&driverSelectors[noCar], SIGNAL(debugToggle(int, bool)), this, SLOT(gpDriverSelector_debugToggle(int, bool)));
    QObject::connect(&driverSelectors[noCar], SIGNAL(driverEnabled(int, bool)), this, SLOT(onDriverEnabled(int, bool)));
    QObject::connect(&driverSelectors[noCar], SIGNAL(driverEnabled(int, bool)), this, SIGNAL(driverEnableChanged()));
  }
  ui->driverGroupBox->setLayout(&driverSelectorsLayout);

  ui->cbFollow->addItem("All", GPControl::FollowAll);
  ui->cbFollow->addItem("Car 1", GPControl::FollowCar1);
  ui->cbFollow->addItem("Car 2", GPControl::FollowCar2);
  ui->cbFollow->addItem("Car 3", GPControl::FollowCar3);
  ui->cbFollow->setCurrentIndex(0);
  connect(ui->cbFollow, SIGNAL(currentIndexChanged(int)), this, SLOT(onFollowModeChanged(int)));

  ui->cbNextCarMode->addItem("Random", RANDOM);
  ui->cbNextCarMode->addItem("Sequential", SEQUENTIAL);
  ui->cbNextCarMode->setCurrentIndex(0);
  connect(ui->cbNextCarMode, SIGNAL(currentIndexChanged(int)), this, SLOT(onNextCarModeChanged(int)));

  newGPControl();
  enableControls();

  ui->tbStderr->setCheckable(true);
  connect(ui->tbStderr, SIGNAL(toggled(bool)), this, SLOT(onStdErrToggled(bool)));
  _stderrView = new StdErrView(nullptr);
  _stderrView->hide();

  connect(_stderrView, SIGNAL(aboutToClose()), this, SLOT(onStdErrClosed()));
  connect(ui->abortbutton, SIGNAL(clicked(bool)), this, SLOT(onAbortButtonClicked()));
  connect(ui->pbRun, &QPushButton::clicked, this, &GPControlView::onRunClicked);
  connect(ui->tbStep, &QPushButton::clicked, this, &GPControlView::onStepClicked);
  connect(ui->tbTenSteps, &QPushButton::clicked, this, &GPControlView::onTenStepsClicked);
  connect(ui->delaySlider, &QSlider::valueChanged, this, &GPControlView::onDelayChanged);

  if (!driverSelectors[0].hasPilots()) {
    QTimer::singleShot(1000, this, SLOT(showNoPilotMessage()));
  }
}

GPControlView::~GPControlView()
{
  delete _stderrView;
  delete ui;
}

int GPControlView::delay() const
{
  return ui->delaySlider->maximum() - ui->delaySlider->value();
}

void GPControlView::disableControls()
{
  ui->pbRun->setEnabled(false);
  ui->abortbutton->setEnabled(true);
  // ui->tbStderr->setEnabled(false);
  ui->gpMapSelector->enabledSelectionChange(false);
  for (int noCar = 0; noCar < 3; noCar++) {
    driverSelectors[noCar].setGuiEnabled(false);
  }
}

void GPControlView::enableControls()
{
  ui->abortbutton->setEnabled(false);
  ui->gpMapSelector->enabledSelectionChange(true);
  // ui->tbStderr->setEnabled(true);
  for (int noCar = 0; noCar < 3; noCar++) {
    driverSelectors[noCar].setGuiEnabled(true);
  }
  QString map = ui->gpMapSelector->getMapSelected();
  ui->pbRun->setEnabled(!map.isEmpty() && driverSelectors[0].hasPilots());
}

void GPControlView::newGPControl()
{
  if (gpControl) {
    delete gpControl;
  }

  gpControl = new GPControl(this);
  gpControl->setDelay(delay());
  gpControl->setNextCarMode(static_cast<NextCarMode>(ui->cbNextCarMode->itemData(ui->cbNextCarMode->currentIndex()).toInt()));

  QString map = ui->gpMapSelector->getMapSelected();
  if (!map.isEmpty()) {
    gpControl->setMap(map);
  }

  for (int noCar = 0; noCar < 3; noCar++) {
    gpControl->setCarDebug(noCar, driverSelectors[noCar].debugIsChecked());
    onDriverEnabled(noCar, driverSelectors[noCar].isDriverEnabled());
    gpDriverSelector_debugToggle(noCar, driverSelectors[noCar].debugIsChecked());
  }

  connect(gpControl, SIGNAL(newStderrData(int)), this, SLOT(onPilotSterrData(int)));

  emit mapChanged(gpControl);
}

void GPControlView::selectPreviouslySelectedMap()
{
  QSettings settings;
  QString mapName = settings.value("SelectedMapPath", "").toString();
  ui->gpMapSelector->selectMap(mapName);
}

void GPControlView::closeStderrView()
{
  _stderrView->close();
}

void GPControlView::on_gpMapSelector_mapSelected(const QString & mapPath)
{
  if (gpControl->setMap(mapPath)) {
    emit mapChanged(gpControl);
    enableControls();
  } else {
    QMessageBox msg(this);
    msg.setText(tr("Invalid map, please choose another one."));
    msg.exec();
  }
}

void GPControlView::gpDriverSelector_debugToggle(int car, bool debug)
{
  gpControl->setCarDebug(car, debug);
}

void GPControlView::onRunClicked()
{
  if (gpControl->started()) {
    gpControl->setSteps(-1);
    gpControl->nextMove();
    return;
  }
  emit start();

  if (Logger::enabled()) {
    Logger::open();
    QString start("NEW_RACE");
    start += ";" + QFileInfo(ui->gpMapSelector->getMapSelected()).baseName();
    for (int i = 0; i < gpControl->getNbCars(); ++i) {
      if (driverSelectors[i].isDriverEnabled()) {
        start += ";" + driverSelectors[i].getDriverFileName();
      } else {
        start += ";NO_PILOT";
      }
    }
    Logger::write(start + ";" + QTime::currentTime().toString("HH:mm:ss") + "\n");
    Logger::write("ROUND;POS_CAR1;ACCEL_CAR1;BOOST_CAR1;GAS_CAR1;POS_CAR2;ACCEL_CAR2;BOOST_CAR2;GAS_CAR2;POS_CAR3;ACCEL_CAR3;BOOST_CAR3;GAS_CAR3;\n");
  }
  _stderrView->clear();
  for (int noCar = 0; noCar < gpControl->getNbCars(); noCar++) {
    gpControl->startDriver(noCar, driverSelectors[noCar].getDriverPath());
  }
  disableControls();
  QObject::connect(gpControl, SIGNAL(end(QString)), this, SLOT(gpControl_end(QString)));
  QObject::connect(gpControl, SIGNAL(carMoved(int)), this, SLOT(gpControl_carMoved(int)));
  QObject::connect(gpControl, SIGNAL(carMovedWithBoost(int)), this, SLOT(gpControl_carMovedWithBoost(int)));
  QObject::connect(gpControl, SIGNAL(invalidMove(Acceleration)), this, SLOT(gpControl_invalidMove(Acceleration)));
  QObject::connect(gpControl, SIGNAL(syntaxError()), this, SLOT(gpControl_syntaxError()));
  QObject::connect(gpControl, SIGNAL(driverTimeout()), this, SLOT(gpControl_driverTimeout()));
  QObject::connect(gpControl, SIGNAL(driverCrashed(int)), this, SLOT(gpControl_driverCrashed(int)));
  QObject::connect(gpControl, SIGNAL(driverStopped(int)), this, SLOT(gpControl_driverStopped(int)));

  gpControl->setFirstCar();
  gpControl->nextMove();
}

void GPControlView::onAbortButtonClicked()
{
  gpControl->disconnect();
  newGPControl();
  enableControls();
}

void GPControlView::updateDriverInfo()
{
  for (int noCar = 0; noCar < gpControl->getNbCars(); noCar++) {
    int nbMoves = gpControl->getNbMoves(noCar);
    int nbFailures = gpControl->getNbFailures(noCar);
    int carburant = gpControl->getCarburant(noCar);
    driverSelectors[noCar].setInfo(nbMoves, nbFailures, carburant);
  }
}

QString GPControlView::motionMessage(int car, bool boost) const
{
  Acceleration acc = gpControl->getCarLastAccelerationRequest(car);
  QString res = tr("Driver %1%11: AccRequest(%2,%3) MoveTo(%4,%5) NewSpeed(%6,%7), Boost(%8), Gas(left:%9, used:%10)")
                    .arg(car + 1)
                    .arg(acc.x())
                    .arg(acc.y())
                    .arg(gpControl->getCarPosition(car).x())
                    .arg(gpControl->getCarPosition(car).y())
                    .arg(gpControl->getCarSpeed(car).x())
                    .arg(gpControl->getCarSpeed(car).y())
                    .arg(gpControl->getBoost(car))
                    .arg(gpControl->getCarburant(car))
                    .arg(gpControl->gasolineAtStart() - gpControl->getCarburant(car))
                    .arg(boost ? " (Boost)" : "");
  return res;
}

void GPControlView::gpControl_carMoved(int car)
{
  emit mapChanged(gpControl);
  emit carMoved(motionMessage(car, false));
  updateDriverInfo();
}

void GPControlView::gpControl_carMovedWithBoost(int car)
{
  emit mapChanged(gpControl);
  emit carMoved(motionMessage(car, true));
  updateDriverInfo();
}

void GPControlView::gpControl_invalidMove(Acceleration acceleration)
{
  int curCar = gpControl->getCurrentCar();
  emit invalidMove(tr("Driver %1: Invalid acceleration (%2,%3) Gas: %4").arg(curCar + 1).arg(acceleration.x()).arg(acceleration.y()).arg(gpControl->getCarburant(curCar)));
  updateDriverInfo();
}

void GPControlView::gpControl_syntaxError()
{
  emit syntaxError(tr("Driver %1: Syntax error").arg(gpControl->getCurrentCar() + 1));
}

void GPControlView::gpControl_driverTimeout()
{
  emit driverTimeout(tr("Driver %1: Time out.").arg(gpControl->getCurrentCar() + 1));
}

void GPControlView::gpControl_driverCrashed(int noCar)
{
  emit driverCrashed(tr("<span style=\"color: red;\">Driver %1: crashed</span>").arg(noCar + 1));
}

void GPControlView::gpControl_driverStopped(int noCar)
{
  emit driverCrashed(tr("Driver %1: Stopped (program ended)").arg(noCar + 1));
}

void GPControlView::onDelayChanged(int)
{
  gpControl->setDelay(delay());
}

void GPControlView::gpControl_end(QString results)
{

  if (Logger::enabled()) {
    int maxPositionCount = 0;
    for (int car = 0; car < gpControl->getNbCars(); ++car) {
      if (gpControl->getCarPositions(car).size() > maxPositionCount) {
        maxPositionCount = gpControl->getCarPositions(car).size();
      }
    }
    int i = 0;
    while (i < maxPositionCount) {
      QString line = QString("%1").arg(i);
      for (int car = 0; car < gpControl->getNbCars(); ++car) {
        if (i < gpControl->getCarPositions(car).size()) {
          const Position & p = gpControl->getCarPositions(car).at(i);
          line += ";" + QString("%1,%2").arg(p.x()).arg(p.y());
          if (i < gpControl->getCarAccRequests(car).size()) {
            const Position & a = gpControl->getCarAccRequests(car).at(i);
            line += ";" + QString("%1,%2").arg(a.x()).arg(a.y());
            line += QString(";%1").arg(static_cast<int>(isABoost(a)));
            line += QString(";%1").arg(gpControl->getCarGasLevels(car).at(i));
          } else {
            line += ";;;";
          }
        } else {
          line += ";;;;";
        }
      }
      Logger::write(line + "\n");
      ++i;
    }

    QString finish = gpControl->csvResults();
    Logger::write(finish + ";" + QTime::currentTime().toString("HH:mm:ss") + "\n");
    Logger::close();
  }

  FinnishDialog * msg = new FinnishDialog(this);
  msg->setResults(results);
  msg->setWindowTitle(tr("Finnish!"));
  msg->setModal(true);
  msg->exec();
  msg->deleteLater();
  onAbortButtonClicked();
}

void GPControlView::onNextCarModeChanged(int index)
{
  gpControl->setNextCarMode(static_cast<NextCarMode>(ui->cbNextCarMode->itemData(index).toInt()));
}

void GPControlView::onFollowModeChanged(int index)
{
  switch (index) {
  case GPControl::FollowAll:
    emit carToFollow(-1);
    break;
  case GPControl::FollowCar1:
    emit carToFollow(0);
    break;
  case GPControl::FollowCar2:
    emit carToFollow(1);
    break;
  case GPControl::FollowCar3:
    emit carToFollow(2);
    break;
  }
}

void GPControlView::onDriverEnabled(int car, bool enabled)
{
  if (enabled) {
    gpControl->enableDriver(car);
  } else {
    gpControl->disableDriver(car);
  }
}

void GPControlView::showNoPilotMessage()
{
  int button = QMessageBox::information(this, "Error",
                                        "No executable pilot program found in the ./drivers folder.<br/><br/>"
                                        "You should first install at least one program, then restart the race manager. "
                                        "Right now you won't be able to start a race, but at least you can navigate through the maps."
                                        "<br/><br/>Press Ok to stay, or Close to exit.",
                                        QMessageBox::Ok, QMessageBox::Close);
  if (button == QMessageBox::Close) {
    qApp->quit();
  }
}

void GPControlView::onPilotSterrData(int car)
{
  _stderrView->addData(car, gpControl->logArray(car));
  gpControl->clearLogArray(car);
}

void GPControlView::onStdErrToggled(bool on)
{
  if (on) {
    _stderrView->show();
  } else {
    _stderrView->close();
  }
}

void GPControlView::onStdErrClosed()
{
  ui->tbStderr->setChecked(false);
}

void GPControlView::onStepClicked()
{
  gpControl->setSteps(1);
  if (gpControl->started()) {
    gpControl->nextMove();
  } else {
    onRunClicked();
    ui->pbRun->setEnabled(true);
  }
}

void GPControlView::onTenStepsClicked()
{
  gpControl->setSteps(10 * gpControl->enabledDrivers());
  if (gpControl->started()) {
    gpControl->nextMove();
  } else {
    onRunClicked();
    ui->pbRun->setEnabled(true);
  }
}
