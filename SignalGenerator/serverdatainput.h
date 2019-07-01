#ifndef SERVERDATAINPUT_H
#define SERVERDATAINPUT_H

#include <QWidget>
#include <QLineEdit>
#include <QIntValidator>
#include <QFormLayout>
#include <QLabel>

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
public:
  explicit ServerDataInput(QWidget *parent = nullptr);

signals:
  void serverDataReceived(QString host, quint16 port);
public slots:
  void connect();
};

#endif // SERVERDATAINPUT_H
