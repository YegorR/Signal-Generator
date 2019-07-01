#ifndef FRAMECREATOR_H
#define FRAMECREATOR_H

#include <QObject>

#include "oscillator.h"
#include "frame.h"
#include "channelattributes.h"

class FrameCreator : public QObject
{
  Q_OBJECT
private:
  Oscillator* _oscillator = nullptr;
  ChannelAttributes _ch_attr;
  Frame* frame = nullptr;
public:
  explicit FrameCreator(ChannelAttributes ch_attr ,QObject *parent = nullptr);
  void setOscillator(Oscillator* oscillator);
  void setChannelAttributes(ChannelAttributes ch_attr);
signals:
  void generated(Frame*);
private slots:
  void receiveValue(double);
};

#endif // FRAMECREATOR_H
