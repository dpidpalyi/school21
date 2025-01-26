#include "view.h"

#include "./ui_view.h"
//#include "calc.h"
#include "qcustomplot.h"

s21::View::View(s21::Controller *c, s21::CreditController *cc,
                s21::DepoController *dc, QWidget *parent)
    : controller(c),
      credit_controller(cc),
      depo_controller(dc),
      QMainWindow(parent),
      ui(new Ui::View) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_open, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_close, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(press_lexems()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(press_lexems()));

  ui->dateEdit->setDate(QDate::currentDate());
  ui->dateEdit_add->setDate(QDate::currentDate());
  ui->dateEdit_remove->setDate(QDate::currentDate());
}

s21::View::~View() { delete ui; }

void s21::View::press_lexems() {
  QPushButton *button = (QPushButton *)sender();

  if ((QString::compare(ui->lineEdit_exp->text(), "0", Qt::CaseInsensitive)) ==
      0) {
    ui->lineEdit_exp->setText("");
  }
  QString currentText = ui->lineEdit_exp->text();
  ui->lineEdit_exp->setText(currentText + button->text());
}

void s21::View::on_pushButton_clear_clicked() {
  ui->lineEdit_exp->setText("0");
}

void s21::View::on_pushButton_erase_clicked() {
  QString currentText = ui->lineEdit_exp->text();
  if (!currentText.isEmpty()) {
    currentText.chop(1);
  }
  ui->lineEdit_exp->setText(currentText);
}

void s21::View::on_pushButton_calc_clicked() {
  controller->SetInput(ui->lineEdit_exp->text().toStdString(),
                       ui->lineEdit_var->text().toDouble());
  if (!controller->Calculate()) {
    ui->lineEdit_result->setText(
        QString::number(controller->GetResult(), 'g', 15));
  } else {
    ui->lineEdit_result->setText("Bad input!");
  }
}

void s21::View::on_pushButton_sign_clicked() {
  QString exp = ui->lineEdit_exp->text();
  int lastSignIdx = exp.lastIndexOf("+");
  if (lastSignIdx != -1) {
    exp.replace(lastSignIdx, 1, "-");
  } else {
    lastSignIdx = exp.lastIndexOf("-");
    if (lastSignIdx != -1) {
      exp.replace(lastSignIdx, 1, "+");
    }
  }
  ui->lineEdit_exp->setText(exp);
}

void s21::View::on_pushButton_dot_clicked() {
  QString currentText = ui->lineEdit_exp->text();
  ui->lineEdit_exp->setText(currentText + ui->pushButton_dot->text());
}

void s21::View::on_pushButton_draw_clicked() {
  ui->customPlot->clearGraphs();
  controller->SetInput(ui->lineEdit_copy_exp->text().toStdString(), 0.0);
  controller->SetMinX(ui->lineEdit_xmin->text().toDouble());
  controller->SetMaxX(ui->lineEdit_xmax->text().toDouble());
  controller->SetMinY(ui->lineEdit_ymin->text().toDouble());
  controller->SetMaxY(ui->lineEdit_ymax->text().toDouble());
  if (!controller->FillVectors()) {
    // create graph and assign data to it:
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(
        QVector<double>(controller->GetVectorX().begin(),
                        controller->GetVectorX().end()),
        QVector<double>(controller->GetVectorY().begin(),
                        controller->GetVectorY().end()));
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(controller->GetMinX(),
                                    controller->GetMaxX());
    ui->customPlot->yAxis->setRange(controller->GetMinY(),
                                    controller->GetMaxY());
    ui->customPlot->replot();
  } else {
    ui->lineEdit_copy_exp->setText(ui->lineEdit_copy_exp->text() +
                                   " Bad input!");
  }
}

void s21::View::on_pushButton_copy_exp_clicked() {
  ui->lineEdit_copy_exp->setText(ui->lineEdit_exp->text());
}

