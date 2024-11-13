/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#ifndef GPCONTROL_H
#define GPCONTROL_H

#include <QFile>
#include <QObject>
#include <QPair>
#include <QTextStream>
#include <QTimer>
#include <QtDebug>
#include <memory>
#include "car.h"

enum NextCarMode
{
  RANDOM,
  SEQUENTIAL
};

/**
 * @brief Structure pour le position d'un element sur la map avec des
 * coordonnees entieres
 */
typedef struct {
  int x;
  int y;
} Pos2Dint;

/**
 * @brief Structure pour une position 2D avec des coordonnees flottantes
 */
typedef struct {
  float x;
  float y;
} Pos2Dfloat;

/**
 * @brief Structure permettant de definir un segment et de se deplacer le long
 */
typedef struct {
  Pos2Dint posStart;    /*< Debut du segment */
  Pos2Dint posEnd;      /*< Fin du segment */
  Pos2Dfloat posActual; /*< Position Actuel sur le segment */
  Pos2Dfloat delta;     /*< Variation en x et en y pour le deplacement */
  int len;              /*< Longueur suivant l'axe principale */
  int pos;              /*< Position de reference sur la ligne */
} infoLine;

/**
 * @brief Definition d'un segment entre deux points
 */
void line(int x1, int y1, int x2, int y2, infoLine * data);

/**
 * @brief Deplacement sur un segment dans un sens donne (+1 vers la fin, et -1
 * vers le debut)
 */
int nextPoint(infoLine * data, Pos2Dint * point, int sens);

class GPControl : public QObject {
  Q_OBJECT

public:
  explicit GPControl(QObject * parent = 0);
  ~GPControl();

  enum Tile
  {
    OUT = 0,
    NORMAL = 1,
    SAND = 2,
    START1 = 3,
    START2 = 4,
    START3 = 5,
    GOAL = 6
  };

  enum TileChar
  {
    OUT_CHAR = '.',
    NORMAL_CHAR = '#',
    SAND_CHAR = '~',
    START1_CHAR = '1',
    START2_CHAR = '2',
    START3_CHAR = '3',
    GOAL_CHAR = '='
  };

  enum FollowMode
  {
    FollowAll,
    FollowCar1,
    FollowCar2,
    FollowCar3
  };

private:
  QVector<GPControl::Tile> tiles;
  QVector<Car> cars;
  std::shared_ptr<QFile> _logFiles[3];
  QByteArray _logArrays[3];
  bool _driverEnabled[3];

  QTimer timer;

  NextCarMode nextCarMode;
  int sizeX;
  int sizeY;
  int nbCars;
  int currentCarIndex;
  static const int nbrMaxBoost = 5; /* Valeur par defaut dans le cas de la gestion du carburant */
  int delay;
  int gasLevelAtStart;
  void nextCar();
  int finishPosition;

signals:
  void carMoved(int car);
  void carMovedWithBoost(int car);
  void driverTimeout();
  void driverCrashed(int);
  void driverStopped(int);
  void invalidMove(Acceleration);
  void syntaxError();
  void end(QString res);
  void newStderrData(int car);

public:
  const QByteArray & logArray(int car) const;
  void clearLogArray(int car);

  bool setMap(const QString & mapPath);
  int getSizeX();
  int getSizeY();
  int getNbCars();

  const QList<Position> & getCarPositions(int car) const;
  const QList<Position> & getCarAccRequests(int car) const;
  const QList<int> & getCarGasLevels(int car) const;

  Position getCarPosition(int noCar) const;
  Acceleration getCarLastAccelerationRequest(int noCar) const;
  Position getOldCarPosition(int noCar, int numPos) const;
  int getCarburant(int noCar);
  Speed getCarSpeed(int noCar) const;
  int getBoost(int noCar);
  int getNbBoostUsed(int noCar);
  int getIndexBoostUsed(int noCar, int numBoost);
  int getNbMoves(int noCar);
  int getNbFailures(int noCar);
  int getNbPositions(int noCar);
  int startPosition(int noCar);
  QColor getColor(int noCar);
  void setCarDebug(int car, bool debug);
  bool getCarDebug(int car);
  QString getDriverName(int noCar);

  void setNextCarMode(NextCarMode mode);
  GPControl::Tile getTile(Position position) const;
  char getTileChar(int x, int y);
  int getCurrentCar();
  void startDriver(int noCar, const QString & driverPath);
  QByteArray mapData();
  QByteArray positionsData();

  int gasolineAtStart() const;
  void moveCurrentCar(Acceleration acceleration);
  QSet<Acceleration> availableAccelerations(int noCar) const;
  bool isFree(Position position) const;
  void setDelay(int value);
  bool isAtEnd() const;
  QString results();
  QString csvResults();
  bool noCollision(int noCar, Acceleration acceleration);

  bool driverDisabled(int car) const;
  bool driverEnabled(int car) const;

  void disableDriver(int car);
  void enableDriver(int car);
  void closeCarStderr(int noCar);

  static int gasolineConsumption(Acceleration acceleration, Speed speed);
  static QString logFilename(int noCar);

  bool started() const;
  int enabledDrivers() const;

public slots:
  void setFirstCar();
  void nextMove();
  void setSteps(int steps = -1);
private slots:
  void readyReadStandardOutput();
  void onReadyReadStandardError(int car);
  void timeout();

private:
  int _carSequence[3];
  int _positionInCarSequence = 0;
  int _steps;
  bool _started = false;
};

#endif // GPCONTROL_H
