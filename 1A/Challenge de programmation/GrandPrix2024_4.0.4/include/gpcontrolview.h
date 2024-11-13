/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#ifndef GPCONTROLVIEW_H
#define GPCONTROLVIEW_H

#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>
#include "gpcontrol.h"
#include "gpdriverselector.h"
#include "stderrview.h"

namespace Ui
{
class GPControlView;
}

class GPControlView : public QWidget {
  Q_OBJECT

public:
  explicit GPControlView(QWidget * parent = nullptr);
  ~GPControlView();

  int delay() const;

private:
  Ui::GPControlView * ui;
  GPControl * gpControl;
  QVBoxLayout driverSelectorsLayout;
  GPDriverSelector driverSelectors[3];
  StdErrView * _stderrView;

  void enableControls();
  void disableControls();
  void newGPControl();
  void updateDriverInfo();

  QString motionMessage(int car, bool boost) const;

public slots:

  void selectPreviouslySelectedMap();
  void closeStderrView();

private slots:

  void on_gpMapSelector_mapSelected(const QString & mapPath);
  void gpDriverSelector_debugToggle(int car, bool debug);
  void onRunClicked();

  void onDelayChanged(int value);
  void gpControl_carMoved(int car);
  void gpControl_carMovedWithBoost(int car);
  void gpControl_end(QString);
  void gpControl_driverTimeout();
  void gpControl_invalidMove(Acceleration);
  void gpControl_syntaxError();
  void gpControl_driverCrashed(int);
  void gpControl_driverStopped(int);

  void onAbortButtonClicked();

  void onNextCarModeChanged(int index);
  void onFollowModeChanged(int index);
  void onDriverEnabled(int car, bool enabled);

  void showNoPilotMessage();
  void onPilotSterrData(int car);

  void onStdErrToggled(bool);
  void onStdErrClosed();
  void onStepClicked();
  void onTenStepsClicked();

signals:
  void mapChanged(GPControl * gpControl);
  void carMoved(QString);
  void driverTimeout(QString);
  void driverCrashed(QString);
  void driverStopped(QString);
  void invalidMove(QString);
  void syntaxError(QString);
  void serverResponse(QString);
  void start();
  void carToFollow(int);
  void driverEnableChanged();
};

#endif // GPCONTROLVIEW_H
