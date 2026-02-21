#include "matrix.hpp"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <print>
#include <span>
#include <stdexcept>
#include <utility>

Vec solveLowerTriangular(const Mat &A, const Vec &b) {
  assert(A.getDim().first == A.getDim().second &&
         A.getDim().second == b.getDim().first &&
         "Matrix vector size mismatch");

  const size_t n = b.getDim().first;

  Vec soln(n);

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

Vec solveUpperTriangular(const Mat &A, const Vec &b) {
  assert(A.getDim().first == A.getDim().second &&
         A.getDim().second == b.getDim().first &&
         "Matrix vector size mismatch");

  const size_t n = b.getDim().first;

  Vec soln(n);

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

Mat readMatrixFromFile(const std::filesystem::path &filename) {
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

  Mat M(rows, cols);
  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      file >> M[i, j];
    }
  }
  return M;
}

Vec readVectorFromFile(const std::filesystem::path &filename) {
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

  Vec v(size);
  for (size_t i = 0; i < size; ++i) {
    file >> v[i];
  }
  return v;
}

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

  Mat L = readMatrixFromFile(matrixFile);
  Vec b = readVectorFromFile(vectorFile);

  Vec ans = solveLowerTriangular(L, b);

  if (!solutionFile.empty()) {
    Vec actualAns = readVectorFromFile(solutionFile);
    std::cout << (ans == actualAns ? "Correct Solution" : "Wrong Solution")
              << std::endl;
  }

  ans.display();
}
