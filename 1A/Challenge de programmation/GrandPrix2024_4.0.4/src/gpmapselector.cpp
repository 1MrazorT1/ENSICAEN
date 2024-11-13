/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include "gpmapselector.h"
#include <QDir>
#include <QSettings>
#include <QtDebug>
#include "ui_gpmapselector.h"

namespace
{
bool caseInsensitiveLessThan(const QString & s1, const QString & s2)
{
  return s1.toLower() < s2.toLower();
}
} // namespace

GPMapSelector::GPMapSelector(QWidget * parent) : QWidget(parent), ui(new Ui::GPMapSelector)
{
  ui->setupUi(this);
  QDir tracks = QDir("./tracks/");
  // qWarning() << QDir::currentPath();
  // qWarning() << tracks;

  QStringList filters;
  filters << "*.txt";
  QStringList list = tracks.entryList(filters, QDir::Files | QDir::Readable, QDir::Name);
  std::sort(list.begin(), list.end(), caseInsensitiveLessThan);
  ui->listMap->addItems(list);

  mapSel = QString();
}

GPMapSelector::~GPMapSelector()
{
  if (ui->listMap->currentItem()) {
    QSettings().setValue("SelectedMapPath", ui->listMap->currentItem()->text());
  }
  delete ui;
}

void GPMapSelector::enabledSelectionChange(bool state)
{
  ui->listMap->setEnabled(state);
}

void GPMapSelector::selectMap(QString text)
{
  for (int row = 0; row < ui->listMap->count(); ++row) {
    if (ui->listMap->item(row)->text() == text) {
      ui->listMap->setCurrentRow(row);
      return;
    }
  }
}

void GPMapSelector::on_listMap_itemSelectionChanged()
{
  QListWidgetItem * item = ui->listMap->currentItem();
  if (item) {
    mapSel = "./tracks/" + item->text();
    emit mapSelected(mapSel);
  }
}

QString GPMapSelector::getMapSelected()
{
  return mapSel;
}
