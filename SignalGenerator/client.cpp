#include "client.h"

Client::Client(QString host, quint16 port, QObject *parent) : QObject(parent),
  _host(host), _port(port)
{

}

quint16 Client::port() {
  return _port;
}

QString Client::host() {
  return _host;
}
