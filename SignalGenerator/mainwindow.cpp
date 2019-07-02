#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setFixedSize(this->geometry().width(), this->geometry().height());

//  _layout = new QGridLayout(ui->centralWidget);
//  ui->centralWidget->setLayout(_layout);

//  _serverDataInput = new ServerDataInput(this);
//  _layout->addWidget(_serverDataInput, 0, 0);
//  _channelDataInput = new ChannelDataInput(this);
//  _layout->addWidget(_channelDataInput, 1, 0);

//  _oscillatorInput = new OscillatorInput(this);
//  _layout->addWidget(_oscillatorInput, 2, 0);

//  _sinusOscillatorInput = new SinusOscillatorInput(this);
//  _layout->addWidget(_sinusOscillatorInput, 3, 0);

  _tabWidget = new QTabWidget(ui->centralWidget);
  _layout = new QGridLayout(ui->centralWidget);
  ui->centralWidget->setLayout(_layout);
  _layout->addWidget(_tabWidget);

  _oscillatorPage = new QWidget();
  _connectPage = new QWidget();

  _oscillatorInput = new OscillatorInput(_oscillatorPage);
  _sinusOscillatorInput = new SinusOscillatorInput(_oscillatorPage);
  _oscillatorLayout = new QGridLayout(_oscillatorPage);
  _oscillatorPage->setLayout(_oscillatorLayout);
  _oscillatorLayout->addWidget(_oscillatorInput);
  _oscillatorLayout->addWidget(_sinusOscillatorInput);

  _connectLayout = new QGridLayout(_connectPage);
  _connectPage->setLayout(_connectLayout);
  _serverDataInput = new ServerDataInput(_connectPage);
  _connectLayout->addWidget(_serverDataInput);

  _tabWidget->addTab(_connectPage, "Подключение");
  _tabWidget->addTab(_oscillatorPage, "Осциллятор");

}

MainWindow::~MainWindow()
{
  delete ui;
}
