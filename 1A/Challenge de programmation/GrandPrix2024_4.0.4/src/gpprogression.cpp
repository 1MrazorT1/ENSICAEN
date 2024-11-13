/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include "gpprogression.h"
#include "ui_gpprogression.h"

GPProgression::GPProgression(QWidget *parent)
    : QWidget(parent), ui(new Ui::GPProgression) {
  ui->setupUi(this);
}

GPProgression::~GPProgression() { delete ui; }
