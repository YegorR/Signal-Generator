#ifndef CHANNELATTRIBUTES_H
#define CHANNELATTRIBUTES_H

#include <QString>

struct ChannelAttributes {
  QString channelName;
  QString xMeasure;
  QString yMeasure;
  float divisionXValue;
  float divisionYValue;
  qint32  offsetX;
  quint32 valuesCount;
};

#endif // CHANNELATTRIBUTES_H
