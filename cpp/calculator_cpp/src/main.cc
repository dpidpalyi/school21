#include <QApplication>

#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::CreditModel credit_model;
  s21::DepoModel depo_model;
  s21::Controller controller(&model);
  s21::CreditController credit_controller(&credit_model);
  s21::DepoController depo_controller(&depo_model);
  s21::View w(&controller, &credit_controller, &depo_controller);
  w.show();
  return a.exec();
}
