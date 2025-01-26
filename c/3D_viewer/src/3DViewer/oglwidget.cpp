#include "oglwidget.h"

#include "mainwindow.h"

extern "C" {
#include "../lib/s21_3DViewer.h"
};

OGLWidget::OGLWidget(QWidget *parent) : QOpenGLWidget{parent} {}
void OGLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

int OGLWidget::Allocate() {
  clearData();
  int result = 0;
  result =
      s21_parse_file((char *)findFile.toStdString().c_str(), &(this->data));
  if (result == 0) {
    move_x(&data.matrix_3d, 0 - (data.mn[0] + (data.mx[0] - data.mn[0]) / 2.0));
    move_y(&data.matrix_3d, 0 - (data.mn[1] + (data.mx[1] - data.mn[1]) / 2.0));
    move_z(&data.matrix_3d, 0 - (data.mn[2] + (data.mx[2] - data.mn[2]) / 2.0));
    double scale = 1 / max_scale(&data);
    scale_all(&data.matrix_3d, scale, scale, scale);
    update();
  }
  return result;
}

double OGLWidget::max_scale(Data *data) {
  double res = DBL_MIN, temp;
  for (int i = 0; i < 3; ++i) {
    temp = data->mx[i] - data->mn[i];
    if (temp > res) res = temp;
  }
  return res;
}

void OGLWidget::paintGL() {
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);

  // styles
  glLineWidth(lineSize);
  glPointSize(pointSize);
  glColor3f(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
  if (lineType) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  if (pointType == 1) {
    glEnable(GL_POINT_SMOOTH);
  } else if (pointType == 2) {
    glDisable(GL_POINT_SMOOTH);
  }
  if (perspective)
    glFrustum(-1, 1, -1.0, 1.0, 1.0, 100.0);
  else
    glOrtho(-2, 2, -1, 1, -10, 10);
  //  glOrtho(-(float)width() / height(),
  //    (float)width() / height(), -1, 1, -10, 10);

  for (int i = 1; i < data.count_of_facets + 1; i++) {
    for (int v = 0; v < data.polygons[i].number_of_vertexes_in_facets; v++) {
      int vertex = data.polygons[i].vertexes[v];
      x = data.matrix_3d.matrix[vertex][0];
      y = data.matrix_3d.matrix[vertex][1];
      z = data.matrix_3d.matrix[vertex][2];

      glBegin(GL_LINE_LOOP);
      glVertex3f(x, y, z);
    }
    glEnd();
  }
  if (pointType) {
    glColor3d(pointColor.redF(), pointColor.greenF(), pointColor.blueF());
    for (int i = 1; i < data.count_of_facets + 1; i++) {
      for (int v = 0; v < data.polygons[i].number_of_vertexes_in_facets; v++) {
        int vertex = data.polygons[i].vertexes[v];
        x = data.matrix_3d.matrix[vertex][0];
        y = data.matrix_3d.matrix[vertex][1];
        z = data.matrix_3d.matrix[vertex][2];

        glEnable(GL_BLEND);
        glBegin(GL_POINTS);
        glVertex3d(x, y, z);
      }
    }
    glEnd();
  }
}

void OGLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

inline void OGLWidget::qColorToRGB(const QColor &C, float &r, float &g,
                                   float &b) const {
  int red = C.red();
  int green = C.green();
  int blue = C.blue();
  r = normalize_0_1(red, RGB_MIN, RGB_MAX);
  g = normalize_0_1(green, RGB_MIN, RGB_MAX);
  b = normalize_0_1(blue, RGB_MIN, RGB_MAX);
}

inline float OGLWidget::normalize_0_1(float val, float min, float max) const {
  return (val - min) / (max - min);
}

void OGLWidget::moveAll(double x, double y, double z) {
  move_all(&data.matrix_3d, x, y, z);
  update();
}

void OGLWidget::scale(double x) {
  scale_all(&data.matrix_3d, x, x, x);
  update();
}

void OGLWidget::rotateX(double x) {
  rotation_x(&data.matrix_3d, x);
  update();
}

void OGLWidget::rotateY(double y) {
  rotation_y(&data.matrix_3d, y);
  update();
}

void OGLWidget::rotateZ(double z) {
  rotation_z(&data.matrix_3d, z);
  update();
}

void OGLWidget::clearData() {
  if (data.polygons != NULL || data.matrix_3d.matrix != NULL) {
    s21_remove_model(&data);
    data = {0};
    // qDebug() << "inside free";
  }
}
