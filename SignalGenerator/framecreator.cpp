#include "framecreator.h"

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

  if (frame == nullptr) {
      frame = new Frame();
    }
  frame->points.push_front(QVariant(value));
  if (frame->points.size() < _ch_attr.frameSize) {
      return;
    }

  frame->time = 0;          //Заглушка
  frame->frameNumber = 0;   //Заглушка
  frame->isFloat = true;    //Заглушка
  frame->isComplex = false; //Заглушка
  frame->pointSize = 8;     //Заглушка

  frame->divisionXValue = _ch_attr.divisionXValue;
  frame->divisionYValue = _ch_attr.divisionYValue;
  frame->channelName = _ch_attr.channelName;
  frame->offsetX = _ch_attr.offsetX;
  frame->xMeasure = _ch_attr.xMeasure;
  frame->yMeasure = _ch_attr.yMeasure;

  emit generated(frame);
  delete frame;
}
