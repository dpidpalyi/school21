#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.load_settings();
  w.show();
  QObject::connect(&a, &QCoreApplication::aboutToQuit, &w,
                   &MainWindow::save_settings);
  return a.exec();
}
