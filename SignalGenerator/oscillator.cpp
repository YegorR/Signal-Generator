#include "oscillator.h"

Oscillator::Oscillator(QObject* parent) : QObject (parent)
{

}

unsigned long Oscillator::milliPeriod() {
  return _milliPeriod;
}

unsigned long Oscillator::nanoPeriod() {
  return _nanoPeriod;
}

void Oscillator::setMilliPeriod(unsigned long milliPeriod) {
  _milliPeriod = milliPeriod;
}

void Oscillator::setNanoPeriod(unsigned long nanoPeriod) {
  _nanoPeriod = nanoPeriod;
}
