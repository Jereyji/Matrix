#include "s21_matrix_oop.h"

#include <stdexcept>

// Конструктор по умолчанию
S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

// Параметризированный конструктор с количеством строк и столбцов
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw std::length_error(
        "Exception in constructor! Incorrect size by rows or columns!");
  }
  matrix_ = new double *[rows];

  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_];
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0;
    }
  }
}

// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix &other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Конструктор перемещения
S21Matrix::S21Matrix(S21Matrix &&other) noexcept : S21Matrix() {
  SwapMatrix(std::move(other));
}

// Деструктор
S21Matrix::~S21Matrix() noexcept {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
  }
}

// ПЕРЕГРУЗКА ОПЕРАТОРОВ

S21Matrix S21Matrix::operator+(const S21Matrix &matrixAnother) {
  S21Matrix matrixResult(*this);
  matrixResult.SumMatrix(matrixAnother);
  return matrixResult;
}

S21Matrix S21Matrix::operator-(const S21Matrix &matrixAnother) {
  S21Matrix matrixResult(*this);
  matrixResult.SubMatrix(matrixAnother);
  return matrixResult;
}

S21Matrix S21Matrix::operator*(const double number) {
  S21Matrix matrixResult(*this);
  matrixResult.MulNumber(number);
  return matrixResult;
}

S21Matrix S21Matrix::operator*(const S21Matrix &matrixAnother) {
  S21Matrix matrixResult(*this);
  matrixResult.MulMatrix(matrixAnother);
  return matrixResult;
}

// Перегрузка с переносом
S21Matrix &S21Matrix::operator=(S21Matrix &&matrixAnother) {
  if (this != &matrixAnother) {
    SwapMatrix(std::move(matrixAnother));
  }
  return *this;
}

// Перегрузка копированием
S21Matrix &S21Matrix::operator=(S21Matrix &matrixAnother) {
  S21Matrix copy(matrixAnother);
  SwapMatrix(std::move(copy));
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &matrixAnother) const {
  return EqMatrix(matrixAnother);
}

void S21Matrix::operator+=(const S21Matrix &matrixAnother) {
  SumMatrix(matrixAnother);
}

void S21Matrix::operator-=(const S21Matrix &matrixAnother) {
  SubMatrix(matrixAnother);
}

void S21Matrix::operator*=(const double number) { MulNumber(number); }

void S21Matrix::operator*=(const S21Matrix &matrixAnother) {
  MulMatrix(matrixAnother);
}

double &S21Matrix::operator()(int i, int j) {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::length_error(
        "Excepton in overloading brackets! Incorrect row or column index!");
  }
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  if (i < 0 || i >= rows_ || j < 0 || j >= cols_) {
    throw std::length_error(
        "Excepton in overloading brackets! Incorrect row or column index!");
  }
  return matrix_[i][j];
}

