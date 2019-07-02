#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include <QTabWidget>

#include "serverdatainput.h"
#include "channeldatainput.h"
#include "oscillatorinput.h"
#include "sinusoscillatorinput.h"

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
  SinusOscillatorInput* _sinusOscillatorInput;

  QTabWidget* _tabWidget;
  QWidget* _connectPage;  QGridLayout* _connectLayout;
  QWidget* _oscillatorPage; QGridLayout* _oscillatorLayout;
};

#endif // MAINWINDOW_H
