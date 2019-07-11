#include "datadebugger.h"
#include <QDebug>

void DataDebugger::debugData(QByteArray data) {
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
