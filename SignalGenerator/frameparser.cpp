#include "frameparser.h"

#include <QIODevice>
#include <QDataStream>

#include <QDebug>

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

  for(int i = 0; i < frame->points.size();i++) {
      stream << frame->points.at(i).toDouble();
      //stream << static_cast<double>(i);
      //stream << static_cast<quint32>(i);
    }

  stream.device()->seek(0);
  stream << static_cast<quint32>(data.size());
  return data;
}


void writeString(QDataStream& stream, QString& string) {
  int size = string.size();
  QByteArray byteArray = string.toUtf8();
  //qDebug() << size << byteArray << byteArray.toHex();
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
