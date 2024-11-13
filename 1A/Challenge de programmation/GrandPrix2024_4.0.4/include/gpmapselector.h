/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#ifndef GPMAPSELECTOR_H
#define GPMAPSELECTOR_H

#include <QListWidgetItem>
#include <QWidget>

namespace Ui
{
class GPMapSelector;
}

class GPMapSelector : public QWidget {
  Q_OBJECT

private:
  QString mapSel;

public:
  explicit GPMapSelector(QWidget * parent = 0);
  ~GPMapSelector();
  QString getMapSelected();

private slots:
  void on_listMap_itemSelectionChanged();

private:
  Ui::GPMapSelector * ui;

signals:
  void mapSelected(QString mapPath);

public slots:
  void enabledSelectionChange(bool state);
  void selectMap(QString text);
};

#endif // GPMAPSELECTOR_H
