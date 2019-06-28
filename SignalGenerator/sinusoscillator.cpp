#include "sinusoscillator.h"
#include <QThread>
#include <QtMath>

SinusOscillator::SinusOscillator(double phase, double frequency, double amplitude, QObject* parent) :
  Oscillator(parent), _phase(phase), _sinusFrequency(frequency), _amplitude(amplitude)
{

}

void SinusOscillator::_generate()
{
  unsigned long time = 0;
  while (!_is_stopped) {
      unsigned long samplingPeriod = static_cast<unsigned long>(1 / frequency() * 1000);
      QThread::msleep(samplingPeriod);
      time += samplingPeriod / 1000;
      double value = _amplitude * qSin(_phase + time * _sinusFrequency * 2 * M_PI);
      emit generated(value);
    }
}

void SinusOscillator::start()
{
  if (!_is_stopped) {
      return;
    }
  _is_stopped = false;
  _generate();
}

void SinusOscillator::stop()
{
  _is_stopped = true;
}
