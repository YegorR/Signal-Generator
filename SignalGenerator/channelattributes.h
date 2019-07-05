#ifndef CHANNELATTRIBUTES_H
#define CHANNELATTRIBUTES_H

#include <QString>

struct ChannelAttributes {
  QString channelName;
  QString xMeasure;
  QString yMeasure;
  float divisionXValue = 1;
  float divisionYValue = 1;
  qint32  offsetX = 0;
  quint32 valuesCount = 100;
  quint32 frameValuesCount = 100;
  bool isFloat = false;
  bool isComplex = false;
  quint8 pointSize = 4;
};

#endif // CHANNELATTRIBUTES_H
