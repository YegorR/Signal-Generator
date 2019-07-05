#include "frameparser.h"

#include <QIODevice>
#include <QDataStream>

#include <QDebug>

void writeString(QDataStream&, QString&);
void defineType(QDataStream& stream, Frame* frame);
template <typename T> void writeValues(QDataStream& stream, Frame* frame);

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
  stream << static_cast<quint32>(0);  //Заглушка
  stream << frame->time;
  stream << static_cast<quint8>(0);
  frame->isComplex ? stream << static_cast<quint8>(1) : stream << static_cast<quint8>(0);
  frame->isFloat ? stream << static_cast<quint8>(1) : stream << static_cast<quint8>(0);

  if (frame->isComplex) {
      stream << static_cast<quint8>(frame->pointSize / 2);
    }
  else {
      stream << frame->pointSize;
    }
   stream.setByteOrder(QDataStream::LittleEndian);

  defineType(stream, frame);

  stream.device()->seek(0);
  stream << static_cast<quint32>(data.size());
  return data;
}


void writeString(QDataStream& stream, QString& string) {
  int size = string.size();
  QByteArray byteArray = string.toUtf8();
  stream << static_cast<quint8>(size);
  for (int i = 0; i < byteArray.size(); ++i) {
      stream << static_cast<quint8>(byteArray.at(i));
    }
  if ((size + 1) % 4 == 0) {
      return;
    }
  for (int i = 0; i < 4 - ((size + 1) % 4); ++i) {
      stream << static_cast<quint8>(0);
    }
}

void defineType(QDataStream& stream, Frame* frame) {
  if (frame->isFloat == true) {
      if (frame->pointSize == 4) {
          writeValues<float>(stream, frame);
        }
      else if (frame->pointSize == 8) {
          writeValues<double>(stream, frame);
        }
    }
  else {
      if (frame->pointSize == 1) {
          writeValues<quint8>(stream, frame);
        }
      else if (frame->pointSize == 2) {
          writeValues<quint16>(stream, frame);
        }
      else if (frame->pointSize == 4) {
          writeValues<quint32>(stream, frame);
        }
      else if (frame->pointSize == 8) {
          writeValues<quint64>(stream, frame);
        }
    }
}

template<typename T>
void writeValues(QDataStream& stream, Frame* frame) {
  for(int i = 0; i < frame->points.size();i++) {
      stream << static_cast<T>(frame->points.at(i).toDouble());
    }
}
