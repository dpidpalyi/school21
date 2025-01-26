#ifndef S21_CREDIT_MODEL_H
#define S21_CREDIT_MODEL_H

/**
 * @file credit_model.h
 *
 * @brief MVC model to calculate credit
 *
 */

#include <vector>

namespace s21 {
class CreditModel {
 public:
  CreditModel() = default;
  ~CreditModel() = default;

  /**
   * @brief Set input parameters
   *
   * @param a amount of money
   * @param r credit rate
   * @param p number of periods
   * @param y need to calculate in months
   *
   * @return true if input is correct
   */
  bool SetInp(double a, double r, int p, int y) {
    amount = a;
    rate = r / 12.0 / 100.0;
    period = p;
    if (y == 0) period *= 12;
    total_amount = overpay = 0;
    return amount > 0 && period > 0 && rate > 0;
  }

  /**
   * @brief Calculate annuitent payments
   */
  void CreditCalcAnnt() {
    double temp = pow(1 + rate, period);
    pay = (amount * rate * temp) / (temp - 1);
    total_amount = pay * period;
    overpay = total_amount - amount;
  }

  /**
   * @brief Calculate difference payments
   */
  void CreditCalcDiff() {
    diff.clear();
    total_amount = overpay = 0;
    double remaining = amount, principal_pay = amount / period;
    for (int month = 1; month <= period; ++month) {
      pay = principal_pay + remaining * rate;
      total_amount += pay;
      diff.push_back(pay);
      remaining -= principal_pay;
    }
    overpay = total_amount - amount;
  }

  /**
   * @brief Gets difference payments
   *
   * @return vector of difference payments
   */
  std::vector<double> &GetDiff() { return diff; }

  /**
   * @brief Gets annuitent payment
   *
   * @return payment
   */
  double GetPay() { return pay; }

  /**
   * @brief Gets total amount of credit
   *
   * @return total amount
   */
  double GetTotal() { return total_amount; }

  /**
   * @brief Gets total amount of percents overpaied
   *
   * @return overpay
   */
  double GetOver() { return overpay; }

 private:
  double amount;
  double total_amount;
  double overpay;
  double rate;
  int period;
  double pay;
  std::vector<double> diff;
};
};  // namespace s21

#endif  // S21_CREDIT_MODEL_H
