#ifndef STDERRVIEW_H
#define STDERRVIEW_H

#include <QWidget>

class QByteArray;

namespace Ui
{
class StdErrView;
}

class StdErrView : public QWidget {
  Q_OBJECT

public:
  explicit StdErrView(QWidget * parent = nullptr);
  ~StdErrView();
  void showEvent(QShowEvent *) override;
  void closeEvent(QCloseEvent *) override;
  void addData(int car, const QByteArray & data);

public slots:
  void setFontSize(int);
  void clear();
signals:
  void aboutToClose();

private:
  Ui::StdErrView * ui;
  bool _firstShow;
};

#endif // STDERRVIEW_H
