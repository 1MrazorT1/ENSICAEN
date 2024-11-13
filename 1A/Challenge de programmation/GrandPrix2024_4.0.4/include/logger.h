#ifndef GPLOGGER_H
#define GPLOGGER_H
#include <QFile>
#include <QString>
#include <memory>

class Logger {
public:
  static void setEnabled();
  static void open();
  static void write(QString line);
  static bool enabled();
  static void close();

public:
  static std::unique_ptr<QFile> _file;
  static bool _isEnabled;
};

#endif
