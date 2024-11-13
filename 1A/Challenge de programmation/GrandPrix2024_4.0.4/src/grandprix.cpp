/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include "grandprix.h"
#include <QCloseEvent>
#include <QSettings>
#include <QShortcut>
#include <QTimer>
#include "ui_grandprix.h"

#define STRINGIFY(s) #s
#define X_STRINGIFY(s) STRINGIFY(s)

GrandPrix::GrandPrix(QWidget * parent) : QMainWindow(parent), ui(new Ui::GrandPrix)
{
  ui->setupUi(this);
  setWindowTitle("GrandPrix 2020 v" X_STRINGIFY(GP_VERSION));
  QApplication::setWindowIcon(QIcon(":/res/grand_prix.png"));
  QObject::connect(ui->controlview, SIGNAL(mapChanged(GPControl *)), ui->mapview, SLOT(mapChanged(GPControl *)));
  QObject::connect(ui->controlview, SIGNAL(driverEnableChanged()), ui->mapview, SLOT(update()));

  ui->driverview->setDriverView(true);

  QObject::connect(ui->controlview, SIGNAL(carToFollow(int)), ui->driverview, SLOT(setCarToFollow(int)));

  QObject::connect(ui->controlview, SIGNAL(mapChanged(GPControl *)), ui->driverview, SLOT(mapChanged(GPControl *)));

  QObject::connect(ui->controlview, SIGNAL(start()), ui->log, SLOT(clear()));

  QObject::connect(ui->controlview, SIGNAL(carMoved(QString)), ui->log, SLOT(appendPlainText(QString)));
  QObject::connect(ui->controlview, SIGNAL(driverTimeout(QString)), ui->log, SLOT(appendPlainText(QString)));
  QObject::connect(ui->controlview, SIGNAL(driverCrashed(QString)), ui->log, SLOT(appendHtml(QString)));
  QObject::connect(ui->controlview, SIGNAL(invalidMove(QString)), ui->log, SLOT(appendPlainText(QString)));
  QObject::connect(ui->controlview, SIGNAL(syntaxError(QString)), ui->log, SLOT(appendPlainText(QString)));
  QObject::connect(ui->controlview, SIGNAL(serverResponse(QString)), ui->log, SLOT(appendPlainText(QString)));

  QShortcut * quit = new QShortcut(QKeySequence::Quit, this);
  quit->setContext(Qt::ApplicationShortcut);
  connect(quit, &QShortcut::activated, this, &GrandPrix::close);
}

GrandPrix::~GrandPrix()
{
  delete ui;
}

void GrandPrix::showEvent(QShowEvent *)
{
  if (_firstShow) {
    _firstShow = false;
    QSettings settings;
    QPoint position = settings.value("Config/MainWindowPosition", QPoint()).toPoint();
    QRect r = settings.value("Config/MainWindowRect", QRect()).toRect();
    if (r.isValid()) {
      setGeometry(r);
      move(position);
    }
    QTimer::singleShot(0, ui->controlview, SLOT(selectPreviouslySelectedMap()));
  }
}

void GrandPrix::closeEvent(QCloseEvent * event)
{
  QSettings settings;
  settings.setValue("Config/MainWindowPosition", frameGeometry().topLeft());
  settings.setValue("Config/MainWindowRect", rect());
  settings.setValue("Config/Speed", ui->controlview->delay());
  ui->controlview->closeStderrView();
  event->accept();
}
