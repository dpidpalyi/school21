#ifndef S21_DEPO_MODEL_H
#define S21_DEPO_MODEL_H

/**
 * @file depo_model.h
 *
 * @brief MVC model to calculate deposit
 *
 */

#include <vector>

namespace s21 {
class DepoModel {
 private:
  struct DepositInfo {
    QDate date;
    double amount;
  };

 public:
  DepoModel() = default;
  ~DepoModel() = default;

  /**
   * @brief Set input parameters
   *
   * @param a amount of money
   * @param m months
   * @param y if need to calculate in months
   * @param cap if need to capitalize percents
   * @param d if capitalize daily
   * @param r deposit rate
   * @param f_t free tax rate
   * @param p date when deposit opened
   *
   * @return true if input is correct
   */
  bool SetInp(double a, int m, int y, bool cap, int d, double r, double f_t,
              QDate p) {
    amount = a;
    months = m;
    capitalize = cap;
    daily = d;
    if (y == 0) months *= 12;
    rate = r / 100.0;
    free_taxes = 1000000 * f_t / 100.0;
    period = p;
    future = period.addMonths(months);
    percents = tax_total = 0;
    return amount > 0 && m > 0 && rate > 0 && free_taxes > 0;
  }

  /**
   * @brief Calculate deposit
   */
  void DepoCalc() {
    SortDeposits();
    double depo_curr_percents = 0;
    if (deposits.size() > 0) {
      for (int row = 0; row < deposits.size(); ++row) {
        QDate curr_period = deposits[row].date;
        double curr_amount = deposits[row].amount;
        QDate tax_date;
        tax_date.setDate(period.year(), 12, 31);
        if (curr_period >= tax_date) {
          days = period.daysTo(tax_date);
          depo_curr_percents += CalcPercents();
          percents += depo_curr_percents;
          curr_period = tax_date;
          if (depo_curr_percents - free_taxes > free_taxes) {
            tax_total += (depo_curr_percents - free_taxes) * 0.13;
          }
          depo_curr_percents = 0;
        }
        if (curr_period >= period && curr_period <= future &&
            (amount + curr_amount >= 0)) {
          days = period.daysTo(curr_period);
          depo_curr_percents = CalcPercents();
          percents += depo_curr_percents;
          period = curr_period;
          amount += curr_amount;
        }
      }
    }
    while (period.year() < future.year()) {
      QDate curr_year;
      curr_year.setDate(period.year(), 12, 31);
      days = period.daysTo(curr_year);
      depo_curr_percents += CalcPercents();
      percents += depo_curr_percents;
      if (depo_curr_percents > free_taxes) {
        tax_total += (depo_curr_percents - free_taxes) * 0.13;
      }
      period.setDate(period.year() + 1, 1, 1);
      depo_curr_percents = 0;
    }
    days = period.daysTo(future);
    percents += CalcPercents();
  }

  /**
   * @brief Gets amount of all percents
   */
  double GetPercents() { return percents; }

  /**
   * @brief Gets amount of deposit
   */
  double GetAmnt() { return amount; }

  /**
   * @brief Gets amount of tax need to pay
   */
  double GetTax() { return tax_total; }

  /**
   * @brief Adding to deposit_add
   *
   * @param a amount
   * @param d date
   */
  void DepoAddPushBack(double a, QDate d) { PushBack(deposits_add, a, d); }

  /**
   * @brief Adding to deposit_remove
   *
   * @param a amount
   * @param d date
   */
  void DepoRemPushBack(double a, QDate d) { PushBack(deposits_remove, -a, d); }

  /**
   * @brief Removing from deposit_add
   */
  void DepoAddPopBack() { PopBack(deposits_add); }

  /**
   * @brief Removing from deposit_remove
   */
  void DepoRemPopBack() { PopBack(deposits_remove); }

 private:
  void PushBack(std::vector<DepositInfo> &depo, double a, QDate d) {
    DepositInfo deposit;
    deposit.amount = a;
    deposit.date = d;
    depo.push_back(deposit);
  }

  void PopBack(std::vector<DepositInfo> &depo) { depo.pop_back(); }

  double CalcPercents() {
    double curr_percents;
    if (capitalize) {
      if (daily == 0) {
        curr_percents = CapitalizeDaily();
      } else {
        curr_percents = CapitalizeMonthly();
      }
    } else {
      curr_percents = WithoutCapitalize();
    }

    return curr_percents;
  }

  double WithoutCapitalize() { return amount * rate * days / 365; }

  double CapitalizeDaily() {
    return amount * pow(1 + rate / 365, days) - amount;
  }

  double CapitalizeMonthly() {
    return amount * pow(1 + rate / 12, days / 29.3) - amount;
  }

  void SortDeposits() {
    deposits.clear();
    deposits.reserve(deposits_add.size() + deposits_remove.size());
    deposits.insert(deposits.end(), deposits_add.begin(), deposits_add.end());
    deposits.insert(deposits.end(), deposits_remove.begin(),
                    deposits_remove.end());

    std::sort(deposits.begin(), deposits.end(),
              [](const DepositInfo &info1, const DepositInfo &info2) {
                return info1.date < info2.date;
              });
  }

  std::vector<DepositInfo> deposits_add;
  std::vector<DepositInfo> deposits_remove;
  std::vector<DepositInfo> deposits;

  double amount;
  int months;
  int days;
  double rate;
  double free_taxes;
  double percents;
  double tax_total = 0;
  QDate period;
  QDate future;
  bool capitalize;
  int daily;
};
};  // namespace s21

#endif  // S21_DEPO_MODEL_H
