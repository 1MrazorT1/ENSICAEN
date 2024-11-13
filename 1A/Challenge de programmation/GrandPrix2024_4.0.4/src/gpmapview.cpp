/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include "gpmapview.h"
#include <QMouseEvent>
#include <QtCore/qmath.h>
#include <assert.h>
#include <utility>
#include "ui_gpmapview.h"

GPMapView::GPMapView(QWidget * parent)
    : QWidget(parent), ui(new Ui::GPMapView), _driverView(false), zoom(1.), normal(":/res/normal.png"), sand(":/res/sand.png"), goal(":/res/goal.png"), out(":/res/out.png"), car1(":/res/car1.png"),
      car2(":/res/car2.png"), car3(":/res/car3.png"), available1(":/res/available1.png"), available2(":/res/available2.png"), available3(":/res/available3.png"), current(":/res/current.png"),
      carToFollow(-1)
{
  ui->setupUi(this);
  _gpControl = nullptr;
}

GPMapView::~GPMapView()
{
  delete ui;
}

void GPMapView::mapChanged(GPControl * gpControl)
{
  _gpControl = gpControl;
  update();
}

void GPMapView::setDriverView(bool driverView)
{
  _driverView = driverView;
}

void GPMapView::setCarToFollow(int nCar)
{
  carToFollow = nCar;
}

