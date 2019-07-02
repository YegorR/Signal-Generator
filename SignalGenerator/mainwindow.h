#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "serverdatainput.h"
#include "channeldatainput.h"
#include "oscillatorinput.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  QGridLayout* _layout;
  ServerDataInput* _serverDataInput;
  ChannelDataInput* _channelDataInput;
  OscillatorInput* _oscillatorInput;
};

#endif // MAINWINDOW_H
