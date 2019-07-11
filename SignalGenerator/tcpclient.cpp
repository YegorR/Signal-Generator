#include "tcpclient.h"
#include <datadebugger.h>
#include <QDebug>


TcpClient::TcpClient(QString host, quint16 port, QObject *parent) : Client(host, port, parent)
{
  connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(error(QAbstractSocket::SocketError)));
}

void TcpClient::connectToHost() {
   _socket.connectToHost(host(), port(), QIODevice::WriteOnly);
     if (!_socket.waitForConnected(1000 * 3)) {
         qDebug() << "TCP_client: No connect!";
       } else {
         qDebug() << "TCP_client: Successful connect!";
      }
}

TcpClient::~TcpClient() {
    disconnect(this);
   _socket.disconnectFromHost();
}

void TcpClient::send(QByteArray& data) {
  DataDebugger::debugData(data);
  _socket.write(data);
  _socket.flush();
}

