class S21Matrix {
 public:
  // Конструкторы
  S21Matrix() noexcept;

  S21Matrix(int rows, int cols);

  S21Matrix(const S21Matrix& other);

  S21Matrix(S21Matrix&& other) noexcept;

  // Деструктор
  ~S21Matrix() noexcept;

  // Перегрузка операторов
  S21Matrix operator+(const S21Matrix& matrixAnother);

  S21Matrix operator-(const S21Matrix& matrixAnother);

  S21Matrix operator*(const double number);

  S21Matrix operator*(const S21Matrix& matrixAnother);

  S21Matrix& operator=(S21Matrix&& matrixAnother);

  S21Matrix& operator=(S21Matrix& matrixAnother);

  bool operator==(const S21Matrix& matrixAnother) const;

  void operator+=(const S21Matrix& matrixAnother);

  void operator-=(const S21Matrix& matrixAnother);

  void operator*=(const double number);

  void operator*=(const S21Matrix& matrixAnother);

  double& operator()(int i, int j);

  const double& operator()(int i, int j) const;

  // Основные методы
  bool EqMatrix(const S21Matrix& other) const;

  void SumMatrix(const S21Matrix& other);

  void SubMatrix(const S21Matrix& other);

  void MulNumber(const double num);

  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose() const;

  S21Matrix CalcComplements() const;

  double Determinant() const;

  S21Matrix InverseMatrix() const;

  // Геттеры

  double GetRows() const;

  double GetCols() const;

  // Сеттеры

  void SetRows(int row);

  void SetCols(int col);

  // Вспомогательные методы

  S21Matrix Minor(int row, int col) const;

  int GetSign(int i, int j) const;

  void ResizeMatrix(int row, int col);

  bool CheckMatrix() const;

  void SwapMatrix(S21Matrix&& other);

 private:
  int rows_, cols_;

  double** matrix_;
};
