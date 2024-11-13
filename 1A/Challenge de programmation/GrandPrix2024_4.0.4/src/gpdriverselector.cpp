/**
 * @brief Gestionnaire de course de voitures. Projet 1A Ensicaen.
 *
 * @authors Julien Gosme (2012)
 *          Modifié par G. Lebrun (2015), S. Fourey (2016-...)
 */
#include "gpdriverselector.h"
#include <QDir>
#include <QPainter>
#include <QPolygon>
#include <QSettings>
#include "ui_gpdriverselector.h"

namespace
{
bool caseInsensitiveLessThan(const QString & s1, const QString & s2)
{
  return s1.toLower() < s2.toLower();
}
} // namespace

GPDriverSelector::GPDriverSelector(QWidget * parent) : QWidget(parent), ui(new Ui::GPDriverSelector)
{
  ui->setupUi(this);
  _noCar = 0;
  _guiEnabled = true;
  QDir drivers = QDir("./drivers/");
  QStringList list = drivers.entryList(QDir::Files | QDir::Readable | QDir::Executable, QDir::Name);
  std::sort(list.begin(), list.end(), caseInsensitiveLessThan);
  ui->comboBox->addItems(list);
  _noPilots = list.isEmpty();
  _enabledDriverIndex = 0;
}

void GPDriverSelector::setNoCar(int noCar)
{
  _noCar = noCar;
  ui->label->setText(tr("Driver %1:").arg(noCar + 1));
  QString color;
  switch (noCar) {
  case 0:
    color = "red";
    break;
  case 1:
    color = "green";
    break;
  case 2:
    color = "blue";
    break;
  }
  ui->label->setStyleSheet("QLabel { color : " + color + "; }");

  QImage image(":/res/normal.png");
  QPainter painter(&image);
  painter.drawImage(0, 0, QImage(QString(":/res/car%1.png").arg(noCar + 1)));

  QPolygon p;
  const int w = image.width();
  const int h = image.height();
  p << QPoint(w, h / 4);
  p << QPoint(w, h);
  p << QPoint(w / 4, h);
  painter.setBrush(Qt::white);
  painter.drawPolygon(p);

  QFont font = painter.font();
  font.setPixelSize(image.height() / 2);
  font.setBold(true);
  painter.setFont(font);
  painter.setPen(Qt::black);
  painter.drawText(image.rect().adjusted(0, 0, 0, 2), Qt::AlignBottom | Qt::AlignRight, QString::number(noCar + 1));

  _enabledPixmap = QPixmap::fromImage(image);
  ui->label->setPixmap(_enabledPixmap);

  // painter.fillRect(image.rect(), QColor(0, 0, 0, 192));
  // _disabledPixmap = QPixmap::fromImage(image);

  QSettings settings;
  QString previousSelection = settings.value(QString("SelectedDriver%1").arg(_noCar + 1)).toString();
  for (int index = 0; index < ui->comboBox->count(); ++index) {
    if (ui->comboBox->itemText(index) == previousSelection) {
      ui->comboBox->setCurrentIndex(index);
      _enabledDriverIndex = index;
      break;
    }
  }

  connect(ui->cbEnable, SIGNAL(toggled(bool)), this, SLOT(onEnableToggled(bool)));
  ui->cbEnable->setChecked(QSettings().value(QString("Driver%1Enabled").arg(_noCar + 1), true).toBool());
  onEnableToggled(ui->cbEnable->isChecked());

  ui->debug->setChecked(QSettings().value(QString("DebugDriver%1").arg(noCar + 1), false).toBool());
}

void GPDriverSelector::setGuiEnabled(bool enabled)
{
  _guiEnabled = enabled;
  checkPilotsFound();
  ui->cbEnable->setEnabled(_guiEnabled);
  if (_guiEnabled) {
    ui->comboBox->setEnabled(ui->cbEnable->isChecked());
    ui->debug->setEnabled(ui->cbEnable->isChecked());
  } else {
    ui->comboBox->setEnabled(false);
    ui->debug->setEnabled(false);
  }
}

QString GPDriverSelector::getDriverPath()
{
  if (ui->cbEnable->isChecked()) {
    return "./drivers/" + ui->comboBox->currentText();
  } else {
    return QString();
  }
}

QString GPDriverSelector::getDriverFileName()
{
  return ui->comboBox->currentText();
}

void GPDriverSelector::setInfo(int nbMoves, int nbFailures, int carburant)
{
  ui->info->setText(QString("Hops(%1) Gas(%2) Fail(%3)").arg(nbMoves).arg(carburant).arg(nbFailures));
}

bool GPDriverSelector::isDriverEnabled() const
{
  return ui->cbEnable->isChecked();
}

bool GPDriverSelector::hasPilots() const
{
  return !_noPilots;
}

bool GPDriverSelector::debugIsChecked()
{
  return ui->debug->isChecked();
}

void GPDriverSelector::on_debug_toggled(bool toggle)
{
  emit debugToggle(_noCar, toggle);
}

void GPDriverSelector::onEnableToggled(bool enable)
{
  setGuiEnabled(_guiEnabled);
  ui->label->setEnabled(enable);
  if (enable) {
    if (ui->comboBox->itemText(0) == "(No pilot)") {
      ui->comboBox->removeItem(0);
      ui->comboBox->setCurrentIndex(_enabledDriverIndex);
    }
  } else {
    _enabledDriverIndex = ui->comboBox->currentIndex();
    ui->comboBox->insertItem(0, "(No pilot)");
    ui->comboBox->setCurrentIndex(0);
  }
  emit driverEnabled(_noCar, enable);
}

void GPDriverSelector::checkPilotsFound()
{
  if (_noPilots) {
    ui->comboBox->clear();
    ui->comboBox->addItem("No pilot found");
    ui->comboBox->setToolTip("Folder ./drivers/ is empty.");
    _guiEnabled = false;
  }
}

GPDriverSelector::~GPDriverSelector()
{
  QSettings settings;
  settings.setValue(QString("SelectedDriver%1").arg(_noCar + 1), ui->comboBox->currentText());
  settings.setValue(QString("Driver%1Enabled").arg(_noCar + 1), ui->cbEnable->isChecked());
  settings.setValue(QString("DebugDriver%1").arg(_noCar + 1), ui->debug->isChecked());

  delete ui;
}
