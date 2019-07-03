#include "configreader.h"

#include <QtXml>
#include <QStack>
#include <QFile>
#include <QtDebug>


ConfigReader::ConfigReader(QString filename) : _filename(filename)
{
}

bool ConfigReader::read() {
  QFile file(_filename);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qCritical() << "File opening error";
      return false;
    }
  QXmlStreamReader xml(&file);

  QStack<QString> nodeName;
  while(!xml.atEnd() && !xml.hasError()) {
      QXmlStreamReader::TokenType token = xml.readNext();
      if (token == QXmlStreamReader::StartDocument) {
          continue;
        }
      if (token == QXmlStreamReader::StartElement) {
          nodeName.push(xml.name().toString());
          continue;
        }
      if (token == QXmlStreamReader::EndElement) {
          nodeName.pop();
          continue;
        }
      if (token == QXmlStreamReader::Characters) {
          QVectorIterator<QString> iter(nodeName);
          QString value = xml.text().toString().trimmed();
          if (value.isEmpty()) {
              continue;
            }
          QString node;
          while(true) {
              node.append(iter.next());
              if (iter.hasNext()) {
                  node.append("/");
                }
              else {
                  break;
                }
            }
          _dict[node] = value.trimmed();
          continue;
        }
    }
  if(xml.hasError()) {
      file.close();
      qCritical() << "XML error" << xml.error() << xml.errorString();
      return false;
    }
  file.close();
  return true;
}


QString ConfigReader::value(QString key) {
  return _dict[key];
}
