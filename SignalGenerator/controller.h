#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "oscillator.h"
#include "framecreator.h"
#include "client.h"

class Controller : public QObject
{
  Q_OBJECT
private:
  QString _filename;
  Oscillator* _sinusOscillator;
  FrameCreator* _frameCreator;
  Client* _client;
public:
  explicit Controller(QString filename, QObject *parent = nullptr);
private slots:
  void receiveFrame(Frame*);
  void handleError(QAbstractSocket::SocketError);
public slots:
  void run();
};

#endif // CONTROLLER_H
