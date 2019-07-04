#ifndef FILEOSCILLATOR_H
#define FILEOSCILLATOR_H

#include "oscillator.h"

class FileOscillator : public Oscillator
{
public:
  FileOscillator(QString filename ,QObject* parent = nullptr);
  void start();
  void stop();
};

#endif // FILEOSCILLATOR_H
