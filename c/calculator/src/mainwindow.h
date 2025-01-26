#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QMainWindow>

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

 private:
  struct DepositInfo {
    QDate date;
    double amount;
  };
  std::vector<DepositInfo> deposits_add, deposits_remove, deposits;
  Ui::MainWindow *ui;

 private slots:
  void press_lexems();
  void on_pushButton_clear_clicked();
  void on_pushButton_erase_clicked();
  void on_pushButton_calc_clicked();
  void on_pushButton_sign_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_draw_clicked();
  void on_pushButton_copy_exp_clicked();
  void on_pushButton_credit_clicked();
  void on_pushButton_depo_clicked();
  void on_pushButton_add_plus_clicked();
  void on_pushButton_remove_plus_clicked();
  void on_pushButton_add_minus_clicked();
  void on_pushButton_remove_minus_clicked();
  void sort_deposits();
  double calc_depo_percents(double amount, double rate, int days);
};

double eval_annuitent_pay(double amount, int period, double rate);

#endif  // MAINWINDOW_H
