#include "matrix.hpp"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <print>
#include <span>
#include <stdexcept>
#include <utility>

using mat = Matrix<float>;

template <typename T> class ColumnVector : public Matrix<T> {
public:
  ColumnVector(size_t n) : Matrix<T>(n, 1) {}

  ColumnVector(const Matrix<T> &m) : Matrix<T>(m) {
    assert(m.getDim().second == 1 &&
           "Matrix must be n x 1 to become a ColumnVector");
  }

  T &operator[](size_t i) { return Matrix<T>::operator[](i, 0); }

  T operator[](size_t i) const { return Matrix<T>::operator[](i, 0); }

  using Matrix<T>::operator*;
  T operator*(const ColumnVector<T> &other) const {
    assert(this->getDim().first == other.getDim().first &&
           "Vectors must be the same length");

    T dotProduct = 0;
    size_t length = this->getDim().first;

    for (size_t i = 0; i < length; ++i) {
      dotProduct += (*this)[i] * other[i];
    }

    return dotProduct;
  }

  double determinant() const = delete;

  Matrix<T> get_minor(size_t row_to_remove,
                      size_t col_to_remove) const = delete;
};

using vec = ColumnVector<float>;

vec solveLowerTriangular(const mat &A, const vec &b) {
  assert(A.getDim().first == A.getDim().second &&
         A.getDim().second == b.getDim().first &&
         "Matrix vector size mismatch");

  const size_t n = b.getDim().first;

  vec soln(n);

  for (size_t i = 0; i < n; i++) {
    float xi = 0;
    for (size_t j = 0; j < n; j++) {
      if (j > i) {
        if (A[i, j] != 0)
          throw std::runtime_error("Not a lower triangular matrix");
      } else if (i == j) {
        xi += b[i];
      } else {
        xi -= A[i, j] * soln[j];
      }
    }
    if (A[i, i] == 0) {
      throw std::runtime_error("Not invertible");
    }
    soln[i] = xi / A[i, i];
  }

  return soln;
}

vec solveUpperTriangular(const mat &A, const vec &b) {
  assert(A.getDim().first == A.getDim().second &&
         A.getDim().second == b.getDim().first &&
         "Matrix vector size mismatch");

  const size_t n = b.getDim().first;

  vec soln(n);

  for (long long i = n - 1; i >= 0; i--) {
    float xi = 0;
    for (long long j = n - 1; j >= 0; j--) {
      if (j < i) {
        if (A[i, j] != 0)
          throw std::runtime_error("Not a Upper triangular matrix");
      } else if (i == j) {
        xi += b[i];
      } else {
        xi -= A[i, j] * soln[j];
      }
    }
    if (A[i, i] == 0) {
      throw std::runtime_error("Not invertible");
    }
    soln[i] = xi / A[i, i];
  }

  return soln;
}

mat readMatrixFromFile(const std::filesystem::path &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open matrix file: " +
                             filename.string());
  }

  size_t rows, cols;
  if (!(file >> rows >> cols)) {
    throw std::runtime_error("Failed to read matrix dimensions from " +
                             filename.string());
  }

  mat M(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      file >> M[i, j];
    }
  }
  return M;
}

vec readVectorFromFile(const std::filesystem::path &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open vector file: " +
                             filename.string());
  }

  size_t size;
  if (!(file >> size)) {
    throw std::runtime_error("Failed to read vector size from " +
                             filename.string());
  }

  vec v(size);
  for (size_t i = 0; i < size; ++i) {
    file >> v[i];
  }
  return v;
}

// L U

int main(int argc, char *argv[]) {

  std::span<char *> args(argv, argc);
  if (args.size() < 2) {
    std::println("Give matrix and vector files.\nUsage ./a.out <matrix> "
                 "<vector> <solution[optional]>");
  }
  std::filesystem::path matrixFile(args[1]);
  std::filesystem::path vectorFile(args[2]);
  std::filesystem::path solutionFile;

  if (args.size() > 3)
    solutionFile = std::filesystem::path(args[3]);

  mat L = readMatrixFromFile(matrixFile);
  mat b = readVectorFromFile(vectorFile);

  vec ans = solveLowerTriangular(L, b);

  if (!solutionFile.empty()) {
    vec actualAns = readVectorFromFile(solutionFile);
    std::cout << (ans == actualAns ? "Correct Solution" : "Wrong Solution")
              << std::endl;
  }

  ans.display();
}
