#include <gtest/gtest.h>

#include <limits>

#include "../model.h"

TEST(ParseTest, Test1) {
  bool want_error = false;
  double want_result = 1.0;
  s21::Model m;
  m.SetInp("1", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(ParseTest, Test2) {
  bool want_error = true;
  s21::Model m;
  m.SetInp("      ", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(ParseTest, Test3) {
  bool want_error = true;
  s21::Model m;
  m.SetInp("a", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(ParseTest, Test4) {
  bool want_error = true;
  s21::Model m;
  m.SetInp("b ", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(ParseTest, Test5) {
  bool want_error = true;
  s21::Model m;
  m.SetInp(" c ", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(ParseTest, Test6) {
  bool want_error = false;
  double want_result = 123.456;
  s21::Model m;
  m.SetInp("   123.456   ", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(ParseTest, Test7) {
  bool want_error = true;
  s21::Model m;
  m.SetInp("a5.2", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(ParseTest, Test8) {
  bool want_error = true;
  s21::Model m;
  m.SetInp("5.2b", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(ParseTest, Test9) {
  bool want_error = true;
  s21::Model m;
  m.SetInp("2mod", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(ParseTest, Test10) {
  bool want_error = false;
  double want_result = 1.0;
  s21::Model m;
  m.SetInp("5 mod 2", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(ParseTest, Test11) {
  bool want_error = true;
  s21::Model m;
  m.SetInp("5..2", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(ParseTest, Test12) {
  bool want_error = true;
  s21::Model m;
  m.SetInp("(((1))", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(ParseTest, Test13) {
  bool want_error = false;
  double want_result = 1.0;
  s21::Model m;
  m.SetInp("(((1)))", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(ParseTest, Test14) {
  bool want_error = true;
  s21::Model m;
  m.SetInp("3^^", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
}

TEST(CalcTest, Test1) {
  bool want_error = false;
  double want_result = 3.3;
  s21::Model m;
  m.SetInp("1.1+2.2", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test2) {
  bool want_error = false;
  double want_result = 1.3333;
  s21::Model m;
  m.SetInp("x", 1.3333);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test3) {
  bool want_error = false;
  double want_result = 1.3333;
  s21::Model m;
  m.SetInp("x", 1.3333);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test4) {
  bool want_error = false;
  double want_result = 2.0;
  s21::Model m;
  m.SetInp("+2", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test5) {
  bool want_error = false;
  double want_result = 9.0;
  s21::Model m;
  m.SetInp("3^2", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test6) {
  bool want_error = false;
  double want_result = 16.0;
  s21::Model m;
  m.SetInp("x * x", 4.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test7) {
  bool want_error = false;
  double want_result = 2.0;
  s21::Model m;
  m.SetInp("(x / (x - 2))", 4.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test8) {
  bool want_error = false;
  double want_result = -25.0;
  s21::Model m;
  m.SetInp("x * (-3 - 2)", 5.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test9) {
  bool want_error = false;
  double want_result = 1.0;
  s21::Model m;
  m.SetInp("8 * x ^ - 1)", 8.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test10) {
  bool want_error = false;
  double want_result = std::numeric_limits<double>::infinity();
  s21::Model m;
  m.SetInp("1/0)", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test11) {
  bool want_error = false;
  double want_result = 4.0;
  s21::Model m;
  m.SetInp("log(100)+2", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test12) {
  bool want_error = false;
  double want_result = cos(0.5);
  s21::Model m;
  m.SetInp("cos(x)", 0.5);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test13) {
  bool want_error = false;
  double want_result = sin(0.5);
  s21::Model m;
  m.SetInp("sin(0.5)", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test14) {
  bool want_error = false;
  double want_result = tan(0.5);
  s21::Model m;
  m.SetInp("tan(0.5)", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test15) {
  bool want_error = false;
  double want_result = atan(0.5);
  s21::Model m;
  m.SetInp("atan(0.5)", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test16) {
  bool want_error = false;
  double want_result = acos(0.5);
  s21::Model m;
  m.SetInp("acos(0.5)", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test17) {
  bool want_error = false;
  double want_result = asin(0.5);
  s21::Model m;
  m.SetInp("asin(0.5)", 0.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test18) {
  bool want_error = false;
  double want_result = 4.0;
  s21::Model m;
  m.SetInp("sqrt(x)", 16.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(CalcTest, Test19) {
  bool want_error = false;
  double want_result = log(16.0);
  s21::Model m;
  m.SetInp("ln(x)", 16.0);
  m.Calc();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_DOUBLE_EQ(want_result, m.GetRes());
}

TEST(GraphTest, Test1) {
  bool want_error = false;
  std::vector<double> want_x(101);
  std::vector<double> want_y(101);
  for (int i = 0; i < 101; ++i) want_x[i] = want_y[i] = i;
  s21::Model m;
  m.SetInp("x", 0.0);
  m.SetMnX(0);
  m.SetMxX(100);
  m.FillVect();
  EXPECT_EQ(want_error, m.GetErr());
  EXPECT_EQ(want_x, m.GetX());
  EXPECT_EQ(want_y, m.GetY());
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
