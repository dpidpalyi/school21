#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(1, 1){};

S21Matrix::S21Matrix(int rows, int cols) : rows_{rows}, cols_{cols} {
  if (rows_ < 1 || cols_ < 1)
    throw std::invalid_argument("the number of cols or rows is less than 1");
  Allocate();
}

S21Matrix::S21Matrix(const S21Matrix& rhs)
    : rows_{rhs.rows_}, cols_{rhs.cols_} {
  Allocate();
  for (auto i = 0; i < rows_; ++i)
    std::copy(rhs.matrix_[i], rhs.matrix_[i] + cols_, matrix_[i]);
}

S21Matrix::S21Matrix(S21Matrix&& rhs) noexcept
    : rows_{rhs.rows_}, cols_{rhs.cols_}, matrix_{rhs.matrix_} {
  rhs.rows_ = rhs.cols_ = 0;
  rhs.matrix_ = nullptr;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& rhs) {
  auto tmp(rhs);
  swap(*this, tmp);
  return *this;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& rhs) noexcept {
  if (this != &rhs) {
    Free();
    rows_ = std::move(rhs.rows_);
    cols_ = std::move(rhs.cols_);
    matrix_ = std::move(rhs.matrix_);
    rhs.rows_ = rhs.cols_ = 0;
    rhs.matrix_ = nullptr;
  }
  return *this;
}

S21Matrix::~S21Matrix() { Free(); }

int S21Matrix::get_rows() const noexcept { return rows_; }

int S21Matrix::get_cols() const noexcept { return cols_; }

void S21Matrix::set_rows(int rows) {
  if (rows < 1)
    throw std::invalid_argument("the number of rows is less then 1");
  S21Matrix tmp(rows, cols_);
  for (auto i = 0; i < (rows < rows_ ? rows : rows_); ++i)
    for (auto j = 0; j < cols_; ++j) tmp.matrix_[i][j] = matrix_[i][j];
  swap(*this, tmp);
}

void S21Matrix::set_cols(int cols) {
  if (cols < 1)
    throw std::invalid_argument("the number of cols is less then 1");
  S21Matrix tmp(rows_, cols);
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < (cols < cols_ ? cols : cols_); ++j)
      tmp.matrix_[i][j] = matrix_[i][j];
  swap(*this, tmp);
}

bool S21Matrix::EqMatrix(const S21Matrix& rhs) const {
  if (!IsSameSize(rhs)) return false;
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_; ++j)
      if (std::abs(matrix_[i][j] - rhs.matrix_[i][j]) > EPS) return false;
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& rhs) {
  if (!IsSameSize(rhs))
    throw std::invalid_argument("different matrix dimensions");
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_; ++j) matrix_[i][j] += rhs.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix& rhs) {
  if (!IsSameSize(rhs))
    throw std::invalid_argument("different matrix dimensions");
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_; ++j) matrix_[i][j] -= rhs.matrix_[i][j];
}

