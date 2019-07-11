#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include "client.h"

#include <QUdpSocket>

class UdpClient : public Client
{
private:
  QUdpSocket _socket;
public:
  UdpClient(QString host, quint16 port, QObject *parent = nullptr);
  void connectToHost();
  void send(QByteArray&);
  ~UdpClient();
};

#endif // UDPCLIENT_H
