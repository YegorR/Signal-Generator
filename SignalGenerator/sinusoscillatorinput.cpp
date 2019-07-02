#include "sinusoscillatorinput.h"

SinusOscillatorInput::SinusOscillatorInput(QWidget* parent) : QWidget(parent)
{
  _layout = new QFormLayout(this);
  this->setLayout(_layout);

  _phaseLabel = new QLabel("Фаза", this);
  _phaseInput = new QLineEdit(this);
  _layout->addRow(_phaseLabel, _phaseInput);

  _frequencyLabel = new QLabel("Частота", this);
  _frequencyInput = new QLineEdit(this);
  _layout->addRow(_frequencyLabel, _frequencyInput);

  _amplitudeLabel = new QLabel("Амплитуда", this);
  _amplitudeInput = new QLineEdit(this);
  _layout->addRow(_amplitudeLabel, _amplitudeInput);

  _validator = new QDoubleValidator(this);
  _phaseInput->setValidator(_validator);
  _frequencyInput->setValidator(_validator);
  _amplitudeInput->setValidator(_validator);
}

void SinusOscillatorInput::changeSinusAttribute() {
  double phase = 0;
  if (!_phaseInput->text().trimmed().isEmpty()) {
      phase = _phaseInput->text().toDouble();
    }
  double frequency = 0;
  if (!_frequencyInput->text().trimmed().isEmpty()) {
      frequency = _frequencyInput->text().toDouble();
    }
  double amplitude = 0;
  if (!_amplitudeInput->text().trimmed().isEmpty()) {
      amplitude = _amplitudeInput->text().toDouble();
    }
  emit sinusAttributesChanged(phase, frequency, amplitude);
}
