#include "matrix.hpp"
#include "utils.hpp"
#include <cstddef>
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

int main(int argc, char *argv[]) {

  std::span<char *> args(argv, argc);
  if (args.size() < 2) {
    std::println("Give matrix and vector files.\nUsage ./a.out <matrix> "
                 "<vector> <solution[optional]>");
		return 1;
  }
  std::filesystem::path matrixFile(args[1]);
  std::filesystem::path vectorFile(args[2]);
  std::filesystem::path solutionFile;

  if (args.size() > 3)
    solutionFile = std::filesystem::path(args[3]);

  auto L_result = readMatrixFromFile(matrixFile);
  if (!L_result) {
    std::println(stderr, "Error: {}", L_result.error());
    return 1;
  }
  Mat L = L_result.value();

  auto b_result = readVectorFromFile(vectorFile);
  if (!b_result) {
    std::println(stderr, "Error: {}", b_result.error());
    return 1;
  }
  Vec b = b_result.value();

  Vec ans = solveLowerTriangular(L, b);

  if (!solutionFile.empty()) {
    auto ans_result = readVectorFromFile(vectorFile);
    if (!ans_result) {
      std::println(stderr, "Error: {}", ans_result.error());
      return 1;
    }
    Vec actualAns = ans_result.value();
    std::cout << (ans == actualAns ? "Correct Solution" : "Wrong Solution")
              << std::endl;
  }

  ans.display();
}
