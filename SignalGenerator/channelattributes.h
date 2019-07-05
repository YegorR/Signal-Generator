#ifndef CHANNELATTRIBUTES_H
#define CHANNELATTRIBUTES_H

#include <QString>

struct ChannelAttributes {
  QString channelName;
  QString xMeasure;
  QString yMeasure;
  float divisionXValue;
  float divisionYValue;
  qint32  offsetX = 0;
  quint32 valuesCount;
  bool isFloat = false;
  bool isComplex = false;
  quint8 pointSize = 4;
};

#endif // CHANNELATTRIBUTES_H
