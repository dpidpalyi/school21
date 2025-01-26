#include "mainwindow.h"

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QIntValidator>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  oglwidget = new OGLWidget;
  timer = new QTimer(0);

  connect(ui->button_selectFile, SIGNAL(pressed()), this,
          SLOT(Button_SelectFile_Pressed()));
  connect(ui->button_JPG, SIGNAL(pressed()), this,
          SLOT(Button_ScreenFile_Pressed()));
  connect(ui->button_BPM, SIGNAL(pressed()), this,
          SLOT(Button_ScreenFile_Pressed()));
  connect(ui->button_GIF, SIGNAL(pressed()), this, SLOT(Button_Gif_Pressed()));
  connect(timer, SIGNAL(timeout()), this, SLOT(gif()));
}

MainWindow::~MainWindow() {
  ui->widget->clearData();
  delete oglwidget;
  delete ui;
}

void MainWindow::Button_SelectFile_Pressed() {
  ui->widget->findFile = QFileDialog::getOpenFileName(this, tr("Select a file"),
                                                      QDir::homePath(), tr(""));
  ui->label_fileName->setText("  " + ui->widget->findFile);
  if (!ui->widget->findFile.isEmpty()) {
    if (ui->widget->Allocate()) {
      ui->label_fileName->setText("Error file read");
      ui->widget->data = {0};
    } else {
      ui->doubleSpinBox_scale->setValue(1.0);
      ui->label_edgesCount->setText(QString::number(
          ui->widget->data
              .count_of_facets));  // Кол во вершин в файле (после парсинга)
      ui->label_verticesCount->setText(QString::number(
          ui->widget->data
              .count_of_vertexes));  // Кол во ребер в файле (после парсинга)
    }
  } else {
    ui->label_edgesCount->setText("");
    ui->label_verticesCount->setText("");
  }
}

void MainWindow::Button_ScreenFile_Pressed() {
  QFileDialog fileImg(this);
  QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh.mm.ss");
  ;
  QString name = "Image " + date;
  QString fname = fileImg.getSaveFileName(this, tr("Save a screenshot"), name,
                                          tr("image (*.bmp *.jpeg)"));
  QImage img = ui->widget->grabFramebuffer();
  img.save(fname);
}

void MainWindow::Button_Gif_Pressed() {
  QString date = QDateTime::currentDateTime().toString("yyyy-MM-dd hh.mm.ss");
  ;
  QString name = "GIF " + date + ".gif";
  gif_name = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                          name, tr("gif (*.gif)"));
  ui->button_GIF->setDisabled(true);
  frame = new QGifImage;
  frame->setDefaultDelay(10);
  timer->setInterval(100);
  timer->start();
}

void MainWindow::gif() {
  QImage image = ui->widget->grabFramebuffer();
  // QSize image_size(640, 480);
  QImage scaled_image = image.scaled(640, 480);
  frame->addFrame(scaled_image);
  if (frames_counter == 50) {
    timer->stop();
    frame->save(gif_name);
    frames_counter = 0;
    QMessageBox messageBoxGif;
    messageBoxGif.information(0, "", "Gif saved");
    delete frame;
    ui->button_GIF->setEnabled(true);
  }
  frames_counter++;
}

//
// Start transformations
//
void MainWindow::on_Slider_moveX_valueChanged(int value) {
  double result = (double)value / FPS - posX;
  posX = (double)value / FPS;
  ui->spinBox_moveX->blockSignals(true);
  ui->spinBox_moveX->setValue(value);
  ui->spinBox_moveX->blockSignals(false);
  ui->widget->moveAll(result, 0.0, 0.0);
}

void MainWindow::on_Slider_moveY_valueChanged(int value) {
  double result = (double)value / FPS - posY;
  posY = (double)value / FPS;
  ui->spinBox_moveY->blockSignals(true);
  ui->spinBox_moveY->setValue(value);
  ui->spinBox_moveY->blockSignals(false);
  ui->widget->moveAll(0.0, result, 0.0);
}

