#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "calc.h"
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
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

MainWindow::~MainWindow() { delete ui; }

void MainWindow::press_lexems() {
  QPushButton *button = (QPushButton *)sender();

  if ((QString::compare(ui->lineEdit_exp->text(), "0", Qt::CaseInsensitive)) ==
      0) {
    ui->lineEdit_exp->setText("");
  }
  QString currentText = ui->lineEdit_exp->text();
  ui->lineEdit_exp->setText(currentText + button->text());
}

void MainWindow::on_pushButton_clear_clicked() {
  ui->lineEdit_exp->setText("0");
}

void MainWindow::on_pushButton_erase_clicked() {
  QString currentText = ui->lineEdit_exp->text();
  if (!currentText.isEmpty()) {
    currentText.chop(1);
  }
  ui->lineEdit_exp->setText(currentText);
}

void MainWindow::on_pushButton_calc_clicked() {
  QString exp = ui->lineEdit_exp->text();
  QByteArray byteExp = exp.toLatin1();
  char *ptr = byteExp.data();
  stack *rpn = init();
  int err = parse(ptr, rpn);
  if (!err) {
    double res = 0;
    err = eval(rpn, &res, ui->lineEdit_var->text().toDouble());
    if (!err) {
      ui->lineEdit_result->setText(QString::number(res, 'g', 15));
    } else {
      ui->lineEdit_result->setText("Bad input!");
    }
  } else {
    ui->lineEdit_result->setText("Bad input!");
  }
  destroy_stack(rpn);
  free(rpn);
}