void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_; ++j) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix& rhs) {
  if (cols_ != rhs.rows_)
    throw std::invalid_argument(
        "the number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  S21Matrix tmp(rows_, rhs.cols_);
  for (auto i = 0; i < tmp.rows_; ++i)
    for (auto j = 0; j < tmp.cols_; ++j) {
      tmp.matrix_[i][j] = 0;
      for (auto k = 0; k < rhs.rows_; ++k)
        tmp.matrix_[i][j] += matrix_[i][k] * rhs.matrix_[k][j];
    }
  swap(*this, tmp);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix tmp(cols_, rows_);
  for (auto i = 0; i < rows_; ++i)
    for (auto j = 0; j < cols_; ++j) tmp.matrix_[j][i] = matrix_[i][j];
  return tmp;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) throw std::invalid_argument("the matrix is not square");
  S21Matrix result{rows_, cols_};
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
    return result;
  }
  for (auto i = 0; i < result.rows_; ++i)
    for (auto j = 0; j < result.cols_; ++j) {
      S21Matrix minor_matrix = GetMinor(i, j);
      result.matrix_[i][j] = minor_matrix.Determinant();
      if ((i + j) % 2 != 0) result.matrix_[i][j] = -result.matrix_[i][j];
    }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) throw std::invalid_argument("the matrix is not square");
  double result = 1.0;
  S21Matrix tmp(*this);
  int size = rows_;
  for (auto i = 0; i < size; ++i) {
    int p = i;
    for (auto j = i + 1; j < size; ++j)
      if (std::abs(tmp.matrix_[j][i]) > std::abs(tmp.matrix_[p][i])) p = j;
    if (std::abs(tmp.matrix_[p][i]) < EPS) return 0.0;
    tmp.SwapRows(i, p);
    result *= tmp.matrix_[i][i];
    if (i != p) result = -result;
    for (auto j = i + 1; j < size; ++j) {
      double koef = tmp.matrix_[j][i] / tmp.matrix_[i][i];
      for (auto k = i; k < size; ++k)
        tmp.matrix_[j][k] -= tmp.matrix_[i][k] * koef;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) throw std::invalid_argument("the matrix is not square");
  auto det = Determinant();
  if (std::abs(det) < EPS) throw std::logic_error("matrix determinant is 0");
  return Transpose().CalcComplements() * (1.0 / det);
}

void swap(S21Matrix& lhs, S21Matrix& rhs) noexcept {
  std::swap(lhs.rows_, rhs.rows_);
  std::swap(lhs.cols_, rhs.cols_);
  std::swap(lhs.matrix_, rhs.matrix_);
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 1 || row > rows_ || col < 1 || col > cols_)
    throw std::out_of_range("index is outside the matrix");
  return matrix_[row - 1][col - 1];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row < 1 || row > rows_ || col < 1 || col > cols_)
    throw std::out_of_range("index is outside the matrix");
  return matrix_[row - 1][col - 1];
}

bool S21Matrix::operator==(const S21Matrix& rhs) const { return EqMatrix(rhs); }

bool S21Matrix::operator!=(const S21Matrix& rhs) const {
  return !EqMatrix(rhs);
}

S21Matrix S21Matrix::operator+(const S21Matrix& rhs) const {
  auto tmp(*this);
  tmp.SumMatrix(rhs);
  return tmp;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& rhs) {
  SumMatrix(rhs);
  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix& rhs) const {
  auto tmp(*this);
  tmp.SubMatrix(rhs);
  return tmp;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& rhs) {
  SubMatrix(rhs);
  return *this;
}

S21Matrix S21Matrix::operator*(const double num) const {
  auto tmp(*this);
  tmp.MulNumber(num);
  return tmp;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& rhs) const {
  auto tmp(*this);
  tmp.MulMatrix(rhs);
  return tmp;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& rhs) {
  MulMatrix(rhs);
  return *this;
}

void S21Matrix::Allocate() {
  matrix_ = new double* [rows_] {};
  for (auto i = 0; i < rows_; ++i) {
    try {
      matrix_[i] = new double[cols_]{};
    } catch (std::bad_alloc& err) {
      for (auto j = 0; j < i; ++j) delete[] matrix_[j];
      delete[] matrix_;
      throw;
    }
  }
}

void S21Matrix::Free() {
  if (matrix_) {
    for (auto j = 0; j < rows_; ++j) delete[] matrix_[j];
    delete[] matrix_;
  }
}

bool S21Matrix::IsSameSize(const S21Matrix& rhs) const {
  return rows_ == rhs.rows_ && cols_ == rhs.cols_;
}

S21Matrix S21Matrix::GetMinor(int skip_row, int skip_col) const {
  S21Matrix result{rows_ - 1, cols_ - 1};
  int shift_i = 0;
  for (auto i = 0; i < result.rows_; ++i) {
    if (i == skip_row) shift_i = 1;
    int shift_j = 0;
    for (auto j = 0; j < result.cols_; ++j) {
      if (j == skip_col) shift_j = 1;
      result.matrix_[i][j] = matrix_[i + shift_i][j + shift_j];
    }
  }
  return result;
}

void S21Matrix::SwapRows(int from, int to) {
  std::swap(matrix_[from], matrix_[to]);
}