void MainWindow::on_Slider_moveZ_valueChanged(int value) {
  double result = (double)value / FPS - posZ;
  posZ = (double)value / FPS;
  ui->spinBox_moveZ->blockSignals(true);
  ui->spinBox_moveZ->setValue(value);
  ui->spinBox_moveZ->blockSignals(false);
  ui->widget->moveAll(0.0, 0.0, result);
}

void MainWindow::on_Slider_scale_valueChanged(int value) {
  double result = (double)value / (FPS * 10.0) / scale;
  scale = (double)value / (FPS * 10.0);
  ui->doubleSpinBox_scale->blockSignals(true);
  ui->doubleSpinBox_scale->setValue(scale);
  ui->doubleSpinBox_scale->blockSignals(false);
  ui->widget->scale(result);
}

void MainWindow::on_Slider_rotateX_valueChanged(int value) {
  double result = (double)value / 100 - rotX;
  rotX = (double)value / 100;
  ui->spinBox_rotateX->blockSignals(true);
  ui->spinBox_rotateX->setValue(value);
  ui->spinBox_rotateX->blockSignals(false);
  ui->widget->rotateX(result);
}

void MainWindow::on_Slider_rotateY_valueChanged(int value) {
  double result = (double)value / 100 - rotY;
  rotY = (double)value / 100;
  ui->spinBox_rotateY->blockSignals(true);
  ui->spinBox_rotateY->setValue(value);
  ui->spinBox_rotateY->blockSignals(false);
  ui->widget->rotateY(result);
}

void MainWindow::on_Slider_rotateZ_valueChanged(int value) {
  double result = (double)value / 100 - rotZ;
  rotZ = (double)value / 100;
  ui->spinBox_rotateZ->blockSignals(true);
  ui->spinBox_rotateZ->setValue(value);
  ui->spinBox_rotateZ->blockSignals(false);
  ui->widget->rotateZ(result);
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1) {
  int res = (int)(arg1 * 1000.0);
  ui->Slider_scale->setSliderPosition(res);
  ui->Slider_scale->setValue(res);
}

void MainWindow::on_spinBox_moveX_valueChanged(int arg1) {
  ui->Slider_moveX->setSliderPosition(arg1);
  ui->Slider_moveX->setValue(arg1);
}

void MainWindow::on_spinBox_moveY_valueChanged(int arg1) {
  ui->Slider_moveY->setSliderPosition(arg1);
  ui->Slider_moveY->setValue(arg1);
}

void MainWindow::on_spinBox_moveZ_valueChanged(int arg1) {
  ui->Slider_moveZ->setSliderPosition(arg1);
  ui->Slider_moveZ->setValue(arg1);
}

void MainWindow::on_spinBox_rotateX_valueChanged(int arg1) {
  ui->Slider_rotateX->setSliderPosition(arg1);
  ui->Slider_rotateX->setValue(arg1);
}

void MainWindow::on_spinBox_rotateY_valueChanged(int arg1) {
  ui->Slider_rotateY->setSliderPosition(arg1);
  ui->Slider_rotateY->setValue(arg1);
}

void MainWindow::on_spinBox_rotateZ_valueChanged(int arg1) {
  ui->Slider_rotateZ->setSliderPosition(arg1);
  ui->Slider_rotateZ->setValue(arg1);
}
//
// End transformations
//

