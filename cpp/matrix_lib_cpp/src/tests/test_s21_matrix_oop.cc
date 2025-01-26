#include <gtest/gtest.h>

#include "../lib/s21_matrix_oop.h"

TEST(ConstructorTest, DefaultConstructor) {
  S21Matrix got;
  EXPECT_EQ(got.get_rows(), 1);
  EXPECT_EQ(got.get_cols(), 1);
}

TEST(ConstructorTest, ParameterizedConstructorSuccess1) {
  S21Matrix got(2, 2);
  EXPECT_EQ(got.get_rows(), 2);
  EXPECT_EQ(got.get_cols(), 2);
}

TEST(ConstructorTest, ParameterizedConstructorSuccess2) {
  S21Matrix got(10000, 10000);
  EXPECT_EQ(got.get_rows(), 10000);
  EXPECT_EQ(got.get_cols(), 10000);
}

TEST(ConstructorTest, ParameterizedConstructorFailure) {
  EXPECT_THROW(S21Matrix got(-1, 10000), std::invalid_argument);
}

TEST(ConstructorTest, CopyConstructorSuccess) {
  S21Matrix got1(10, 10);
  got1(10, 10) = 555;
  S21Matrix got2(got1);
  EXPECT_EQ(got2.get_rows(), 10);
  EXPECT_EQ(got2.get_cols(), 10);
  EXPECT_DOUBLE_EQ(got2(1, 1), 0);
  EXPECT_DOUBLE_EQ(got2(10, 10), 555);
}

TEST(ConstructorTest, MoveConstructorSuccess) {
  S21Matrix got1(10, 10);
  got1(10, 10) = 555;
  S21Matrix got2(std::move(got1));
  EXPECT_EQ(got1.get_rows(), 0);
  EXPECT_EQ(got1.get_cols(), 0);
  EXPECT_EQ(got2.get_rows(), 10);
  EXPECT_EQ(got2.get_cols(), 10);
  EXPECT_DOUBLE_EQ(got2(1, 1), 0);
  EXPECT_DOUBLE_EQ(got2(10, 10), 555);
}

TEST(CopyAssignmentTest, CopyAssignmentSuccess1) {
  S21Matrix got1(10, 10);
  got1(10, 10) = 555;
  S21Matrix got2;
  got2 = got1;
  EXPECT_EQ(got2.get_rows(), 10);
  EXPECT_EQ(got2.get_cols(), 10);
  EXPECT_DOUBLE_EQ(got2(1, 1), 0);
  EXPECT_DOUBLE_EQ(got2(10, 10), 555);
}

TEST(CopyAssignmentTest, CopyAssignmentSuccess2) {
  S21Matrix got1(10, 10);
  got1(10, 10) = 555;
  got1 = got1;
  EXPECT_EQ(got1.get_rows(), 10);
  EXPECT_EQ(got1.get_cols(), 10);
  EXPECT_DOUBLE_EQ(got1(1, 1), 0);
  EXPECT_DOUBLE_EQ(got1(10, 10), 555);
}

TEST(MoveAssignmentTest, MoveAssignmentSuccess1) {
  S21Matrix got1(10, 10);
  got1(10, 10) = 555;
  S21Matrix got2;
  got2 = std::move(got1);
  EXPECT_EQ(got1.get_rows(), 0);
  EXPECT_EQ(got1.get_cols(), 0);
  EXPECT_EQ(got2.get_rows(), 10);
  EXPECT_EQ(got2.get_cols(), 10);
  EXPECT_DOUBLE_EQ(got2(1, 1), 0);
  EXPECT_DOUBLE_EQ(got2(10, 10), 555);
}

TEST(MoveAssignmentTest, MoveAssignmentSuccess2) {
  S21Matrix got1(10, 10);
  got1(10, 10) = 555;
  got1 = std::move(got1);
  EXPECT_EQ(got1.get_rows(), 10);
  EXPECT_EQ(got1.get_cols(), 10);
  EXPECT_DOUBLE_EQ(got1(1, 1), 0);
  EXPECT_DOUBLE_EQ(got1(10, 10), 555);
}

