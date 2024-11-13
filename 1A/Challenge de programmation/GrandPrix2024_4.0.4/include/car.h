/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#ifndef VOITURE_H
#define VOITURE_H
#include <QColor>
#include <QPoint>
#include <QProcess>

typedef QPoint Position;
typedef QPoint Speed;
typedef QPoint Acceleration;

class Car {

public:
  QString name;
  QList<Position> positions;
  QList<Position> accelerationRequests;
  QList<int> gasLevels;
  QList<int> boostUsage;
  Speed speed;
  Acceleration lastAccelerationRequest;
  int moveCount;
  int failureCount;
  int gasLevel;
  int boostLevel;
  int startPosition;
  int finishPosition;
  bool previousTimeout;
  QColor color;
  bool debug;
  QProcess * driver;
  Car();
  ~Car();
  void stop();
  void reset(int x, int y, int boostLevel, int startPosition, QColor color);
  void fillTank(int value);
  bool isOutOfGas() const;
  void useGasoline(int value);
};

inline bool qHash(const Acceleration & acceleration)
{
  return qHash(QPair<int, int>(acceleration.x(), acceleration.y()));
}

inline bool validSpeed(Speed speed)
{
  return (speed.x() * speed.x() + speed.y() * speed.y()) <= 25;
}

inline bool validSpeedInSand(Speed speed)
{
  return (speed.x() * speed.x() + speed.y() * speed.y()) <= 1;
}

inline bool isABoost(Acceleration acceleration)
{
  return std::abs(acceleration.x()) == 2 || std::abs(acceleration.y()) == 2;
}
#endif
