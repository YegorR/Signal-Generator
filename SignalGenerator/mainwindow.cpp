#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setFixedSize(this->geometry().width(), this->geometry().height());
  ui->oscillatorTypeChoice->addItem("Синусоида");

  QStringList channelAttributesHeaders;
  channelAttributesHeaders.append("Имя канала");
  channelAttributesHeaders.append("Единица измерения оси X");
  channelAttributesHeaders.append("Единица измерения оси Y");
  channelAttributesHeaders.append("Цена деления оси X");
  channelAttributesHeaders.append("Цена деления оси Y");
  channelAttributesHeaders.append("Смещение по оси X");
  channelAttributesHeaders.append("Размер фрейма");
  ui->channelAttributesTable->setVerticalHeaderLabels(channelAttributesHeaders);

  ui->sinusPhaseInput->setValidator();
}

MainWindow::~MainWindow()
{
  delete ui;
}