TEST(MutatorTest, SetRowsSuccess1) {
  S21Matrix got1;
  got1(1, 1) = 10;
  got1.set_rows(5);
  got1(5, 1) = 123.456;
  EXPECT_EQ(got1.get_rows(), 5);
  EXPECT_EQ(got1.get_cols(), 1);
  EXPECT_DOUBLE_EQ(got1(5, 1), 123.456);
  EXPECT_DOUBLE_EQ(got1(1, 1), 10);
}

TEST(MutatorTest, SetRowsSuccess2) {
  S21Matrix got1(3, 3);
  got1(3, 3) = 50;
  got1(2, 3) = 100;
  got1.set_rows(2);
  EXPECT_EQ(got1.get_rows(), 2);
  EXPECT_EQ(got1.get_cols(), 3);
  EXPECT_DOUBLE_EQ(got1(2, 3), 100);
}

TEST(MutatorTest, SetRowsFailure) {
  S21Matrix got1;
  got1(1, 1) = 10;
  EXPECT_THROW(got1.set_rows(0), std::invalid_argument);
  EXPECT_EQ(got1.get_rows(), 1);
  EXPECT_EQ(got1.get_cols(), 1);
  EXPECT_DOUBLE_EQ(got1(1, 1), 10);
}

TEST(MutatorTest, SetColsSuccess1) {
  S21Matrix got1;
  got1(1, 1) = 10;
  got1.set_cols(5);
  got1(1, 5) = 123.456;
  EXPECT_EQ(got1.get_rows(), 1);
  EXPECT_EQ(got1.get_cols(), 5);
  EXPECT_DOUBLE_EQ(got1(1, 5), 123.456);
  EXPECT_DOUBLE_EQ(got1(1, 1), 10);
}

TEST(MutatorTest, SetColsSuccess2) {
  S21Matrix got1(3, 3);
  got1(3, 2) = 50;
  got1(2, 3) = 100;
  got1.set_cols(2);
  EXPECT_EQ(got1.get_rows(), 3);
  EXPECT_EQ(got1.get_cols(), 2);
  EXPECT_DOUBLE_EQ(got1(3, 2), 50);
}

TEST(MutatorTest, SetColsFailure) {
  S21Matrix got1(5, 5);
  got1(1, 1) = 10;
  EXPECT_THROW(got1.set_cols(-10), std::invalid_argument);
  EXPECT_EQ(got1.get_rows(), 5);
  EXPECT_EQ(got1.get_cols(), 5);
  EXPECT_DOUBLE_EQ(got1(1, 1), 10);
}

TEST(EqMatrixTest, EqMatrixSuccess) {
  S21Matrix got1(2, 2);
  S21Matrix got2(2, 2);
  got1(2, 2) = 10.123;
  got2(2, 2) = 10.123;
  EXPECT_EQ(got1, got2);
}

TEST(EqMatrixTest, EqMatrixFailure1) {
  S21Matrix got1(2, 2);
  S21Matrix got2(2, 2);
  got1(2, 2) = 10.124;
  got2(2, 2) = 10.123;
  EXPECT_EQ(got1 == got2, false);
  EXPECT_NE(got1, got2);
}

TEST(EqMatrixTest, EqMatrixFailure2) {
  S21Matrix got1(3, 3);
  S21Matrix got2(2, 2);
  EXPECT_EQ(got1 == got2, false);
  EXPECT_NE(got1, got2);
}

TEST(SumMatrixTest, SumMatrixSuccess1) {
  S21Matrix got1;
  got1(1, 1) = 10;
  S21Matrix got2(got1);
  S21Matrix got3 = got1 + got2;
  EXPECT_EQ(got3.get_rows(), 1);
  EXPECT_EQ(got3.get_cols(), 1);
  EXPECT_DOUBLE_EQ(got3(1, 1), 20);
}

TEST(SumMatrixTest, SumMatrixSuccess2) {
  S21Matrix got1;
  got1(1, 1) = 100;
  got1 += got1;
  EXPECT_DOUBLE_EQ(got1(1, 1), 200);
}

TEST(SumMatrixTest, SumMatrixFailure) {
  S21Matrix got1;
  got1(1, 1) = 100;
  S21Matrix got2(2, 2);
  EXPECT_THROW(got1 + got2, std::invalid_argument);
  EXPECT_DOUBLE_EQ(got1(1, 1), 100);
}

