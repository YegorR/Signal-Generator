#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setFixedSize(this->geometry().width(), this->geometry().height());

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


  _oscillator = new SinusOscillator(0, 100, 15, this);

  QObject::connect(_serverDataInput, SIGNAL(serverDataReceived(QString, quint16)), this, SLOT(connect(QString, quint16)));
  QObject::connect(_oscillatorInput, SIGNAL(oscillatorStarted()), );
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::connect(QString host, quint16 port) {
  _serverDataInput->setDisactive();
  _client = new TcpClient(host, port, this);
  QObject::connect(_client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleConnectionError(QAbstractSocket::SocketError)));
  _client->connectToHost();
}

void MainWindow::handleConnectionError(QAbstractSocket::SocketError error) {
  QMessageBox::warning(this, this->windowTitle(), QString("Ошибка соединения:%1").arg(error));
  disconnect();
}

void MainWindow::disconnect() {
  if (_client != nullptr) {
      delete _client;
    }
  _serverDataInput->setActive();
}
