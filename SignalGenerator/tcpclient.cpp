#include "tcpclient.h"

TcpClient::TcpClient(QString host, quint16 port, QObject *parent) : Client(host, port, parent)
{
  connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(error(QAbstractSocket::SocketError)));
}

void TcpClient::connectToHost() {
   _socket.connectToHost(host(), port(), QIODevice::WriteOnly);
}

TcpClient::~TcpClient() {
    disconnect(this);
   _socket.disconnectFromHost();
}

void TcpClient::send(QByteArray& data) {
  _socket.write(data);
}