void MainWindow::on_pushButton_sign_clicked() {
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

void MainWindow::on_pushButton_dot_clicked() {
  QString currentText = ui->lineEdit_exp->text();
  ui->lineEdit_exp->setText(currentText + ui->pushButton_dot->text());
}

void MainWindow::on_pushButton_draw_clicked() {
  QString exp = ui->lineEdit_copy_exp->text();
  QByteArray byteExp = exp.toLatin1();
  char *ptr = byteExp.data();
  stack *rpn = init();
  int err = parse(ptr, rpn);
  ui->customPlot->clearGraphs();
  if (!err) {
    stack *copy = init();
    double temp_y;
    double xmin = ui->lineEdit_xmin->text().toDouble();
    double xmax = ui->lineEdit_xmax->text().toDouble();
    double ymin = ui->lineEdit_ymin->text().toDouble();
    double ymax = ui->lineEdit_ymax->text().toDouble();
    QVector<double> x(101), y(101);
    if (xmin < xmax) {
      for (int i = 0; i < 101; ++i) {
        x[i] = xmin + i * (xmax - xmin) / 100;
        copy_stack(rpn, copy);
        err = eval(copy, &temp_y, x[i]);
        if (!err) {
          y[i] = temp_y;
        }
      }
      // create graph and assign data to it:
      ui->customPlot->addGraph();
      ui->customPlot->graph(0)->setData(x, y);
      // give the axes some labels:
      ui->customPlot->xAxis->setLabel("x");
      ui->customPlot->yAxis->setLabel("y");
      // set axes ranges, so we see all data:
      ui->customPlot->xAxis->setRange(xmin, xmax);
      ui->customPlot->yAxis->setRange(ymin, ymax);
      ui->customPlot->replot();
      destroy_stack(copy);
    }
    free(copy);
  } else {
    ui->lineEdit_copy_exp->setText(ui->lineEdit_copy_exp->text() +
                                   " Bad input!");
  }
  destroy_stack(rpn);
  free(rpn);
}

void MainWindow::on_pushButton_copy_exp_clicked() {
  ui->lineEdit_copy_exp->setText(ui->lineEdit_exp->text());
}

double eval_annuitent_pay(double amount, int period, double rate) {
  double temp = pow(1 + rate, period);
  double payment = (amount * rate * temp) / (temp - 1);
  return payment;
}

void MainWindow::on_pushButton_credit_clicked() {
  ui->plainTextEdit_payment->clear();
  ui->lineEdit_overpay->clear();
  ui->lineEdit_total_amount->clear();
  double amount = ui->lineEdit_amount->text().toDouble();
  int period = ui->lineEdit_period->text().toInt();
  if (ui->comboBox_period->currentIndex() == 0) {
    period *= 12;
  }
  double rate = ui->lineEdit_rate->text().toDouble() / 12.0 / 100.0;
  double pay = 0, overpay = 0, total_amount = 0;
  if (amount > 0 && period > 0 && rate > 0) {
    if (ui->comboBox_type->currentIndex() == 0) {
      pay = eval_annuitent_pay(amount, period, rate);
      total_amount = pay * period;
      ui->plainTextEdit_payment->setPlainText(QString::number(pay, 10, 2));
    } else {
      double remaining = amount, principal_pay = amount / period;
      for (int month = 1; month <= period; month++) {
        pay = principal_pay + remaining * rate;
        total_amount += pay;
        ui->plainTextEdit_payment->appendPlainText(QString::number(pay, 10, 2));
        remaining -= principal_pay;
      }
    }
    overpay = total_amount - amount;
    ui->lineEdit_total_amount->setText(QString::number(total_amount, 10, 2));
    ui->lineEdit_overpay->setText(QString::number(overpay, 10, 2));
  } else {
    ui->plainTextEdit_payment->setPlainText("Ошибка ввода!");
    ui->lineEdit_total_amount->setText("");
    ui->lineEdit_overpay->setText("");
  }
}

double without_capitalize(double amount, double rate, int days) {
  return amount * rate * days / 365;
}

double capitalize_daily(double amount, double rate, int days) {
  return amount * pow(1 + rate / 365, days) - amount;
}

double capitalize_monthly(double amount, double rate, int days) {
  return amount * pow(1 + rate / 12, days / 29.3) - amount;
}

void MainWindow::sort_deposits() {
  deposits.clear();
  deposits.reserve(deposits_add.size() + deposits_remove.size());
  deposits.insert(deposits.end(), deposits_add.begin(), deposits_add.end());
  deposits.insert(deposits.end(), deposits_remove.begin(),
                  deposits_remove.end());

  // Отсортируйте по дате (по возрастанию)
  std::sort(deposits.begin(), deposits.end(),
            [](const DepositInfo &info1, const DepositInfo &info2) {
              return info1.date < info2.date;
            });
}

double MainWindow::calc_depo_percents(double amount, double rate, int days) {
  double percents = 0;
  if (ui->checkBox_capitalize->isChecked()) {
    if (ui->comboBox_pay_period->currentIndex() == 0) {
      percents += capitalize_daily(amount, rate, days);
    } else {
      percents += capitalize_monthly(amount, rate, days);
    }
  } else {
    percents += without_capitalize(amount, rate, days);
  }

  return percents;
}

void MainWindow::on_pushButton_depo_clicked() {
  sort_deposits();
  double amount = ui->lineEdit_depo_amount->text().toDouble();
  int months = ui->lineEdit_depo_period->text().toInt();
  if (ui->comboBox_depo_period->currentIndex() == 0) {
    months *= 12;
  }
  double rate = ui->lineEdit_depo_rate->text().toDouble() / 100.0;
  double free_taxes =
      1000000 * (ui->lineEdit_taxe_rate->text().toDouble() / 100.0);
  double depo_percents = 0, depo_total_amount = 0, tax_total = 0,
         depo_curr_percents = 0;
  QDate period = ui->dateEdit->date();
  QDate future = period.addMonths(months);
  int days;
  if (deposits.size() > 0) {
    for (int row = 0; row < deposits.size(); row++) {
      QDate curr_period = deposits[row].date;
      double curr_amount = deposits[row].amount;
      QDate tax_date;
      tax_date.setDate(period.year(), 12, 31);
      if (curr_period >= tax_date) {
        days = period.daysTo(tax_date);
        depo_curr_percents += calc_depo_percents(amount, rate, days);
        depo_percents += depo_curr_percents;
        curr_period = tax_date;
        if (depo_curr_percents - free_taxes > free_taxes) {
          tax_total += (depo_curr_percents - free_taxes) * 0.13;
        }
        depo_curr_percents = 0;
      }
      if (curr_period >= period && curr_period <= future &&
          (amount + curr_amount >= 0)) {
        days = period.daysTo(curr_period);
        depo_curr_percents = calc_depo_percents(amount, rate, days);
        depo_percents += depo_curr_percents;
        period = curr_period;
        amount += curr_amount;
      }
    }
  }
  while (period.year() < future.year()) {
    QDate curr_year;
    curr_year.setDate(period.year(), 12, 31);
    days = period.daysTo(curr_year);
    depo_curr_percents += calc_depo_percents(amount, rate, days);
    depo_percents += depo_curr_percents;
    if (depo_curr_percents > free_taxes) {
      tax_total += (depo_curr_percents - free_taxes) * 0.13;
    }
    period.setDate(period.year() + 1, 1, 1);
    depo_curr_percents = 0;
  }
  days = period.daysTo(future);
  depo_percents += calc_depo_percents(amount, rate, days);
  ui->lineEdit_depo_percents->setText(QString::number(depo_percents, 10, 2));
  ui->lineEdit_depo_total_amount->setText(QString::number(amount, 10, 2));
  ui->lineEdit_taxes_amount->setText(QString::number(tax_total, 10, 2));
}

void MainWindow::on_pushButton_add_plus_clicked() {
  int row = ui->tableWidget_add->rowCount();
  ui->tableWidget_add->insertRow(row);
  ui->tableWidget_add->setItem(
      row, 0,
      new QTableWidgetItem(ui->dateEdit_add->date().toString("dd-MM-yyyy")));
  ui->tableWidget_add->setItem(row, 1,
                               new QTableWidgetItem(ui->lineEdit_add->text()));
  DepositInfo deposit;
  deposit.amount = ui->lineEdit_add->text().toDouble();
  deposit.date = ui->dateEdit_add->date();
  deposits_add.push_back(deposit);
}

void MainWindow::on_pushButton_remove_plus_clicked() {
  int row = ui->tableWidget_remove->rowCount();
  ui->tableWidget_remove->insertRow(row);
  ui->tableWidget_remove->setItem(
      row, 0,
      new QTableWidgetItem(ui->dateEdit_remove->date().toString("dd-MM-yyyy")));
  ui->tableWidget_remove->setItem(
      row, 1, new QTableWidgetItem(ui->lineEdit_remove->text()));
  DepositInfo deposit;
  deposit.amount = ui->lineEdit_remove->text().toDouble() * (-1);
  deposit.date = ui->dateEdit_remove->date();
  deposits_remove.push_back(deposit);
}

void MainWindow::on_pushButton_add_minus_clicked() {
  int row = ui->tableWidget_add->rowCount();
  if (row > 0) {
    ui->tableWidget_add->removeRow(row - 1);
  }
  deposits_add.pop_back();
}

void MainWindow::on_pushButton_remove_minus_clicked() {
  int row = ui->tableWidget_remove->rowCount();
  if (row > 0) {
    ui->tableWidget_remove->removeRow(row - 1);
  }
  deposits_remove.pop_back();
}
