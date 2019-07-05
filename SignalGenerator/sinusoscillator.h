#ifndef SINUSGENERATOR_H
#define SINUSGENERATOR_H

#include "oscillator.h"


class SinusOscillator : public Oscillator
{
private:
  double _phase;
  const double _sinusFrequency;
  const double _amplitude;
  const double _deltaPhase;
  const double _deltaPeriod;
  bool _is_stopped = true;

  void _generate();
public:
  SinusOscillator(double phase, double frequency, double amplitude,
                  double deltaPhase, uint deltaPeriod, QObject* parent = nullptr);
  void start();
  void stop();
};

#endif // SINUSGENERATOR_H