void GPMapView::paintEvent(QPaintEvent * event)
{
  QPainter painter(this);
  assert(event == event);
  if (!_gpControl || !_gpControl->getNbCars()) {
    return;
  }

  int sizeX = _gpControl->getSizeX();
  int sizeY = _gpControl->getSizeY();

  float tileWidth = 0.0;
  float tileHeight = 0.0;

  int minX = 0;
  int minY = 0;

  int maxX = 0;
  int maxY = 0;

  int offsetY = 32;
  int offsetX = 32;

  int sizeXWidget = 0;
  int sizeYWidget = 0;

  int curCar = _gpControl->getCurrentCar();
  if (carToFollow != -1) {
    curCar = carToFollow;
  }
  Position currCarPosition = _gpControl->getCarPosition(curCar);

  sizeXWidget = this->width();
  sizeYWidget = this->height();

  float radius;
  if (_driverView) {
    radius = 4 * zoom;
  } else {
    radius = std::max(sizeY, sizeX) * zoom;
  }
  if (sizeXWidget >= sizeYWidget) {
    minX = currCarPosition.x() - (int)(sizeXWidget / sizeYWidget * radius);
    maxX = currCarPosition.x() + (int)(sizeXWidget / sizeYWidget * radius);
    minY = currCarPosition.y() - radius;
    maxY = currCarPosition.y() + radius;
  } else {
    minX = currCarPosition.x() - radius;
    maxX = currCarPosition.x() + radius;
    minY = currCarPosition.y() - (int)(sizeYWidget / sizeXWidget * radius);
    maxY = currCarPosition.y() + (int)(sizeYWidget / sizeXWidget * radius);
  }
  if (!_driverView) {
    minX = std::max(0, minX);
    minY = std::max(0, minY);
    maxX = std::min(sizeX, maxX);
    maxY = std::min(sizeY, maxY);
  }

  tileWidth = (float)(width() - offsetX) / (maxX - minX);
  tileHeight = (float)(height() - offsetY) / (maxY - minY);

  for (int y = minY; y < maxY; y++) {
    for (int x = minX; x < maxX; x++) {
      int type = _gpControl->getTile(Position(x, y));
      QImage * img;
      switch (type) {
      case GPControl::NORMAL:
        img = &normal;
        break;
      case GPControl::OUT:
        img = &out;
        break;
      case GPControl::GOAL:
        img = &goal;
        break;
      case GPControl::SAND:
        img = &sand;
        break;
      default:
        img = &out;
      }

      painter.drawImage(QRectF(offsetX + tileWidth * (x - minX), offsetY + tileHeight * (y - minY), tileWidth + 0.01, tileHeight + 0.01), *img, QRectF(0, 0, 36, 36));
      if ((y - minY) == 0 && (_driverView || x % 5 == 0)) {
        painter.drawText(QRectF(offsetX + tileWidth * (x - minX - 1), 0, tileWidth * 3 + 0.01, offsetY), QString("%1").arg(x), QTextOption(Qt::AlignCenter));
      }
      if ((x - minX) == 0 && (_driverView || y % 5 == 0)) {
        painter.drawText(QRectF(0, offsetY + tileHeight * (y - minY - 1), offsetX, tileHeight * 3 + 0.01), QString("%1").arg(y), QTextOption(Qt::AlignCenter));
      }
    }
  }

  for (int noCar = 0; noCar < this->_gpControl->getNbCars(); noCar++) {
    if (_gpControl->driverDisabled(noCar) && !_gpControl->getNbMoves(noCar)) {
      continue;
    }
    QImage * img = nullptr;
    QRectF rectf;
    qreal angle;
    switch (_gpControl->startPosition(noCar)) {
    case 1:
      img = &car1;
      break;
    case 2:
      img = &car2;
      break;
    case 3:
      img = &car3;
      break;
      // default:

      // color=Qt::magenta;
      // qWarning("unknown car type '%i'", noCar);
    }

    // Display of availables positions and current car indicator
    if (noCar == _gpControl->getCurrentCar()) {
      painter.drawImage(QRectF(offsetX + tileWidth * (currCarPosition.x() - minX),  //
                               offsetY + tileHeight * (currCarPosition.y() - minY), //
                               tileWidth,                                           //
                               tileHeight),
                        current, QRectF(0, 0, 36, 36));

      if (_gpControl->getCarDebug(noCar)) {
        QImage * img_available = NULL;
        if (noCar == 0) {
          img_available = &available1;
        } else if (noCar == 1) {
          img_available = &available2;
        } else if (noCar == 2) {
          img_available = &available3;
        }

        QSet<Acceleration> available = _gpControl->availableAccelerations(noCar);
        QSet<Acceleration>::iterator i;
        for (i = available.begin(); i != available.end(); ++i) {
          painter.drawImage(QRectF(offsetX + tileWidth * (_gpControl->getCarPosition(noCar).x() + _gpControl->getCarSpeed(noCar).x() + i->x() - minX),  //
                                   offsetY + tileHeight * (_gpControl->getCarPosition(noCar).y() + _gpControl->getCarSpeed(noCar).y() + i->y() - minY), //
                                   tileWidth,                                                                                                           //
                                   tileHeight),
                            *img_available, //
                            QRectF(0, 0, 36, 36));
        }
      }
    }

    // Display of the cars
    if (img) {
      angle = qAtan2(_gpControl->getCarSpeed(noCar).x(), _gpControl->getCarSpeed(noCar).y()); // Radius between -Pi et Pi
      angle = angle * 180 / M_PI + 90;
      painter.translate(offsetX + tileWidth * (_gpControl->getCarPosition(noCar).x() - minX) + tileWidth * 0.5,
                        offsetY + tileHeight * (_gpControl->getCarPosition(noCar).y() - minY) + tileHeight * 0.5); // On déplace le système de coordonnéees au
                                                                                                                   // centre de l'emplacement que l'on veut
      painter.rotate(-angle);
      rectf = QRectF(-tileWidth * 0.5, -tileHeight * 0.5, tileWidth,
                     tileHeight); // Destination rectangle with rotation
      painter.drawImage(rectf, *img, QRectF(0, 0, 36, 36));
      painter.resetTransform(); // Rotation and translation reset
    }

    // Display of the trajectory of the cars with lines
    for (int i = 1; i < _gpControl->getNbPositions(noCar); i++) {
      QPen pen;
      qreal widthBrush = qAbs((tileWidth + tileHeight) / 20);
      QColor color = _gpControl->getColor(noCar);

      pen.setStyle(Qt::DotLine);
      pen.setWidthF(widthBrush);
      color.setAlpha(100);
      pen.setBrush(color);
      pen.setCapStyle(Qt::SquareCap);

      painter.setPen(pen);
      painter.drawLine(offsetX + tileWidth * (_gpControl->getOldCarPosition(noCar, i - 1).x() - minX) + tileWidth * 0.5,   //
                       offsetY + tileHeight * (_gpControl->getOldCarPosition(noCar, i - 1).y() - minY) + tileHeight * 0.5, //
                       offsetX + tileWidth * (_gpControl->getOldCarPosition(noCar, i).x() - minX) + tileWidth * 0.5,       //
                       offsetY + tileHeight * (_gpControl->getOldCarPosition(noCar, i).y() - minY) + tileHeight * 0.5);
    }

    // Display of the old positions of the cars with circles
    for (int i = 0; i < (_gpControl->getNbPositions(noCar) - 1); i++) {
      int boostUsed = 0, j = 0;

      while (!boostUsed && j < _gpControl->getNbBoostUsed(noCar)) { // Looking for a boost usage at the current position
        boostUsed = (i == _gpControl->getIndexBoostUsed(noCar, j));
        j++;
      }

      QPen pen;
      qreal widthCircle = (tileWidth + tileHeight) / 5 * (1 + boostUsed);

      pen = painter.pen();

      pen.setStyle(Qt::SolidLine);
      painter.setPen(pen);

      painter.drawEllipse(offsetX + tileWidth * (_gpControl->getOldCarPosition(noCar, i).x() - minX) + tileWidth / 2 - widthCircle / 2,
                          offsetY + tileHeight * (_gpControl->getOldCarPosition(noCar, i).y() - minY) + tileHeight / 2 - widthCircle / 2, widthCircle, widthCircle);
    }
  }
}

void GPMapView::mousePressEvent(QMouseEvent * event)
{
  if (event->button() == Qt::LeftButton) {
  } else if (event->button() == Qt::RightButton) {
    zoom = 1.;
  }
  update();
}
void GPMapView::wheelEvent(QWheelEvent * event)
{
  float delta;
  if (event->angleDelta().y() < 0) {
    delta = 1.2;
  } else {
    delta = 0.8;
  }
  zoom = std::max(std::min(zoom * delta, 1.0f), 0.02f);
  update();
}
