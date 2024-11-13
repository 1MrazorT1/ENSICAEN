/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include "car.h"

Car::Car() : positions(), boostUsage(), speed(0, 0), moveCount(0), failureCount(0), boostLevel(0), startPosition(0), finishPosition(4), debug(false)
{
  driver = new QProcess;
  previousTimeout = false;
}

Car::~Car()
{
  driver->disconnect();
  driver->close();
  driver->deleteLater();
}

void Car::stop()
{
  speed = QPoint(0, 0);
}

void Car::reset(int x, int y, int boosts, int position, QColor color)
{
  positions.clear();
  boostUsage.clear();
  positions.append(Position(x, y));
  speed = Speed(0, 0);
  boostLevel = boosts;
  moveCount = 0;
  failureCount = 0;
  startPosition = position;
  finishPosition = 4;
  this->color = color;
  this->gasLevel = 0;
}

void Car::fillTank(int value)
{
  gasLevel = value;
}

bool Car::isOutOfGas() const
{
  return !gasLevel;
}

void Car::useGasoline(int value)
{
  if (value < 0 || value > gasLevel) {
    gasLevel = 0;
  } else {
    gasLevel -= value;
  }
}
