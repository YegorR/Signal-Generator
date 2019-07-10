#include "tcpclient.h"
#include <QDebug>
#include <QMutex>

void debugData(QByteArray data);

TcpClient::TcpClient(QString host, quint16 port, QObject *parent) : Client(host, port, parent)
{
  connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(error(QAbstractSocket::SocketError)));
}

void TcpClient::connectToHost() {
   _socket.connectToHost(host(), port(), QIODevice::WriteOnly);
   if (!_socket.waitForConnected(1000 * 3)) {
       qDebug() << "No connect!";
     } else {
       qDebug() << "Successful connect!";
    }
}

TcpClient::~TcpClient() {
    disconnect(this);
   _socket.disconnectFromHost();
}

void TcpClient::send(QByteArray& data) {
  debugData(data);
  _socket.write(data);
  _socket.flush();
}



void debugData(QByteArray data) {
  data = data.toHex();
  qDebug() << "===============================================================";
  QString line;
  for (auto i = 0; i < data.size(); ++i) {
      line += data[i];
      if ((i + 1) % 8 == 0) {
          qDebug() << line;
          line.clear();
        }
    }
  if (!line.isEmpty()) {
      qDebug() << line;
    }
}
