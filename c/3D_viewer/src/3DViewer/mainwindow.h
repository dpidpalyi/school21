#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qgifimage.h>

#include <QDateTime>
#include <QMainWindow>

#include "oglwidget.h"
#include "qgifglobal.h"

extern "C" {
#include "../lib/s21_3DViewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  OGLWidget *oglwidget;

 public slots:
  void load_settings();
  void save_settings();

 private slots:
  void Button_SelectFile_Pressed();

  void Button_ScreenFile_Pressed();

  void on_Slider_moveX_valueChanged(int value);

  void on_Slider_moveY_valueChanged(int value);

  void on_Slider_moveZ_valueChanged(int value);

  void on_Slider_scale_valueChanged(int value);

  void on_Slider_rotateX_valueChanged(int value);

  void on_Slider_rotateY_valueChanged(int value);

  void on_Slider_rotateZ_valueChanged(int value);

  void on_doubleSpinBox_scale_valueChanged(double arg1);

  void on_Slider_background_valueChanged(int value);

  void on_spinBox_moveX_valueChanged(int arg1);

  void on_spinBox_moveY_valueChanged(int arg1);

  void on_spinBox_moveZ_valueChanged(int arg1);

  void on_spinBox_rotateX_valueChanged(int arg1);

  void on_spinBox_rotateY_valueChanged(int arg1);

  void on_spinBox_rotateZ_valueChanged(int arg1);

  void on_radioButton_solid_clicked();

  void on_radioButton_dashed_clicked();

  void on_Slider_lineSize_valueChanged(int value);

  void on_radioButton_clicked();

  void on_radioButton_central_clicked();

  void on_Slider_lineColor_valueChanged(int value);

  void on_Slider_pointSize_valueChanged(int value);

  void on_radioButton_none_clicked();

  void on_radioButton_circle_clicked();

  void on_radioButton_sqare_clicked();

  void on_Slider_pointColor_valueChanged(int value);

  void Button_Gif_Pressed();

  void gif();

  void on_button_JPG_2_clicked();

  void on_button_JPG_3_clicked();

  void on_button_JPG_4_clicked();

 private:
  Ui::MainWindow *ui;
  const int FPS = 100;
  double posX = 0.0;
  double posY = 0.0;
  double posZ = 0.0;
  double scale = 1.0;
  double rotX = 0.0;
  double rotY = 0.0;
  double rotZ = 0.0;

  QSettings *settings;
  QString gif_name;
  QGifImage *frame;
  int frames_counter = 0;
  QTimer *timer;
};
#endif  // MAINWINDOW_H
