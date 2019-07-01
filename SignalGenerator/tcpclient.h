#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "client.h"

#include <QTcpSocket>

class TcpClient : public Client
{
  QTcpSocket _socket;
public:
  TcpClient(QString host, quint16 port, QObject *parent = nullptr);
  void connectToHost();
  void send(QByteArray&);
  ~TcpClient();
};

#endif // TCPCLIENT_H
