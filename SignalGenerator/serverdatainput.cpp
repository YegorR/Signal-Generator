#include "serverdatainput.h"

ServerDataInput::ServerDataInput(QWidget *parent) : QWidget(parent)
{
  _layout = new QFormLayout(this);
  this->setLayout(_layout);

  _hostLabel = new QLabel("Хост", this);
  _hostInput = new QLineEdit("localhost" , this);
  _layout->addRow(_hostLabel, _hostInput);

  _portLabel = new QLabel("Порт", this);
  _portInput = new QLineEdit("30000", this);
  _layout->addRow(_portLabel, _portInput);

  _portValidator = new QIntValidator(1, 65535);
  _portInput->setValidator(_portValidator);

  _connectButton = new QPushButton("Подключиться" , this);
  _layout->addWidget(_connectButton);
  QObject::connect(_connectButton, SIGNAL(clicked()), this, SLOT(connect()));

  _stopButton = new QPushButton("Отключиться", this);
  _layout->addWidget(_stopButton);
  QObject::connect(_stopButton, SIGNAL(clicked()), this, SLOT(stop()));
  _stopButton->setEnabled(false);
}


void ServerDataInput::connect() {
  _connectButton->setEnabled(false);
  QString host = _hostInput->text().trimmed();
  if (host.isEmpty()) {
      return;
    }
  QString portString = _portInput->text().trimmed();
  if (portString.isEmpty()) {
      return;
    }
  quint16 port = static_cast<quint16>(portString.toInt());
  emit serverDataReceived(host, port);
}

void ServerDataInput::stop() {
  _stopButton->setEnabled(false);
  emit serverStopped();
}

void ServerDataInput::setActive() {
  _stopButton->setEnabled(false);
  _connectButton->setEnabled(true);
}

void ServerDataInput::setDisactive() {
  _stopButton->setEnabled(true);
  _connectButton->setEnabled(false);
}

