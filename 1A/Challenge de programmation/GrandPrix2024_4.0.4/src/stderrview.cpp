#include "include/stderrview.h"
#include <QByteArray>
#include <QCloseEvent>
#include <QDebug>
#include <QSettings>
#include "ui_stderrview.h"

StdErrView::StdErrView(QWidget * parent) : QWidget(parent), ui(new Ui::StdErrView)
{
  ui->setupUi(this);
  setWindowTitle("Pilot standard error outputs");
  QSettings settings;
  int index = settings.value("Config/StderrCurrentTab", 0).toInt();
  ui->tabWidget->setCurrentIndex(index);
  connect(ui->pbClose, SIGNAL(clicked(bool)), this, SLOT(close()));
  QFont font = ui->teDriver1->font();
  font.setFamily("Courier");
  font.setStyleHint(QFont::Courier);

  QPlainTextEdit * textEditors[3] = {ui->teDriver1, ui->teDriver2, ui->teDriver3};

  for (QPlainTextEdit * editor : textEditors) {
    editor->setFont(font);
    editor->setReadOnly(true);
    editor->setLineWrapMode(QPlainTextEdit::WidgetWidth);
  }

  ui->fontSize->setRange(50, 100);
  ui->fontSize->setValue(settings.value("Config/StderrFontSize", 100).toInt());
  connect(ui->fontSize, SIGNAL(valueChanged(int)), this, SLOT(setFontSize(int)));
  _firstShow = true;
}

StdErrView::~StdErrView()
{
  QSettings settings;
  settings.setValue("Config/StderrCurrentTab", ui->tabWidget->currentIndex());
  settings.setValue("Config/StderrFontSize", ui->fontSize->value());
  delete ui;
}

void StdErrView::showEvent(QShowEvent *)
{
  if (_firstShow) {
    _firstShow = false;
    QSettings settings;
    QPoint position = settings.value("Config/StderrPosition", QPoint()).toPoint();
    QRect r = settings.value("Config/StderrWindowRect", QRect()).toRect();
    if (r.isValid()) {
      setGeometry(r);
      move(position);
    }
    setFontSize(ui->fontSize->value());
  }
}

void StdErrView::closeEvent(QCloseEvent * e)
{
  if (isVisible()) {
    QSettings settings;
    settings.setValue("Config/StderrPosition", frameGeometry().topLeft());
    settings.setValue("Config/StderrWindowRect", rect());
  }
  emit aboutToClose();
  e->accept();
}

void StdErrView::addData(int car, const QByteArray & data)
{
  switch (car) {
  case 0:
    ui->teDriver1->insertPlainText(data);
    ui->teDriver1->ensureCursorVisible();
    break;
  case 1:
    ui->teDriver2->insertPlainText(data);
    ui->teDriver2->ensureCursorVisible();
    break;
  case 2:
    ui->teDriver3->insertPlainText(data);
    ui->teDriver3->ensureCursorVisible();
    break;
  default:
    break;
  }
}

void StdErrView::setFontSize(int value)
{
  int size = ui->tabWidget->font().pointSize();
  size = static_cast<int>(size * (value / 100.0));
  QFont font = ui->teDriver1->font();
  font.setPointSize(size);
  ui->teDriver1->setFont(font);
  ui->teDriver2->setFont(font);
  ui->teDriver3->setFont(font);
}

void StdErrView::clear()
{
  ui->teDriver1->clear();
  ui->teDriver2->clear();
  ui->teDriver3->clear();
}
