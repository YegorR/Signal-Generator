#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <QTimer>

#include "controller.h"
int main(int argc, char* argv[])
{
  QCoreApplication app(argc, argv);
  if (argc == 1) {
      qCritical() << QString("Input config file name\n");
      return 0;
    }
  QString filename(argv[1]);

  Controller* controller = new Controller(filename, &app);
  qDebug() << sizeof(float);
  QTimer::singleShot(0, controller, SLOT(run()));

  return app.exec();
}
