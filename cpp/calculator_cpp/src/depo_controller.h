#ifndef S21_DEPO_CONTROLLER_H
#define S21_DEPO_CONTROLLER_H

#include "./depo_model.h"

namespace s21 {
class DepoController {
 public:
  DepoController(s21::DepoModel *m) : depo_model(m){};

  bool SetInput(double a, int m, int y, bool cap, int d, double r, double f_t,
                QDate p) {
    return depo_model->SetInp(a, m, y, cap, d, r, f_t, p);
  }

  void DepoCalculate() { depo_model->DepoCalc(); }

  double GetDepoPercents() { return depo_model->GetPercents(); }

  double GetAmount() { return depo_model->GetAmnt(); }

  double GetTaxTotal() { return depo_model->GetTax(); }

  void DepoAddPush(double a, QDate d) {
    return depo_model->DepoAddPushBack(a, d);
  }

  void DepoRemovePush(double a, QDate d) {
    return depo_model->DepoRemPushBack(a, d);
  }

  void DepoAddPop() { depo_model->DepoAddPopBack(); }

  void DepoRemovePop() { depo_model->DepoRemPopBack(); }

 private:
  s21::DepoModel *depo_model = nullptr;
};

};  // namespace s21

#endif  // S21_DEPO_CONTROLLER_H
