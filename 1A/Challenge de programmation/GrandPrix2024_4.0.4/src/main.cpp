/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>
#include <QString>
#include <QStyleFactory>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "grandprix.h"
#include "headless.h"
#include "logger.h"

int main(int argc, char * argv[])
{
  if (argc == 5) {
    bool ok;
    Headless a(argc, argv, &ok);
    if (ok) {
      return a.exec();
    } else {
      return 1;
    }
  }

  bool log = (argc >= 2 && (QString::fromLocal8Bit(argv[1]) == "--log"));
  if (log) {
    Logger::setEnabled();
  }

  if (!log && argc != 1) {
    qCritical("./GrandPrix [--log | [tracks/<map> drivers/<driver1> drivers/<driver2> "
              "drivers/<driver3>]");
    return EXIT_FAILURE;
  }

  QApplication a(argc, argv);
  // QApplication::setStyle(QStyleFactory::create("Fusion"));
  QCoreApplication::setOrganizationName("Ensicaen");
  QCoreApplication::setOrganizationDomain("ensicaen.fr");
  QCoreApplication::setApplicationName("GrandPrix");
  GrandPrix w;
  w.show();
  return a.exec();
}
