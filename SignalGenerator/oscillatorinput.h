#ifndef OSCILLATORINPUT_H
#define OSCILLATORINPUT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

class OscillatorInput : public QWidget
{
  Q_OBJECT
private:
  QVBoxLayout* _globalLayout;
  QFormLayout* _inputLayout;
  QHBoxLayout*  _buttonLayout;
  QLabel* _frequencyLabel; QLineEdit* _frequencyInput;
  QPushButton* _startButton;
  QPushButton* _stopButton;
public:
  explicit OscillatorInput(QWidget *parent = nullptr);

signals:
  void oscillatorStarted();
  void oscillatorStoped();
private slots:
  void _start();
  void _stop();
};

#endif // OSCILLATORINPUT_H
