#include "udpclient.h"
#include "datadebugger.h"
#include <QNetworkDatagram>

UdpClient::UdpClient(QString host, quint16 port, QObject *parent) : Client(host, port, parent)
{
  connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(error(QAbstractSocket::SocketError)));
}


void UdpClient::connectToHost() {
  _socket.connectToHost(host(), port());
  if (!_socket.waitForConnected(1000 * 3)) {
      qDebug() << "UDP_client: No connect!";
    } else {
      qDebug() << "UDP_client: Successful connect!";
   }
}

void UdpClient::send(QByteArray& data) {
  DataDebugger::debugData(data);
  QNetworkDatagram datagram;
  datagram.setData(data);
  _socket.writeDatagram(datagram);
  _socket.flush();
}

UdpClient::~UdpClient() {
  disconnect(this);
 _socket.disconnectFromHost();
}
