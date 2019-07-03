#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <QString>
#include <QMap>
#include <QXmlStreamReader>

class ConfigReader
{
private:
  QMap<QString, QString> _dict;
  QString _filename;
public:
  ConfigReader(QString filename);
  bool read();
  QString value(QString key);
};

#endif // CONFIGREADER_H
