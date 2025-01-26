#ifndef S21_CONTROLLER_H
#define S21_CONTROLLER_H

#include "./model.h"

namespace s21 {
class Controller {
 public:
  Controller(s21::Model *m) : model(m){};

  void SetInput(const std::string &s, double x) { model->SetInp(s, x); }

  bool Calculate() { return model->Calc(); }

  bool FillVectors() { return model->FillVect(); }

  bool GetError() { return model->GetErr(); }

  double GetResult() { return model->GetRes(); }

  void SetMinX(double x) { model->SetMnX(x); }

  void SetMaxX(double x) { model->SetMxX(x); }

  void SetMinY(double y) { model->SetMnY(y); }

  void SetMaxY(double y) { model->SetMxY(y); }

  double GetMinX() { return model->GetMnX(); }

  double GetMaxX() { return model->GetMxX(); }

  double GetMinY() { return model->GetMnY(); }

  double GetMaxY() { return model->GetMxY(); }

  std::vector<double> &GetVectorX() { return model->GetX(); }

  std::vector<double> &GetVectorY() { return model->GetY(); }

 private:
  s21::Model *model = nullptr;
};

};  // namespace s21

#endif  // S21_CONTROLLER_H
