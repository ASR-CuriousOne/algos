#pragma once
#include <functional>

template <typename T, typename Op = std::plus<T>> class FenwickTree {
private:
  int n;
  std::vector<T> tree;
  Op op;
  T identity;

public:
  FenwickTree(int size, T identity_val, Op operation = Op())
      : n(size), tree(size + 1, identity_val), identity(identity_val),
        op(operation) {}

  void update(int i, T delta) {
    for (; i <= n; i += i & (-i)) {
      tree[i] = op(tree[i], delta);
    }
  }

  T queryPrefix(int i) const {
    T res = identity;
    for (; i > 0; i -= i & (-i)) {
      res = op(res, tree[i]);
    }
    return res;
  }

  template <typename InvOp>
  T queryRange(int left, int right, InvOp invOp) const {
    return invOp(queryPrefix(right), queryPrefix(left - 1));
  }
};
