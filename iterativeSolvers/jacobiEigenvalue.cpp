#include "matrix.hpp"
#include "utils.hpp"
#include <climits>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <print>
#include <span>
using ll = long long;

Mat jacobiEigenvalue(const Mat &A, const int numOfIters) {
  Mat D = A;
  ll n = D.getDim().first;

  for (ll iter = 0; iter < numOfIters; iter++) {
    float maxOffDiag = INT_MIN;
    ll max_i = -1, max_j = -1;

    for (ll i = 0; i < n; i++) {
      for (ll j = 0; j < i; j++) {
        if (std::abs(D[i, j]) > maxOffDiag) {
          maxOffDiag = std::abs(D[i, j]);
          max_i = i;
          max_j = j;
        }
      }
    }

		if (maxOffDiag < 1e-9f) {
			std::println("Converged after {} iterations", iter);
      break; 
    }

    float d_ii = D[max_i, max_i];
    float d_jj = D[max_j, max_j];
    float d_ij = D[max_i, max_j];
    float tau = (d_jj - d_ii) / (2.0f * d_ij);

    float t = (tau >= 0 ? 1.0f : -1.0f) /
              (std::abs(tau) + std::sqrt(1.0f + tau * tau));

    float c = 1.0f / std::sqrt(1.0f + t * t);
    float s = t * c;

    D[max_i, max_i] = (c * c * d_ii) - (2.0f * s * c * d_ij) + (s * s * d_jj);
    D[max_j, max_j] = (s * s * d_ii) + (2.0f * s * c * d_ij) + (c * c * d_jj);

    D[max_i, max_j] = 0;
    D[max_j, max_i] = 0;

    for (ll k = 0; k < n; k++) {
      if (k == max_i || k == max_j)
        continue;

      float D_ik = D[max_i, k];
    	float D_jk = D[max_j, k];

      D[max_i, k] = (c * D_ik) - (s * D_jk);
      D[max_j, k] = (s * D_ik) + (c * D_jk);

      D[k, max_i] = D[max_i, k];
      D[k, max_j] = D[max_j, k];
    }
  }
  return D;
}

int main(int argc, char *argv[]) {
  std::span<char *> args(argv, argc);

  if (args.size() < 3) {
    std::println("Insufficient number of arguments provided.\nUsage "
                 "./jacobiEigenvalue.out <num of iters> <matrixFile>");
    return 1;
  }

  int numberOfIters = std::stoi(args[1]);
  std::filesystem::path matrixFile(args[2]);

	auto A_result = readMatrixFromFile(matrixFile);
  if (!A_result) {
    std::println(stderr, "Error: {}", A_result.error());
    return 1;
  }
  Mat A = A_result.value();

	Mat D = jacobiEigenvalue(A, numberOfIters);

	D.display();
}
