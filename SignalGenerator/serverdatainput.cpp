#include "serverdatainput.h"

ServerDataInput::ServerDataInput(QWidget *parent) : QWidget(parent)
{
  _layout = new QFormLayout(this);
  this->setLayout(_layout);

  _hostLabel = new QLabel("Хост", this);
  _hostInput = new QLineEdit(this);
  _layout->addRow(_hostLabel, _hostInput);

  _portLabel = new QLabel("Порт", this);
  _portInput = new QLineEdit(this);
  _layout->addRow(_portLabel, _portInput);

  _portValidator = new QIntValidator(1, 65535);
  _portInput->setValidator(_portValidator);
}


void ServerDataInput::connect() {
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
