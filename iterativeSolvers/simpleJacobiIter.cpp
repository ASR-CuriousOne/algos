#include "matrix.hpp"
#include "utils.hpp"
#include <cstddef>
#include <print>
#include <span>
#include <string>

Vec solveJacobiIter(const Mat &A, const Vec &b, int numberOfIters) {
  Vec ans(b.getDim().first);
  Mat DInv(A.getDim()), LPlusU(A.getDim());

  for (size_t i = 0; i < A.getDim().first; i++) {
    for (size_t j = 0; j < A.getDim().second; j++) {
      if (i == j)
        DInv[i, j] = 1 / A[i, j];
      else
        LPlusU[i, j] = A[i, j];
    }
  }

  for (size_t k = 0; k < numberOfIters; k++) {
    ans = DInv * (b - (LPlusU)*ans);
  }

  return ans;
}

int main(int argc, char *argv[]) {
  std::span<char *> args(argv, argc);

  if (args.size() < 3) {
    std::println(
        "Insufficient number of arguments provided.\nUsage "
        "./simpleJacobiIter.out <num of iters> <matrixFile> <vectorFile> "
        "<solutionFile[optional]>");
    return 1;
  }

  int numberOfIters = std::stoi(args[1]);
  std::filesystem::path matrixFile(args[2]);
  std::filesystem::path vectorFile(args[3]);
  std::filesystem::path solutionFile;

  if (args.size() > 4)
    solutionFile = std::filesystem::path(args[4]);

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
	A.display();
	std::cout << std::endl;

	b.display();
	std::cout << std::endl;
  Vec ans = solveJacobiIter(A, b, numberOfIters);

  if (!solutionFile.empty()) {
    auto ans_result = readVectorFromFile(solutionFile);
    if (!ans_result) {
      std::println(stderr, "Error: {}", ans_result.error());
      return 1;
    }
    Vec actualAns = ans_result.value();
    if (actualAns == ans) {
      std::println("Correct Ans");
			ans.display();
    } else {
      std::println("Wrong Ans");
      std::cout << '\n';
      std::println("Actual Ans");
      actualAns.display();
      std::cout << '\n';
      std::println("Calculated Ans");
      ans.display();
    }

  } else
    ans.display();
}
