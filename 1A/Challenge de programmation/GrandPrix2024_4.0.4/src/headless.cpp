/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include "headless.h"
#include <iostream>

Headless::Headless(int & argc, char ** argv, bool * loaded) : QCoreApplication(argc, argv)
{
  *loaded = false;
  control.setDelay(0);

  if (!control.setMap(argv[1])) {
    qCritical("Map failed to load.");
    return;
  }
  control.startDriver(0, argv[2]);
  control.startDriver(1, argv[3]);
  control.startDriver(2, argv[4]);

  QObject::connect(&control, SIGNAL(end(QString)), this, SLOT(on_end(QString)));

  control.nextMove();
  *loaded = true;
}

void Headless::on_end(QString)
{
  for (int i = 1; i <= 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (control.startPosition(j) == i) {
        int consumption = control.gasolineAtStart() - control.getCarburant(j);

        QString name = QString("%1").arg(control.getDriverName(j), 25, QChar(' '));
        QString moves = QString("%1 moves").arg(control.getNbMoves(j), 3, 10, QChar(' '));
        QString gas = QString("%1 gas used").arg(consumption, 3, 10, QChar(' '));
        std::cout << i << " " << name.toStdString() << ' ' << moves.toStdString() << ' ' << gas.toStdString() << std::endl;
      }
    }
  }
  ::exit(0);
}