void s21::View::on_pushButton_credit_clicked() {
  ui->plainTextEdit_payment->clear();
  ui->lineEdit_overpay->clear();
  ui->lineEdit_total_amount->clear();
  double amount = ui->lineEdit_amount->text().toDouble();
  double rate = ui->lineEdit_rate->text().toDouble();
  int period = ui->lineEdit_period->text().toInt();
  int year = ui->comboBox_period->currentIndex();
  if (credit_controller->SetInput(amount, rate, period, year)) {
    if (ui->comboBox_type->currentIndex() == 0) {
      credit_controller->CreditCalcAnnuitent();
      ui->plainTextEdit_payment->setPlainText(
          QString::number(credit_controller->GetPayment(), 10, 2));
    } else {
      ui->plainTextEdit_payment->clear();
      credit_controller->CreditCalcDifference();
      for (const auto &pay : credit_controller->GetDiffPayments())
        ui->plainTextEdit_payment->appendPlainText(QString::number(pay, 10, 2));
    }
    ui->lineEdit_total_amount->setText(
        QString::number(credit_controller->GetTotalAmount(), 10, 2));
    ui->lineEdit_overpay->setText(
        QString::number(credit_controller->GetOverpay(), 10, 2));
  } else {
    ui->plainTextEdit_payment->setPlainText("Ошибка ввода!");
    ui->lineEdit_total_amount->setText("");
    ui->lineEdit_overpay->setText("");
  }
}

void s21::View::on_pushButton_depo_clicked() {
  double amount = ui->lineEdit_depo_amount->text().toDouble();
  int months = ui->lineEdit_depo_period->text().toInt();
  int year = ui->comboBox_depo_period->currentIndex();
  bool cap = ui->checkBox_capitalize->isChecked();
  int daily = ui->comboBox_pay_period->currentIndex();
  double rate = ui->lineEdit_depo_rate->text().toDouble();
  double free_taxes = ui->lineEdit_taxe_rate->text().toDouble();
  QDate period = ui->dateEdit->date();
  if (depo_controller->SetInput(amount, months, year, cap, daily, rate,
                                free_taxes, period)) {
    depo_controller->DepoCalculate();
    ui->lineEdit_depo_percents->setText(
        QString::number(depo_controller->GetDepoPercents(), 10, 2));
    ui->lineEdit_depo_total_amount->setText(
        QString::number(depo_controller->GetAmount(), 10, 2));
    ui->lineEdit_taxes_amount->setText(
        QString::number(depo_controller->GetTaxTotal(), 10, 2));
  } else {
    ui->lineEdit_depo_total_amount->setText("Ошибка ввода!");
  }
}

void s21::View::on_pushButton_add_plus_clicked() {
  int row = ui->tableWidget_add->rowCount();
  ui->tableWidget_add->insertRow(row);
  ui->tableWidget_add->setItem(
      row, 0,
      new QTableWidgetItem(ui->dateEdit_add->date().toString("dd-MM-yyyy")));
  ui->tableWidget_add->setItem(row, 1,
                               new QTableWidgetItem(ui->lineEdit_add->text()));
  double amount = ui->lineEdit_add->text().toDouble();
  QDate date = ui->dateEdit_add->date();
  depo_controller->DepoAddPush(amount, date);
}

void s21::View::on_pushButton_remove_plus_clicked() {
  int row = ui->tableWidget_remove->rowCount();
  ui->tableWidget_remove->insertRow(row);
  ui->tableWidget_remove->setItem(
      row, 0,
      new QTableWidgetItem(ui->dateEdit_remove->date().toString("dd-MM-yyyy")));
  ui->tableWidget_remove->setItem(
      row, 1, new QTableWidgetItem(ui->lineEdit_remove->text()));
  double amount = ui->lineEdit_remove->text().toDouble();
  QDate date = ui->dateEdit_remove->date();
  depo_controller->DepoRemovePush(amount, date);
}

void s21::View::on_pushButton_add_minus_clicked() {
  int row = ui->tableWidget_add->rowCount();
  if (row > 0) {
    ui->tableWidget_add->removeRow(row - 1);
    depo_controller->DepoAddPop();
  }
}

void s21::View::on_pushButton_remove_minus_clicked() {
  int row = ui->tableWidget_remove->rowCount();
  if (row > 0) {
    ui->tableWidget_remove->removeRow(row - 1);
    depo_controller->DepoRemovePop();
  }
}
