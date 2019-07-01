#include "frameparser.h"

#include <QIODevice>
#include <QDataStream>

void writeString(QDataStream&, QString&);

FrameParser::FrameParser()
{

}

QByteArray FrameParser::parse(Frame* frame) {
  QByteArray data;
  QDataStream stream(&data, QIODevice::WriteOnly);
  stream << static_cast<quint32>(0) << static_cast<quint32>(0) << static_cast<quint16>(0);
  stream << frame->frameNumber;
  stream << static_cast<quint8>(1);
  writeString(stream, frame->channelName);
  writeString(stream, frame->xMeasure);
  writeString(stream, frame->yMeasure);

  stream << frame->divisionXValue;
  stream << frame->divisionYValue;
  stream << static_cast<quint32>(frame->points.size());
  stream << frame->time;
  stream << static_cast<quint8>(0);
  stream << static_cast<quint8>(frame->isComplex);
  stream << static_cast<quint8>(frame->isFloat);

  if (frame->isComplex) {
      stream << static_cast<quint8>(frame->pointSize / 2);
    }
  else {
      stream << frame->pointSize;
    }

  for(int i = 0; i < frame->points.size(); frame->isComplex? i = i + 2 : i++) {
      stream << frame->points.at(i);
      if (frame->isComplex) {
          stream << frame->points.at(i + 1);
        }
    }

  stream.device()->seek(0);
  stream << static_cast<quint32>(data.size());
  return data;
}


void writeString(QDataStream& stream, QString& string) {
  int size = string.size();
  stream << static_cast<quint8>(size);
  stream << string;
  if ((size + 1) % 4 == 0) {
      return;
    }
  for (int i = 0; i < 4 - ((size + 1) % 4); ++i) {
      stream << static_cast<quint8>(0);
    }
}
