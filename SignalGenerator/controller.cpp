#include "controller.h"
#include "configreader.h"
#include "sinusoscillator.h"
#include "channelattributes.h"
#include "tcpclient.h"
#include "frameparser.h"

#include <QDebug>
#include <QThread>

void setType(QString type, ChannelAttributes& ch_attr);
void setChannelAttributes(ConfigReader& configReader, ChannelAttributes& ch_attr);

Controller::Controller(QString filename, QObject *parent) : QObject(parent), _filename(filename)
{

}

void Controller::run() {
  ConfigReader configReader(_filename);
  if (!configReader.read()) {
      qCritical()  << "Reading error\n";
      return;
    }

  unsigned long milliSampling = configReader.value("config/sampling_period_milli").toULong();
  unsigned long nanoSampling = configReader.value("config/sampling_period_nano").toULong();

  double phase = configReader.value("config/sinus_oscillator/phase").toDouble();
  double frequency = configReader.value("config/sinus_oscillator/frequency").toDouble();
  double amplitude = configReader.value("config/sinus_oscillator/amplitude").toDouble();
  double deltaPhase = configReader.value("config/sinus_oscillator/delta_phase").toDouble();
  uint deltaPeriod = configReader.value("config/sinus_oscillator/delta_period").toUInt();

  _sinusOscillator = new SinusOscillator(phase, frequency, amplitude, deltaPhase, deltaPeriod, this);
  _sinusOscillator->setMilliPeriod(milliSampling);
  _sinusOscillator->setNanoPeriod(nanoSampling);

  ChannelAttributes ch_attr;
  setChannelAttributes(configReader, ch_attr);

  QString random = configReader.value("config/random_frame_order");
  bool is_random = (random == "true") ? true : false;

  _frameCreator = new FrameCreator(ch_attr, is_random, this);
  _frameCreator->setOscillator(_sinusOscillator);

  QString host = configReader.value("config/host");
  quint16 port = static_cast<quint16>(configReader.value("config/port").toUInt());

  _client = new TcpClient(host, port, this);
  connect(_client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handleError(QAbstractSocket::SocketError)));
  connect(_frameCreator, SIGNAL(generated(Frame*)), this, SLOT(receiveFrame(Frame*)));
  _client->connectToHost();
  _sinusOscillator->start();
}

void Controller::receiveFrame(Frame* frame) {
  qDebug()  << "Frame is received";
  QByteArray data = FrameParser::parse(frame);
  _client->send(data);
  QThread::sleep(1);
  delete frame;
}

void Controller::handleError(QAbstractSocket::SocketError error) {
  qCritical() << "Socket error:" << error;
}


void setType(QString type, ChannelAttributes& ch_attr) {
  if (type == "float") {
      ch_attr.isFloat = true;
      ch_attr.pointSize = 4;
    } else if (type == "double") {
      ch_attr.isFloat = true;
      ch_attr.pointSize = 8;
    } else if (type == "int8") {
      ch_attr.isFloat = false;
      ch_attr.pointSize = 1;
    } else if (type == "int16") {
      ch_attr.isFloat = false;
      ch_attr.pointSize = 2;
    } else if (type == "int32") {
      ch_attr.isFloat = false;
      ch_attr.pointSize = 4;
    } else if (type == "int64") {
      ch_attr.isFloat = false;
      ch_attr.pointSize = 8;
    }
}


void setChannelAttributes(ConfigReader& configReader, ChannelAttributes& ch_attr) {
  ch_attr.channelName = configReader.value("config/channel_name");
  ch_attr.xMeasure = configReader.value("config/x_measure");
  ch_attr.yMeasure = configReader.value("config/y_measure");
  ch_attr.divisionXValue = configReader.value("config/division_x_value").toFloat();
  qDebug() << ch_attr.divisionXValue;
  ch_attr.divisionYValue = configReader.value("config/division_y_value").toFloat();
  ch_attr.valuesCount = static_cast<quint32>(configReader.value("config/values_count").toInt());
  ch_attr.frameValuesCount = static_cast<quint32>(configReader.
                                                  value("config/frame_values_count").toInt());
  ch_attr.offsetX = static_cast<qint32>(configReader.value("config/offset_x").toInt());

  setType(configReader.value("config/type"), ch_attr);
}
