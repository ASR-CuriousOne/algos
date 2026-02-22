#include "fenwickTree.hpp"
#include <print>

int main() {
  FenwickTree<long long> sumTree(10, 0LL);

  sumTree.update(3, 5);
  sumTree.update(5, 2);

  std::println("{}", sumTree.queryRange(2, 5, std::minus<long long>()));

  const int MIN_VAL = -1e9;
  FenwickTree<int, const int &(*)(const int &, const int &)> maxTree(
      10, MIN_VAL, std::max<int>);

  maxTree.update(2, 10);
  maxTree.update(4, 25);
  maxTree.update(7, 15);

  std::println("{}", maxTree.queryPrefix(5));

  FenwickTree<int, std::bit_xor<int>> xorTree(10, 0);

  xorTree.update(1, 4);
  xorTree.update(2, 7);

	std::println("{}",xorTree.queryRange(1, 2, std::bit_xor<int>()));
}
