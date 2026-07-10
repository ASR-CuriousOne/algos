#include <functional>
#include <vector>

template <typename ValueType, typename BinaryOp = std::plus<ValueType>>
class SegTree {
  public:
    SegTree(size_t n, ValueType identity, BinaryOp binaryOp = BinaryOp())
        : n(n), m_tree(2 * n, 0), identity(identity), binaryOp(binaryOp) {}

    void update(size_t pos, ValueType value) {
        for (m_tree[pos += n] = value; pos > 1; pos >>= 1) {
            m_tree[pos >> 1] = binaryOp(m_tree[pos & ~1], m_tree[pos | 1]);
        }
    }

    ValueType query(size_t l, size_t r) {
        ValueType resLeft = identity;
        ValueType resRight = identity;

        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                resLeft = binaryOp(resLeft, m_tree[l++]);
            if (r & 1)
                resRight = binaryOp(m_tree[--r], resRight);
        }

        return binaryOp(resLeft, resRight);
    }

  private:
    size_t n;
    std::vector<ValueType> m_tree;
    ValueType identity;
    BinaryOp binaryOp;
};