// ОСНОВНЫЕ МЕТОДЫ

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (CheckMatrix() || other.CheckMatrix()) {
    throw std::length_error(
        "Exception in the SumMatrix method! Incorrect matrix!");
  } else if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::length_error(
        "Exception in the SumMatrix method! Rows no equal Columns!");
  }
  bool check = false;

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (matrix_[i][j] - other.matrix_[i][j] <= 1e-7) {
        check = true;
      } else {
        return false;
      }
    }
  }
  return check;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (CheckMatrix() || other.CheckMatrix()) {
    throw std::length_error(
        "Exception in the SumMatrix method! Incorrect matrix!");
  } else if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::length_error(
        "Exception in the SumMatrix method! Rows no equal Columns!");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (CheckMatrix() || other.CheckMatrix()) {
    throw std::length_error(
        "Exception in the SumMatrix method! Incorrect matrix!");
  } else if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::length_error(
        "Exception in the SumMatrix method! Rows no equal Columns!");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (CheckMatrix()) {
    throw std::length_error(
        "Exception in the MulMatrix method! Incorrect matrix!");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (CheckMatrix() || other.CheckMatrix() || cols_ != other.rows_) {
    throw std::length_error(
        "Exception in the MulMatrix method! Incorrect matrix(s)!");
  }
  S21Matrix m1(rows_, other.cols_);

  for (int i = 0; i < m1.rows_; ++i) {
    for (int j = 0; j < m1.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        m1.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(m1);
}

S21Matrix S21Matrix::Transpose() const {
  if (CheckMatrix()) {
    throw std::length_error(
        "Exception in the Transpose method! Incorrect matrix!");
  }
  S21Matrix TransposeMatrix(cols_, rows_);

  for (int j = 0; j < TransposeMatrix.rows_; ++j) {
    for (int i = 0; i < TransposeMatrix.cols_; ++i) {
      TransposeMatrix.matrix_[j][i] = matrix_[i][j];
    }
  }
  return TransposeMatrix;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (CheckMatrix() || rows_ != cols_) {
    throw std::length_error(
        "Exception in the CalcComplements method! Incorrect matrix!");
  }
  S21Matrix calcMatrix(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      calcMatrix.matrix_[i][j] = Minor(i, j).Determinant() * GetSign(i, j);
    }
  }
  return calcMatrix;
}

double S21Matrix::Determinant() const {
  if (CheckMatrix() || rows_ != cols_) {
    throw std::length_error(
        "Exception in the determinant method! Incorrect matrix!");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }
  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }

  double determinant = 0;

  for (int j = 0; j < cols_; ++j) {
    determinant += Minor(0, j).Determinant() * GetSign(0, j) * matrix_[0][j];
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double opredelitel = Determinant();
  if (!opredelitel) {
    throw std::length_error(
        "Exception in the InverseMatrix method! The determinant of matrix is "
        "zero!");
  }
  S21Matrix resultMatrix(rows_, cols_);
  S21Matrix calcMatrix(CalcComplements());
  S21Matrix transpMatrix(calcMatrix.Transpose());

  for (int i = 0; i < transpMatrix.rows_; ++i) {
    for (int j = 0; j < transpMatrix.cols_; ++j) {
      resultMatrix.matrix_[i][j] =
          (1 / opredelitel) * transpMatrix.matrix_[i][j];
    }
  }
  return resultMatrix;
}

// ГЕТТЕРЫ

double S21Matrix::GetRows() const { return rows_; }

double S21Matrix::GetCols() const { return cols_; }

// СЕТТЕРЫ

void S21Matrix::SetRows(int row) { ResizeMatrix(row, cols_); }

void S21Matrix::SetCols(int col) { ResizeMatrix(rows_, col); }

// Вспомогательные функции

// Минор матрицы
S21Matrix S21Matrix::Minor(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::length_error("Exception in the Minor method! Incorrect matrix!");
  }
  S21Matrix minorMatrix(rows_ - 1, cols_ - 1);

  for (int i = 0, di = 0; i < rows_; ++i) {
    if (i == row) {
      continue;
    }
    for (int j = 0, dj = 0; j < cols_; ++j) {
      if (j == col) {
        continue;
      }
      minorMatrix.matrix_[di][dj] = matrix_[i][j];
      ++dj;
    }
    ++di;
  }
  return minorMatrix;
}

// Изменение размера матрицы
void S21Matrix::ResizeMatrix(int row, int col) {
  S21Matrix copyMatrix(row, col);

  for (int i = 0; i < rows_ && i < row; ++i) {
    for (int j = 0; j < cols_ && j < col; ++j) {
      copyMatrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(copyMatrix);
}

// Swap матрицы
void S21Matrix::SwapMatrix(S21Matrix &&other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

// Получение знака значения матрицы
int S21Matrix::GetSign(int i, int j) const {
  return ((i + j) % 2 == 1) ? -1 : 1;
}

// Проверка матрицы на корректность
bool S21Matrix::CheckMatrix() const {
  return matrix_ == nullptr || rows_ < 1 || cols_ < 1;
}
