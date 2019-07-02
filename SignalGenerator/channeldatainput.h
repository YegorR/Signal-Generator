#ifndef CHANNELDATAINPUT_H
#define CHANNELDATAINPUT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QValidator>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QFormLayout>

#include "channelattributes.h"

class ChannelDataInput : public QWidget
{
  Q_OBJECT
private:
  QLabel* _channelNameLabel; QLineEdit* _channelNameInput;
  QLabel* _xMeasureLabel; QLineEdit* _xMeasureInput;
  QLabel* _yMeasureLabel; QLineEdit* _yMeasureInput;
  QLabel* _divisionXValueLabel; QLineEdit* _divisionXValueInput;
  QLabel* _divisionYValueLabel; QLineEdit* _divisionYValueInput;
  QLabel* _offsetXLabel; QLineEdit* _offsetXInput;
  QLabel* _valuesCountLabel; QLineEdit* _valuesCountInput;
  QFormLayout* _layout;
  QDoubleValidator* _doubleValidator;
  QIntValidator* _int32Validator;

  void _createValidators();
public:
  explicit ChannelDataInput(QWidget *parent = nullptr);

signals:
  void channelDataChanged(ChannelAttributes);
public slots:
  void changeChannelData();
};

#endif // CHANNELDATAINPUT_H
