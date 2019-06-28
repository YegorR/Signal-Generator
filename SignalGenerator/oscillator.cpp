#include "oscillator.h"

Oscillator::Oscillator(QObject* parent) : QObject (parent)
{

}

double Oscillator::frequency() {
  return _frequency;
}

void Oscillator::setFrequency(double frequency) {
  _frequency = frequency;
}
