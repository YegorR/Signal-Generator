#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>

class Oscillator : public QObject {
  Q_OBJECT
private:
  double _frequency = 50;
public:
  Oscillator(QObject* parent = nullptr);
  virtual void start() = 0;
  virtual void stop() = 0;
  double frequency();
  void setFrequency(double frequency);
signals:
  void generated(double);
};

#endif // GENERATOR_H
