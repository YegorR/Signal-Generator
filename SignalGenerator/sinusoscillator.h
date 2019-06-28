#ifndef SINUSGENERATOR_H
#define SINUSGENERATOR_H

#include "oscillator.h"


class SinusOscillator : public Oscillator
{
private:
  const double _phase;
  const double _sinusFrequency;
  const double _amplitude;

  bool _is_stopped = true;

  void _generate();
public:
  SinusOscillator(double phase, double frequency, double amplitude, QObject* parent = nullptr);
  void start();
  void stop();
};

#endif // SINUSGENERATOR_H
