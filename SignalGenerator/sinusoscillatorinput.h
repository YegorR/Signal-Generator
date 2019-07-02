#ifndef SINUSOSCILLATORINPUT_H
#define SINUSOSCILLATORINPUT_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QFormLayout>

class SinusOscillatorInput  : public QWidget
{
  Q_OBJECT
private:
  QFormLayout* _layout;
  QLabel* _phaseLabel; QLineEdit* _phaseInput;
  QLabel* _frequencyLabel; QLineEdit* _frequencyInput;
  QLabel* _amplitudeLabel; QLineEdit* _amplitudeInput;
  QDoubleValidator* _validator;
public:
  SinusOscillatorInput(QWidget* parent = nullptr);
signals:
  void sinusAttributesChanged(double phase, double frequency, double amplitude);
public slots:
  void changeSinusAttribute();
};

#endif // SINUSOSCILLATORINPUT_H