TEST(SubMatrixTest, SubMatrixSuccess1) {
  S21Matrix got1;
  got1(1, 1) = 20;
  S21Matrix got2;
  got2(1, 1) = 5;
  S21Matrix got3 = got1 - got2;
  EXPECT_EQ(got3.get_rows(), 1);
  EXPECT_EQ(got3.get_cols(), 1);
  EXPECT_DOUBLE_EQ(got3(1, 1), 15);
}

TEST(SubMatrixTest, SubMatrixSuccess2) {
  S21Matrix got1;
  got1(1, 1) = 100;
  got1 -= got1;
  EXPECT_DOUBLE_EQ(got1(1, 1), 0);
}

TEST(SubMatrixTest, SubMatrixFailure) {
  S21Matrix got1;
  got1(1, 1) = 100;
  S21Matrix got2(2, 2);
  EXPECT_THROW(got1 - got2, std::invalid_argument);
  EXPECT_DOUBLE_EQ(got1(1, 1), 100);
}

TEST(MulNumberTest, MulNumberSuccess1) {
  S21Matrix got1;
  got1(1, 1) = 10;
  double num = 10;
  S21Matrix got2 = got1 * num;
  EXPECT_EQ(got2.get_rows(), 1);
  EXPECT_EQ(got2.get_cols(), 1);
  EXPECT_DOUBLE_EQ(got2(1, 1), 100);
}

TEST(MulNumberTest, MulNumberSuccess2) {
  S21Matrix got1;
  got1(1, 1) = 10;
  double num = 10;
  got1 *= num;
  EXPECT_DOUBLE_EQ(got1(1, 1), 100);
}

TEST(MulMatrixTest, MulMatrixSuccess1) {
  S21Matrix got1(1, 1);
  got1(1, 1) = 10;
  got1 *= got1;
  EXPECT_EQ(got1.get_rows(), 1);
  EXPECT_EQ(got1.get_cols(), 1);
  EXPECT_DOUBLE_EQ(got1(1, 1), 100);
}

TEST(MulMatrixTest, MulMatrixSuccess2) {
  S21Matrix got1(1, 2);
  S21Matrix got2(2, 1);
  got1(1, 1) = 1;
  got1(1, 2) = 2;
  got2(1, 1) = 3;
  got2(2, 1) = 4;
  S21Matrix got3 = got1 * got2;
  EXPECT_EQ(got3.get_rows(), 1);
  EXPECT_EQ(got3.get_cols(), 1);
  EXPECT_DOUBLE_EQ(got3(1, 1), 11);
}

TEST(MulMatrixTest, MulMatrixFailure) {
  S21Matrix got1;
  got1(1, 1) = 100;
  S21Matrix got2(2, 2);
  EXPECT_THROW(got1 * got2, std::invalid_argument);
  EXPECT_DOUBLE_EQ(got1(1, 1), 100);
}

TEST(TransposeTest, TransposeSuccess1) {
  S21Matrix got1;
  got1(1, 1) = 100;
  S21Matrix got2 = got1.Transpose();
  EXPECT_EQ(got2.get_rows(), 1);
  EXPECT_EQ(got2.get_cols(), 1);
  EXPECT_DOUBLE_EQ(got2(1, 1), 100);
}

TEST(TransposeTest, TransposeSuccess2) {
  S21Matrix got1(4, 1);
  got1(4, 1) = 100;
  S21Matrix got2 = got1.Transpose();
  EXPECT_EQ(got2.get_rows(), 1);
  EXPECT_EQ(got2.get_cols(), 4);
  EXPECT_DOUBLE_EQ(got2(1, 4), 100);
}

TEST(TransposeTest, TransposeSuccess3) {
  S21Matrix got1(2, 3);
  got1(1, 2) = 100;
  S21Matrix got2 = got1.Transpose();
  EXPECT_EQ(got2.get_rows(), 3);
  EXPECT_EQ(got2.get_cols(), 2);
  EXPECT_DOUBLE_EQ(got2(2, 1), 100);
}

