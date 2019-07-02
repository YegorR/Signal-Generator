#include "oscillatorinput.h"

OscillatorInput::OscillatorInput(QWidget *parent) : QWidget(parent)
{
  _globalLayout = new QVBoxLayout(this);
  setLayout(_globalLayout);
  _inputLayout = new QFormLayout();
  _globalLayout->addLayout(_inputLayout);
  _buttonLayout = new QHBoxLayout();
  _globalLayout->addLayout(_buttonLayout);

  _frequencyLabel = new QLabel("Частота дискретизации", this);
  _frequencyInput = new QLineEdit(this);
  _inputLayout->addRow(_frequencyLabel, _frequencyInput);

  _startButton = new QPushButton("Старт", this);
  _stopButton = new QPushButton("Стоп", this);
  _buttonLayout->addWidget(_startButton);
  _buttonLayout->addWidget(_stopButton);

  connect(_startButton, SIGNAL(clicked()), this, SLOT(_start()));
  connect(_stopButton, SIGNAL(clicked()), this, SLOT(_stop()));

 _stopButton->setEnabled(false);
}

void OscillatorInput::_start() {
  _startButton->setEnabled(false);
  _stopButton->setEnabled(true);
  emit oscillatorStarted();
}

void OscillatorInput::_stop() {
  _startButton->setEnabled(true);
  _stopButton->setEnabled(false);
  emit oscillatorStoped();
}
