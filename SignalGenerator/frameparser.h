#ifndef FRAMEPARSER_H
#define FRAMEPARSER_H

#include <QByteArray>

#include "frame.h"

class FrameParser
{
public:
  FrameParser();
  QByteArray parse(Frame*);
};

#endif // FRAMEPARSER_H
