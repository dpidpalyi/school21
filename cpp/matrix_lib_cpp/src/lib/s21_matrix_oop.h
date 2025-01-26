#ifndef S21_MATRIX_OOP_H_
#define S21_MATRIX_OOP_H_

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <utility>

class S21Matrix {
 public:
  // constructors and destructor
  S21Matrix();                                     // default
  S21Matrix(int rows, int cols);                   // parameterized
  S21Matrix(const S21Matrix& rhs);                 // copy
  S21Matrix(S21Matrix&& rhs) noexcept;             // move
  S21Matrix& operator=(const S21Matrix& rhs);      // copy-assignment
  S21Matrix& operator=(S21Matrix&& rhs) noexcept;  // move-assignment
  ~S21Matrix();                                    // destructor

  // accessors and mutators
  int get_rows() const noexcept;
  int get_cols() const noexcept;
  void set_rows(int rows);
  void set_cols(int cols);

  // public methods
  bool EqMatrix(const S21Matrix& rhs) const;
  void SumMatrix(const S21Matrix& rhs);
  void SubMatrix(const S21Matrix& rhs);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& rhs);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;
  friend void swap(S21Matrix& lhs, S21Matrix& rhs) noexcept;

  // operators overloads
  double& operator()(int, int);
  const double& operator()(int, int) const;
  bool operator==(const S21Matrix& rhs) const;
  bool operator!=(const S21Matrix& rhs) const;
  S21Matrix operator+(const S21Matrix& rhs) const;
  S21Matrix& operator+=(const S21Matrix& rhs);
  S21Matrix operator-(const S21Matrix& rhs) const;
  S21Matrix& operator-=(const S21Matrix& rhs);
  S21Matrix operator*(const double num) const;
  S21Matrix& operator*=(const double num);
  S21Matrix operator*(const S21Matrix& rhs) const;
  S21Matrix& operator*=(const S21Matrix& rhs);

 private:
  // private methods
  void Allocate();
  void Free();
  bool IsSameSize(const S21Matrix& rhs) const;
  S21Matrix GetMinor(int skip_row, int skip_col) const;
  void SwapRows(int from, int to);

  // members data
  int rows_{0};
  int cols_{0};
  double** matrix_{nullptr};
  const double EPS{1e-7};
};

#endif
