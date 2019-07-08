#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>

class Oscillator : public QObject {
  Q_OBJECT
private:
  unsigned long _milliPeriod = 500;
  unsigned long _nanoPeriod = 0;
public:
  Oscillator(QObject* parent = nullptr);
  virtual void start() = 0;
  virtual void stop() = 0;
  unsigned long milliPeriod();
  unsigned long nanoPeriod();
  void setMilliPeriod(unsigned long milliPeriod);
  void setNanoPeriod(unsigned long nanoPeriod);
signals:
  void generated(double);
};

#endif // GENERATOR_H
