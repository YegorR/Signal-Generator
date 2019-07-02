#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setFixedSize(this->geometry().width(), this->geometry().height());

  _layout = new QGridLayout(ui->centralWidget);
  ui->centralWidget->setLayout(_layout);

  _serverDataInput = new ServerDataInput(this);
  _layout->addWidget(_serverDataInput, 0, 0);
  _channelDataInput = new ChannelDataInput(this);
  _layout->addWidget(_channelDataInput, 1, 0);

  _oscillatorInput = new OscillatorInput(this);
  _layout->addWidget(_oscillatorInput, 2, 0);
}

MainWindow::~MainWindow()
{
  delete ui;
}
