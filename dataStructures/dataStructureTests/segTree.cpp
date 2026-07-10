#include <algorithm>
#include <iostream>
#include <rangeQueries/segTree.hpp>

int main() {
    auto maxFunc = [](const int a, const int b) { return std::max(a, b); };

    const size_t n = 10;

    SegTree<int, decltype(maxFunc)> maxSegTree(n,
                                               std::numeric_limits<int>::min());

    for (size_t i = 0; i < n; i++) {
        maxSegTree.update(i, i);
    }

    std::cout << maxSegTree.query(1, 3) << '\n';
    std::cout << maxSegTree.query(0, 9) << '\n';

    maxSegTree.update(0, 10);

    std::cout << maxSegTree.query(1, 3) << '\n';
    std::cout << maxSegTree.query(0, 9) << '\n';
}
