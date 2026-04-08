#include "matrix/matrix.hpp"
#include "matrix/utils.hpp"
#include <cmath>
#include <expected>
#include <filesystem>
#include <print>
#include <span>
#include <string>
using ll = long long;

std::expected<Vec, std::string> solveUpperTriangular(const Mat &A,
                                                     const Vec &b) {
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
          return std::unexpected("Not a Upper triangular matrix");
      } else if (i == j) {
        xi += b[i];
      } else {
        xi -= A[i, j] * soln[j];
      }
    }
    if (A[i, i] == 0) {
      return std::unexpected("Not invertible");
    }
    soln[i] = xi / A[i, i];
  }

  return soln;
}

std::expected<Vec, std::string> solveLowerTriangular(const Mat &A,
                                                     const Vec &b) {
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
          return std::unexpected("Not a lower triangular matrix");
      } else if (i == j) {
        xi += b[i];
      } else {
        xi -= A[i, j] * soln[j];
      }
    }
    if (A[i, i] == 0) {
      return std::unexpected("Not invertible");
    }
    soln[i] = xi / A[i, i];
  }

  return soln;
}

std::expected<Mat, std::string> getCholeskyDecomposition(const Mat &A) {
  ll n = A.getDim().first;
  Mat L(n, n);

  for (ll i = 0; i < n; i++) {
    for (ll j = 0; j <= i; j++) {
      float sum = 0;

      for (ll k = 0; k < j; k++) {
        sum += L[j, k] * L[i, k];
      }

      if (i == j) {
        float d = A[i, i] - sum;
        if (d <= 1e-9)
          return std::unexpected("Not Positive Definite");
        L[i, j] = std::sqrt(d);
      } else {
        L[i, j] = (A[i, j] - sum) / L[j, j];
      }
    }
  }

  return L;
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

  auto A_result = readMatrixFromFile(matrixFile);
  if (!A_result) {
    std::println(stderr, "Error: {}", A_result.error());
    return 1;
  }
  Mat A = A_result.value();

  auto b_result = readVectorFromFile(vectorFile);
  if (!b_result) {
    std::println(stderr, "Error: {}", b_result.error());
    return 1;
  }
  Vec b = b_result.value();

  auto L_result = getCholeskyDecomposition(A);

  if (!L_result) {
    std::println(stderr, "Error: {}", L_result.error());
    return 1;
  }


  Mat L = L_result.value();
	std::println("L");
  L.display();
  std::println();

  auto z_result = solveLowerTriangular(L, b);

  if (!z_result) {
    std::println(stderr, "Error: {}", z_result.error());
    return 1;
  }

	std::println("z = L^-1 b");
  Vec z = z_result.value();

  z.display();
  std::println();

  L.transposeInPlace();
	std::println("L^T");
  L.display();
  std::println();

  auto x_result = solveUpperTriangular(L, z);

  if (!x_result) {
    std::println(stderr, "Error: {}", x_result.error());
    return 1;
  }

	std::println("x = L^T^-1 z");
  Vec x = x_result.value();

  x.display();
  std::println();
}
