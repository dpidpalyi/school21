#ifndef OGLWIDGET_H
#define OGLWIDGET_H

extern "C" {
#include "../lib/s21_3DViewer.h"
};

#include <QColor>
#include <QObject>
#include <QOpenGLFunctions>
#include <QtOpenGLWidgets>

#define RGB_MIN 1
#define RGB_MAX 255

class OGLWidget : public QOpenGLWidget, public QOpenGLFunctions {
  Q_OBJECT
 public:
  OGLWidget(QWidget *parent = nullptr);
  void paintGL() override;
  Data data = {0};
  QString findFile;
  QColor backgroundColor;
  bool lineType = false;
  float lineSize = 1;
  float pointSize = 5;
  int pointType = 0;
  QColor pointColor = QColor(255, 0, 0);
  bool perspective = false;
  QColor lineColor = QColor(0, 255, 0);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;

 private:
  void qColorToRGB(const QColor &C, float &r, float &g, float &b) const;
  float normalize_0_1(float val, float min, float max) const;
  QOpenGLShaderProgram *prog = nullptr;
  double x, y, z;
 public slots:
  int Allocate();
  void moveAll(double x, double y, double z);
  void scale(double x);
  void rotateX(double x);
  void rotateY(double y);
  void rotateZ(double z);
  void clearData();
  double max_scale(Data *data);
};

#endif  // OGLWIDGET_H