TEST(TransposeTest, TransposeSuccess4) {
  S21Matrix got1(2, 2);
  got1(1, 2) = 100;
  S21Matrix got2 = got1.Transpose();
  EXPECT_EQ(got2.get_rows(), 2);
  EXPECT_EQ(got2.get_cols(), 2);
  EXPECT_DOUBLE_EQ(got2(2, 1), 100);
}

TEST(CalcComplementsTest, CalcComplementsSuccess1) {
  S21Matrix got1(1, 1);
  got1(1, 1) = 100;
  S21Matrix got2 = got1.CalcComplements();
  EXPECT_EQ(got2.get_rows(), 1);
  EXPECT_EQ(got2.get_cols(), 1);
  EXPECT_DOUBLE_EQ(got2(1, 1), 100);
}

TEST(CalcComplementsTest, CalcComplementsSuccess2) {
  S21Matrix got1(3, 3);
  got1(1, 1) = 1;
  got1(1, 2) = 2;
  got1(1, 3) = 3;
  got1(2, 1) = 0;
  got1(2, 2) = 4;
  got1(2, 3) = 2;
  got1(3, 1) = 5;
  got1(3, 2) = 2;
  got1(3, 3) = 1;
  S21Matrix got2 = got1.CalcComplements();
  EXPECT_EQ(got2.get_rows(), 3);
  EXPECT_EQ(got2.get_cols(), 3);
  EXPECT_DOUBLE_EQ(got2(1, 1), 0);
  EXPECT_DOUBLE_EQ(got2(1, 2), 10);
  EXPECT_DOUBLE_EQ(got2(1, 3), -20);
  EXPECT_DOUBLE_EQ(got2(2, 1), 4);
  EXPECT_DOUBLE_EQ(got2(2, 2), -14);
  EXPECT_DOUBLE_EQ(got2(2, 3), 8);
  EXPECT_DOUBLE_EQ(got2(3, 1), -8);
  EXPECT_DOUBLE_EQ(got2(3, 2), -2);
  EXPECT_DOUBLE_EQ(got2(3, 3), 4);
}

TEST(CalcComplementsTest, CalcComplementsFailure1) {
  S21Matrix got1(1, 2);
  got1(1, 1) = 100;
  EXPECT_THROW(got1.CalcComplements(), std::invalid_argument);
  EXPECT_DOUBLE_EQ(got1(1, 1), 100);
}

TEST(InverseMatrixTest, InverseMatrixSuccess1) {
  S21Matrix got1(3, 3);
  got1(1, 1) = 2;
  got1(1, 2) = 5;
  got1(1, 3) = 7;
  got1(2, 1) = 6;
  got1(2, 2) = 3;
  got1(2, 3) = 4;
  got1(3, 1) = 5;
  got1(3, 2) = -2;
  got1(3, 3) = -3;
  S21Matrix got2 = got1.InverseMatrix();
  EXPECT_EQ(got2.get_rows(), 3);
  EXPECT_EQ(got2.get_cols(), 3);
  EXPECT_NEAR(got2(1, 1), 1, 1e-7);
  EXPECT_NEAR(got2(1, 2), -1, 1e-7);
  EXPECT_NEAR(got2(1, 3), 1, 1e-7);
  EXPECT_NEAR(got2(2, 1), -38, 1e-7);
  EXPECT_NEAR(got2(2, 2), 41, 1e-7);
  EXPECT_NEAR(got2(2, 3), -34, 1e-7);
  EXPECT_NEAR(got2(3, 1), 27, 1e-7);
  EXPECT_NEAR(got2(3, 2), -29, 1e-7);
  EXPECT_NEAR(got2(3, 3), 24, 1e-7);
}

TEST(OperatorBracketsTest, OperatorBracketsSuccess1) {
  const S21Matrix got1(1, 1);
  EXPECT_DOUBLE_EQ(got1(1, 1), 0);
}

TEST(OperatorBracketsTest, OperatorBracketsFailure1) {
  S21Matrix got1(1, 1);
  got1(1, 1) = 100;
  EXPECT_THROW(got1(2, 2), std::out_of_range);
}

TEST(OperatorBracketsTest, OperatorBracketsFailure2) {
  const S21Matrix got1(1, 1);
  EXPECT_THROW(got1(2, 2), std::out_of_range);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
