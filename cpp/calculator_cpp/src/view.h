#ifndef S21_VIEW_H
#define S21_VIEW_H

#include <QDate>
#include <QMainWindow>

#include "./controller.h"
#include "./credit_controller.h"
#include "./depo_controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {
class View : public QMainWindow {
  Q_OBJECT

 public:
  View(s21::Controller *c, s21::CreditController *cc, s21::DepoController *dc,
       QWidget *parent = nullptr);
  ~View();

 private:
  s21::Controller *controller = nullptr;
  s21::CreditController *credit_controller = nullptr;
  s21::DepoController *depo_controller = nullptr;
  Ui::View *ui;

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
};

};  // namespace s21

#endif  // S21_VIEW_H
