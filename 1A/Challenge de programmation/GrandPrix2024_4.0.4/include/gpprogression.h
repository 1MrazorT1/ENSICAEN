/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#ifndef GPPROGRESSION_H
#define GPPROGRESSION_H

#include <QWidget>

namespace Ui {
class GPProgression;
}

class GPProgression : public QWidget {
  Q_OBJECT

public:
  explicit GPProgression(QWidget *parent = 0);
  ~GPProgression();

private:
  Ui::GPProgression *ui;
};

#endif // GPPROGRESSION_H
