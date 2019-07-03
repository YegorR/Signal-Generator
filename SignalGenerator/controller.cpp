#include "controller.h"
#include "configreader.h"
#include "sinusoscillator.h"
#include "channelattributes.h"
#include "tcpclient.h"
#include "frameparser.h"

#include <QDebug>

Controller::Controller(QString filename, QObject *parent) : QObject(parent), _filename(filename)
{

}

void Controller::run() {
  ConfigReader configReader(_filename);
  if (!configReader.read()) {
      qCritical()  << "Reading error\n";
      return;
    }


  double phase = configReader.value("config/sinus_oscillator/phase").toDouble();
  double frequency = configReader.value("config/sinus_oscillator/frequency").toDouble();
  double amplitude = configReader.value("config/sinus_oscillator/amplitude").toDouble();
  double sampling = configReader.value("config/sampling_frequency").toDouble();

  qInfo() << "Sinus Oscillator: phase=" << phase << "frequency=" << frequency <<
             "amplitude="<< amplitude << "sampling=" << sampling;
  _sinusOscillator = new SinusOscillator(phase, frequency, amplitude, this);
  _sinusOscillator->setFrequency(sampling);

  ChannelAttributes ch_attr;
  ch_attr.channelName = configReader.value("config/channel_name");
  ch_attr.xMeasure = configReader.value("config/x_measure");
  ch_attr.yMeasure = configReader.value("config/y_measure");
  ch_attr.divisionXValue = configReader.value("config/division_x_value").toFloat();
  ch_attr.divisionYValue = configReader.value("config/division_y_value").toFloat();
  ch_attr.valuesCount = static_cast<quint8>(configReader.value("config/values_coint").toInt());

  _frameCreator = new FrameCreator(ch_attr, this);
  _frameCreator->setOscillator(_sinusOscillator);

  QString host = configReader.value("config/host");
  quint16 port = static_cast<quint16>(configReader.value("config/port").toUInt());

  _client = new TcpClient(host, port, this);
  connect(_client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
  connect(_frameCreator, SIGNAL(generated(Frame*)), this, SLOT(receiveFrame(Frame*)));
  _client->connectToHost();
}

void Controller::receiveFrame(Frame* frame) {
  QByteArray data = FrameParser::parse(frame);
  _client->send(data);
  delete frame;
}

void Controller::handleError(QAbstractSocket::SocketError error) {
  qCritical() << "Socket error:" << error;
}
