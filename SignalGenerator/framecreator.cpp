#include "framecreator.h"

#include <QDebug>

FrameCreator::FrameCreator(ChannelAttributes ch_attr, QObject *parent) : QObject(parent),
  _ch_attr(ch_attr)
{

}

void FrameCreator::setOscillator(Oscillator *oscillator) {
  if (_oscillator != nullptr) {
      disconnect(oscillator);
    }
   _oscillator = oscillator;
   connect(oscillator, SIGNAL(generated(double)), this, SLOT(receiveValue(double)));
   if (frame != nullptr) {
       delete frame;
     }
}

void FrameCreator::setChannelAttributes(ChannelAttributes ch_attr) {
  _ch_attr = ch_attr;
  if (frame != nullptr) {
      delete frame;
    }
}


void FrameCreator::receiveValue(double value) {
  static Frame* frame = nullptr;
  static bool isSend = true;
  if (isSend) {
      frame = new Frame();
      isSend = false;
    }
  frame->points.push_back(QVariant(value));
  if (frame->points.size() < static_cast<int>(_ch_attr.valuesCount)) {
      return;
    }

  frame->time = 1;          //Заглушка
  frame->frameNumber = 10;   //Заглушка
  frame->isFloat = _ch_attr.isFloat;
  frame->isComplex = _ch_attr.isComplex;
  frame->pointSize = _ch_attr.pointSize;

  frame->divisionXValue = _ch_attr.divisionXValue;
  frame->divisionYValue = _ch_attr.divisionYValue;
  frame->channelName = _ch_attr.channelName;
  //frame->offsetX = _ch_attr.offsetX;
  frame->offsetX = 0;
  frame->xMeasure = _ch_attr.xMeasure;
  frame->yMeasure = _ch_attr.yMeasure;

  qDebug() << "frame is created";
  emit generated(frame);
  isSend = true;
}
