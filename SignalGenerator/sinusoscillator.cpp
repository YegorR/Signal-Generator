#include "sinusoscillator.h"
#include <QtMath>
#include <QDebug>
#include <thread>

SinusOscillator::SinusOscillator(double phase, double frequency, double amplitude,
                                 double deltaPhase, uint deltaPeriod, QObject* parent) :
  Oscillator(parent), _phase(phase), _sinusFrequency(frequency), _amplitude(amplitude),
  _deltaPhase(deltaPhase), _deltaPeriod(deltaPeriod)
{

}

void SinusOscillator::_generate()
{
  double time = 0;
  uint counter = 0;
  while (!_is_stopped) {
      unsigned long samplingPeriod = milliPeriod() * 1000000 + nanoPeriod();
      std::this_thread::sleep_for(std::chrono::nanoseconds(samplingPeriod));
      time += static_cast<double>(samplingPeriod) / 1000000000.0;
      double value = _amplitude * qSin(_phase + time * _sinusFrequency * 2 * M_PI);
      //qDebug() << "SinusOscillator generated value:" << value;
      //qDebug() << "time" << time;
      emit generated(value);
      counter++;
      if (counter >= _deltaPeriod) {
          counter = 0;
          _phase += _deltaPhase;
        }
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
