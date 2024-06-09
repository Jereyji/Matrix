#include <gtest/gtest.h>

#include "../lib/s21_matrix_oop.h"

TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix mat;
  ASSERT_EQ(mat.GetRows(), 0);
  ASSERT_EQ(mat.GetCols(), 0);
}
TEST(S21MatrixTest, Constructor) {
  S21Matrix mat(3, 4);
  ASSERT_EQ(mat.GetRows(), 3);
  ASSERT_EQ(mat.GetCols(), 4);

  EXPECT_ANY_THROW(S21Matrix mat2(0, 1));
  ASSERT_THROW(S21Matrix mat3(3, -1), std::length_error);
}
TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix A(100, 100);
  S21Matrix B(std::move(A));
  EXPECT_EQ(0, A.GetRows());
  EXPECT_EQ(0, A.GetCols());
  EXPECT_EQ(100, B.GetRows());
  EXPECT_EQ(100, B.GetCols());
}
TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix A(3, 4);
  S21Matrix B(A);
  EXPECT_EQ(3, B.GetRows());
  EXPECT_EQ(4, B.GetCols());
  EXPECT_EQ(1, A == B);
}
TEST(S21MatrixTest, EqMatrix1) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 1;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 4;

  EXPECT_TRUE(a.EqMatrix(b));
}
TEST(S21MatrixTest, EqMatrixTest2) {
  S21Matrix A;
  S21Matrix B;
  EXPECT_THROW(A == B, std::length_error);
}
TEST(S21MatrixTest, SumMatrix) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 4;
  a(0, 1) = 19;
  a(1, 0) = 3;
  a(1, 1) = -13;

  b(0, 0) = 6;
  b(0, 1) = 1;
  b(1, 0) = 47;
  b(1, 1) = -7;

  expected(0, 0) = 10;
  expected(0, 1) = 20;
  expected(1, 0) = 50;
  expected(1, 1) = -20;

  a.SumMatrix(b);
  EXPECT_TRUE(a == expected);
}
TEST(S21MatrixTest, SubMatrix) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 4;
  a(0, 1) = 4;
  a(1, 0) = 6;
  a(1, 1) = 6;

  b(0, 0) = 2;
  b(0, 1) = 2;
  b(1, 0) = 3;
  b(1, 1) = 3;

  expected(0, 0) = 2;
  expected(0, 1) = 2;
  expected(1, 0) = 3;
  expected(1, 1) = 3;

  a.SubMatrix(b);
  EXPECT_TRUE(a == expected);
}

