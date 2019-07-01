#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QAbstractSocket>

class Client : public QObject
{
  Q_OBJECT
  QString _host;
  quint16 _port;
public:
  explicit Client(QString host, quint16 port, QObject *parent = nullptr);
  virtual void connectToHost() = 0;
  virtual void send(QByteArray&) = 0;
protected:
  QString host();
  quint16 port();
signals:
  void error(QAbstractSocket::SocketError);
};

#endif // CLIENT_H