void MainWindow::load_settings() {
  QFile file("settings.json");

  if (file.open(QIODevice::ReadOnly)) {
    QByteArray settings = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(settings);

    if (!doc.isNull() && doc.isObject()) {
      QJsonObject obj = doc.object();

      if (obj.contains("perspective") && obj["perspective"].toBool()) {
        ui->radioButton_central->setChecked(true);
        ui->widget->perspective = true;
      } else
        ui->radioButton->setChecked(true);
      if (obj.contains("lineType") && obj["lineType"].toBool()) {
        ui->radioButton_dashed->setChecked(true);
        ui->widget->lineType = true;
      } else
        ui->radioButton_solid->setChecked(true);
      if (obj.contains("lineSize")) {
        ui->widget->lineSize = obj["lineSize"].toDouble();
        ui->Slider_lineSize->setValue(ui->widget->lineSize);
      }
      if (obj.contains("lineColor")) {
        if (QColor::isValidColor(obj["lineColor"].toString()))
          ui->widget->lineColor = QColor(obj["lineColor"].toString());
      }
      if (obj.contains("pointType")) {
        ui->widget->pointType = obj["pointType"].toInt();
        if (ui->widget->pointType == 0)
          ui->radioButton_none->setChecked(true);
        else if (ui->widget->pointType == 1)
          ui->radioButton_circle->setChecked(true);
        else
          ui->radioButton_sqare->setChecked(true);
      }
      if (obj.contains("pointSize")) {
        ui->widget->pointSize = obj["pointSize"].toDouble();
        ui->Slider_pointSize->setValue(ui->widget->pointSize);
      }
      if (obj.contains("pointColor")) {
        if (QColor::isValidColor(obj["pointColor"].toString()))
          ui->widget->pointColor = QColor(obj["pointColor"].toString());
      }
      if (obj.contains("backgroundColor")) {
        if (QColor::isValidColor(obj["backgroundColor"].toString()))
          ui->widget->backgroundColor =
              QColor(obj["backgroundColor"].toString());
      }
    }
    file.close();
  }
}

void MainWindow::save_settings() {
  QJsonObject obj;

  if (ui->radioButton_central->isChecked()) obj["perspective"] = true;
  if (ui->radioButton_dashed->isChecked()) obj["lineType"] = true;
  obj["lineSize"] = ui->widget->lineSize;
  obj["lineColor"] = ui->widget->lineColor.name(QColor::HexArgb);
  obj["pointType"] = ui->widget->pointType;
  obj["pointSize"] = ui->widget->pointSize;
  obj["pointColor"] = ui->widget->pointColor.name(QColor::HexArgb);
  obj["backgroundColor"] = ui->widget->backgroundColor.name(QColor::HexArgb);

  QJsonDocument doc(obj);

  QFile file("settings.json");

  if (file.open(QIODevice::WriteOnly)) {
    file.write(doc.toJson());
    file.close();
  }
}

//
// Start styles
//
void MainWindow::on_Slider_background_valueChanged(int value) {
  ui->widget->backgroundColor.setHsl(value, 100, 100);
  ui->widget->update();
}

void MainWindow::on_radioButton_solid_clicked() {
  ui->widget->lineType = false;
  ui->widget->update();
}

void MainWindow::on_radioButton_dashed_clicked() {
  ui->widget->lineType = true;
  ui->widget->update();
}

void MainWindow::on_Slider_lineSize_valueChanged(int value) {
  ui->widget->lineSize = (float)value;
  ui->widget->update();
}

void MainWindow::on_radioButton_clicked() {
  ui->widget->perspective = false;
  ui->widget->update();
}

void MainWindow::on_radioButton_central_clicked() {
  ui->widget->perspective = true;
  ui->widget->update();
}

void MainWindow::on_Slider_lineColor_valueChanged(int value) {
  ui->widget->lineColor.setHsl(100, 100, value);
  ui->widget->update();
}

void MainWindow::on_Slider_pointSize_valueChanged(int value) {
  ui->widget->pointSize = (float)value;
  ui->widget->update();
}

void MainWindow::on_radioButton_none_clicked() {
  ui->widget->pointType = 0;
  ui->widget->update();
}

void MainWindow::on_radioButton_circle_clicked() {
  ui->widget->pointType = 1;
  ui->widget->update();
}

void MainWindow::on_radioButton_sqare_clicked() {
  ui->widget->pointType = 2;
  ui->widget->update();
}

void MainWindow::on_Slider_pointColor_valueChanged(int value) {
  ui->widget->pointColor.setHsl(100, 100, value);
  ui->widget->update();
}

void MainWindow::on_button_JPG_2_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  ui->widget->lineColor = color;
  ui->widget->update();
}

void MainWindow::on_button_JPG_3_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  ui->widget->backgroundColor = color;
  ui->widget->update();
}

void MainWindow::on_button_JPG_4_clicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose color");
  ui->widget->pointColor = color;
  ui->widget->update();
}
//
// End styles
//
