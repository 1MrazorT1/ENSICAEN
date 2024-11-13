/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#ifndef GPDRIVERSELECTOR_H
#define GPDRIVERSELECTOR_H

#include <QWidget>

namespace Ui
{
class GPDriverSelector;
}

class GPDriverSelector : public QWidget {
  Q_OBJECT

public:
  explicit GPDriverSelector(QWidget * parent = 0);
  ~GPDriverSelector();

  void setNoCar(int _noCar);
  void setGuiEnabled(bool enabled);
  QString getDriverPath();
  QString getDriverFileName();
  bool debugIsChecked();
  void setInfo(int nbMoves, int nbFailures, int carburant);
  bool isDriverEnabled() const;

  bool hasPilots() const;

public slots:

  void onEnableToggled(bool enable);

private:
  Ui::GPDriverSelector * ui;
  int _noCar;
  bool _guiEnabled;

  QPixmap _enabledPixmap;
  // QPixmap _disabledPixmap;
  int _enabledDriverIndex;
  bool _noPilots;
  void checkPilotsFound();
private slots:
  void on_debug_toggled(bool toggle);
signals:
  void debugToggle(int car, bool debug);
  void driverEnabled(int car, bool enabled);
};

#endif // GPDRIVERSELECTOR_H
