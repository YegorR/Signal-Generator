#include "channeldatainput.h"


ChannelDataInput::ChannelDataInput(QWidget *parent) : QWidget(parent)
{
  _layout = new QFormLayout(this);
  this->setLayout(_layout);
  _createValidators();

  _channelNameLabel = new QLabel("Имя канала", this);
  _channelNameInput = new QLineEdit(this);
  _layout->addRow(_channelNameLabel, _channelNameInput);

  _xMeasureLabel = new QLabel("Единица измерения оси X", this);
  _xMeasureInput = new QLineEdit(this);
  _layout->addRow(_xMeasureLabel, _xMeasureInput);

  _yMeasureLabel = new QLabel("Единица измерения оси Y", this);
  _yMeasureInput = new QLineEdit(this);
  _layout->addRow(_yMeasureLabel, _yMeasureInput);

  _divisionXValueLabel = new QLabel("Цена деления оси X", this);
  _divisionXValueInput = new QLineEdit(this);
  _layout->addRow(_divisionXValueLabel, _divisionXValueInput);
  _divisionXValueInput->setValidator(_doubleValidator);

  _divisionYValueLabel = new QLabel("Цена деления оси Y", this);
  _divisionYValueInput = new QLineEdit(this);
  _layout->addRow(_divisionYValueLabel, _divisionYValueInput);
  _divisionYValueInput->setValidator(_doubleValidator);

  _offsetXLabel = new QLabel("Смещение по оси X", this);
  _offsetXInput = new QLineEdit(this);
  _layout->addRow(_offsetXLabel, _offsetXInput);
  _offsetXInput->setValidator(_int32Validator);

  _valuesCountLabel = new QLabel("Количество отсчётов в кадре", this);
  _valuesCountInput = new QLineEdit(this);
  _layout->addRow(_valuesCountLabel, _valuesCountInput);
  _valuesCountInput->setValidator(_int32Validator);
}


void ChannelDataInput::_createValidators() {
  _doubleValidator = new QDoubleValidator(this);
  _doubleValidator->setBottom(0);

  _int32Validator = new QIntValidator(this);
}


void ChannelDataInput::changeChannelData() {
  ChannelAttributes ch_attr;
  ch_attr.channelName = _channelNameInput->text();
  ch_attr.xMeasure = _xMeasureInput->text();
  ch_attr.yMeasure = _yMeasureInput->text();

  _divisionXValueInput->text().trimmed().isEmpty() ? ch_attr.divisionXValue = 0
      : ch_attr.divisionXValue = _divisionXValueInput->text().toFloat();
  _divisionYValueInput->text().trimmed().isEmpty() ? ch_attr.divisionYValue = 0
      : ch_attr.divisionYValue = _divisionYValueInput->text().toFloat();
  _offsetXInput->text().isEmpty() ? ch_attr.offsetX = 0
      : ch_attr.offsetX = static_cast<qint32>(_offsetXInput->text().toInt());
  _valuesCountInput->text().trimmed().isEmpty() ? ch_attr.valuesCount  = 0
      : ch_attr.valuesCount = static_cast<quint8>(_valuesCountInput->text().toInt());
  emit channelDataChanged(ch_attr);
}