TEST(S21MatrixTest, MulMatrix) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  b(0, 0) = 5;
  b(0, 1) = 6;
  b(1, 0) = 7;
  b(1, 1) = 8;

  expected(0, 0) = 19;
  expected(0, 1) = 22;
  expected(1, 0) = 43;
  expected(1, 1) = 50;

  a.MulMatrix(b);

  EXPECT_TRUE(a == expected);
}
TEST(S21MatrixTest, MulNumber) {
  S21Matrix a(2, 2);
  S21Matrix expected(2, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(1, 0) = 3;
  a(1, 1) = 4;

  expected(0, 0) = 2;
  expected(0, 1) = 4;
  expected(1, 0) = 6;
  expected(1, 1) = 8;

  a.MulNumber(2);

  EXPECT_TRUE(a == expected);
}
TEST(S21MatrixTest, Transpose) {
  S21Matrix a(2, 4);
  S21Matrix b(4, 2);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;
  a(0, 3) = 4;
  a(1, 0) = 5;
  a(1, 1) = 6;
  a(1, 2) = 7;
  a(1, 3) = 8;

  b(0, 0) = 1;
  b(0, 1) = 5;
  b(1, 0) = 2;
  b(1, 1) = 6;
  b(2, 0) = 3;
  b(2, 1) = 7;
  b(3, 0) = 4;
  b(3, 1) = 8;

  a = a.Transpose();
  EXPECT_EQ(1, a == b);
}
TEST(S21MatrixTest, Determinant) {
  S21Matrix a(3, 3);

  a(0, 0) = 4;
  a(0, 1) = 6;
  a(0, 2) = 5;
  a(1, 0) = 7;
  a(1, 1) = 8;
  a(1, 2) = 8;
  a(2, 0) = 1;
  a(2, 1) = 14;
  a(2, 2) = 4;

  double determ = a.Determinant();
  EXPECT_EQ(10, determ);
}
TEST(S21MatrixTest, Inverse) {
  S21Matrix R(3, 3);
  R(0, 0) = 8;
  R(0, 1) = 2;
  R(0, 2) = 4;
  R(1, 0) = 4;
  R(1, 1) = 6;
  R(1, 2) = 6;
  R(2, 0) = 4;
  R(2, 1) = 8;
  R(2, 2) = 8;

  S21Matrix result(3, 3);
  result(0, 0) = 0;
  result(0, 1) = 1;
  result(0, 2) = -0.75;
  result(1, 0) = -0.5;
  result(1, 1) = 3;
  result(1, 2) = -2;
  result(2, 0) = 0.5;
  result(2, 1) = -3.5;
  result(2, 2) = 2.5;

  S21Matrix result_inverse(3, 3);
  result_inverse = R.InverseMatrix();
  EXPECT_EQ(1, result == result_inverse);
}
TEST(S21MatrixTest, CalcComplents) {
  S21Matrix mat1(3, 3);
  mat1(0, 0) = 13;
  mat1(0, 1) = 1;
  mat1(0, 2) = 12;
  mat1(1, 0) = 10;
  mat1(1, 1) = 8;
  mat1(1, 2) = 10;
  mat1(2, 0) = 1;
  mat1(2, 1) = 12;
  mat1(2, 2) = 9;

  S21Matrix trueMat(3, 3);
  trueMat(0, 0) = -48;
  trueMat(0, 1) = -80;
  trueMat(0, 2) = 112;
  trueMat(1, 0) = 135;
  trueMat(1, 1) = 105;
  trueMat(1, 2) = -155;
  trueMat(2, 0) = -86;
  trueMat(2, 1) = -10;
  trueMat(2, 2) = 94;

  mat1 = mat1.CalcComplements();
  EXPECT_EQ(1, mat1 == trueMat);
}
TEST(S21MatrixTest, OperatorEq1) {
  S21Matrix mat(2, 2);
  S21Matrix copyMat(2, 2);

  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;

  copyMat = std::move(mat);
  EXPECT_EQ(1, mat == copyMat);
}
TEST(S21MatrixTest, OperatorEq2) {
  S21Matrix mat(2, 2);
  S21Matrix copyMat(2, 2);

  mat(0, 0) = 1;
  mat(0, 1) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;

  copyMat = mat;
  EXPECT_EQ(1, mat == copyMat);
}
TEST(S21MatrixTest, OperatorSkobki) {
  const S21Matrix mat(1, 1);

  const double result = 0;
  EXPECT_EQ(1, mat(0, 0) == result);
}
TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;
  A = B + B;
  EXPECT_EQ(false, A == B);
}
TEST(S21MatrixTest, OperatorMinus) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;
  A = B - B;
  EXPECT_EQ(1, A == B);
}
TEST(S21MatrixTest, OperatorPlusEq) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;
  A += B;
  EXPECT_EQ(1, A == B);
}
TEST(S21MatrixTest, OperatorMinusEq) {
  S21Matrix A(3, 4);
  S21Matrix B(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 4;
  A(1, 0) = 5;
  A(1, 1) = 6;
  A(1, 2) = 7;
  A(1, 3) = 8;
  A(2, 0) = 9;
  A(2, 1) = 10;
  A(2, 2) = 11;
  A(2, 3) = 12;
  A -= B;
  B -= B;
  EXPECT_EQ(1, A == B);
}
TEST(S21MatrixTest, OperatorMulNumberEq) {
  S21Matrix B(3, 4);
  S21Matrix A(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;

  A(0, 0) = 2;
  A(0, 1) = 4;
  A(0, 2) = 6;
  A(0, 3) = 8;
  A(1, 0) = 10;
  A(1, 1) = 12;
  A(1, 2) = 14;
  A(1, 3) = 16;
  A(2, 0) = 18;
  A(2, 1) = 20;
  A(2, 2) = 22;
  A(2, 3) = 24;

  B *= 2;
  EXPECT_EQ(1, B == A);
}
TEST(S21MatrixTest, OperatorMulMatrixEq) {
  S21Matrix B(2, 2);
  S21Matrix A(2, 2);
  S21Matrix expected(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  expected(0, 0) = 11;
  expected(0, 1) = 14;
  expected(1, 0) = 35;
  expected(1, 1) = 46;

  B *= A;
  EXPECT_EQ(1, B == expected);
}
TEST(S21MatrixTest, OperatorMulMatrix) {
  S21Matrix B(2, 2);
  S21Matrix A(2, 2);
  S21Matrix expected(2, 2);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(1, 0) = 5;
  B(1, 1) = 6;

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 5;
  A(1, 1) = 6;

  expected(0, 0) = 11;
  expected(0, 1) = 14;
  expected(1, 0) = 35;
  expected(1, 1) = 46;

  B = B * A;
  EXPECT_EQ(1, B == expected);
}
TEST(S21MatrixTest, OperatorMulNumber) {
  S21Matrix B(3, 4);
  S21Matrix A(3, 4);
  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(0, 3) = 4;
  B(1, 0) = 5;
  B(1, 1) = 6;
  B(1, 2) = 7;
  B(1, 3) = 8;
  B(2, 0) = 9;
  B(2, 1) = 10;
  B(2, 2) = 11;
  B(2, 3) = 12;

  A(0, 0) = 2;
  A(0, 1) = 4;
  A(0, 2) = 6;
  A(0, 3) = 8;
  A(1, 0) = 10;
  A(1, 1) = 12;
  A(1, 2) = 14;
  A(1, 3) = 16;
  A(2, 0) = 18;
  A(2, 1) = 20;
  A(2, 2) = 22;
  A(2, 3) = 24;

  B = B * 2;
  EXPECT_EQ(1, B == A);
}
TEST(S21MatrixTest, ErrorInEqMatrixs) {
  S21Matrix A(2, 3);
  S21Matrix B(2, 2);
  EXPECT_THROW(A.EqMatrix(B), std::length_error);
}
TEST(S21MatrixTest, ErrorInSumMatrix1) {
  S21Matrix A;
  S21Matrix B;
  EXPECT_THROW(A.SumMatrix(B), std::length_error);
}
TEST(S21MatrixTest, ErrorInSumMatrix2) {
  S21Matrix A(2, 3);
  S21Matrix B(3, 3);
  EXPECT_THROW(A.SumMatrix(B), std::length_error);
}
TEST(S21MatrixTest, ErrorInSubMatrix1) {
  S21Matrix A;
  S21Matrix B;
  EXPECT_THROW(A.SubMatrix(B), std::length_error);
}
TEST(S21MatrixTest, ErrorInSubMatrix2) {
  S21Matrix A(2, 3);
  S21Matrix B(2, 4);
  EXPECT_THROW(A.SubMatrix(B), std::length_error);
}
TEST(S21MatrixTest, ErrorInMulNumber) {
  S21Matrix A;
  EXPECT_THROW(A.MulNumber(3), std::length_error);
}
TEST(S21MatrixTest, ErrorInMulMatrix) {
  S21Matrix A(3, 3);
  S21Matrix B;
  EXPECT_THROW(A.MulMatrix(B), std::length_error);
}
TEST(S21MatrixTest, ErrorInTranspose) {
  S21Matrix A;
  EXPECT_THROW(A.Transpose(), std::length_error);
}
TEST(S21MatrixTest, ErrorInCalcComplements) {
  S21Matrix A(5, 7);
  EXPECT_THROW(A.CalcComplements(), std::length_error);
}
TEST(S21MatrixTest, ErrorInDeterminant1) {
  S21Matrix A;
  EXPECT_THROW(A.Determinant(), std::length_error);
}
TEST(S21MatrixTest, ErrorInDeterminant2) {
  S21Matrix A(1, 2);
  EXPECT_THROW(A.Determinant(), std::length_error);
}
TEST(S21MatrixTest, ErrorInInverseMatrix1) {
  S21Matrix A;
  EXPECT_THROW(A.InverseMatrix(), std::length_error);
}
TEST(S21MatrixTest, ErrorInInverseMatrix2) {
  S21Matrix A(2, 2);
  EXPECT_THROW(A.InverseMatrix(), std::length_error);
}
TEST(S21MatrixTest, ErrorInMinorMatrix) {
  S21Matrix A(2, 2);
  EXPECT_THROW(A.Minor(2, 1), std::length_error);
}
TEST(S21MatrixTest, ErrorInOperatorSkobki1) {
  S21Matrix B(2, 2);
  EXPECT_THROW((B(0, 5) = 2), std::length_error);
}
TEST(S21MatrixTest, ErrorInOperatorSkobki2) {
  S21Matrix A(1, 1);
  A(0, 0) = 1;
  EXPECT_EQ(A(0, 0), 1);
}
TEST(S21MatrixTest, ErrorInSetRows1) {
  S21Matrix A;
  EXPECT_THROW(A.SetRows(0), std::length_error);
}
TEST(S21MatrixTest, ErrorInSetRows2) {
  S21Matrix A(1, 1);
  S21Matrix B(3, 3);
  A.SetRows(3);
  EXPECT_EQ(A.GetRows(), B.GetRows());
}
TEST(S21MatrixTest, ErrorInSetCols1) {
  S21Matrix A;
  EXPECT_THROW(A.SetCols(0), std::length_error);
}
TEST(S21MatrixTest, ErrorInSetCols2) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 2);
  A.SetCols(2);
  EXPECT_EQ(A.GetCols(), B.GetCols());
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}