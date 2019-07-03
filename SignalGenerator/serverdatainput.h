#ifndef SERVERDATAINPUT_H
#define SERVERDATAINPUT_H

#include <QWidget>
#include <QLineEdit>
#include <QIntValidator>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>

class ServerDataInput : public QWidget
{
  Q_OBJECT
private:
  QLineEdit* _hostInput;
  QLineEdit* _portInput;
  QLabel* _hostLabel;
  QLabel* _portLabel;
  QIntValidator* _portValidator;
  QFormLayout* _layout;
  QPushButton* _connectButton;
  QPushButton* _stopButton;
public:
  explicit ServerDataInput(QWidget *parent = nullptr);
  void setActive();
  void setDisactive();
signals:
  void serverDataReceived(QString host, quint16 port);
  void serverStopped();
private slots:
  void connect();
  void stop();
};

#endif // SERVERDATAINPUT_H
