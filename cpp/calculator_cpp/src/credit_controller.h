#ifndef S21_CREDIT_CONTROLLER_H
#define S21_CREDIT_CONTROLLER_H

#include "./credit_model.h"

namespace s21 {
class CreditController {
 public:
  CreditController(s21::CreditModel *m) : credit_model(m){};

  bool SetInput(double a, double r, int p, bool y) {
    return credit_model->SetInp(a, r, p, y);
  }

  void CreditCalcAnnuitent() { credit_model->CreditCalcAnnt(); }

  void CreditCalcDifference() { credit_model->CreditCalcDiff(); }

  double GetPayment() { return credit_model->GetPay(); }

  double GetTotalAmount() { return credit_model->GetTotal(); }

  double GetOverpay() { return credit_model->GetOver(); }

  std::vector<double> &GetDiffPayments() { return credit_model->GetDiff(); }

 private:
  s21::CreditModel *credit_model = nullptr;
};

};  // namespace s21

#endif  // S21_CREDIT_CONTROLLER_H
