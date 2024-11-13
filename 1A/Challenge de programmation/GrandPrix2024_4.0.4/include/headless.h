/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#ifndef HEADLESS_H
#define HEADLESS_H

#include <QApplication>
#include <QObject>
#include "gpcontrol.h"

class Headless : public QCoreApplication {
  Q_OBJECT

private:
  GPControl control;

public:
  Headless(int & argc, char ** argv, bool * loaded);

public slots:
  void on_end(QString str);
};

#endif
