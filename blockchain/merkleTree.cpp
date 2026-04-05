#include <iostream>
#include <print>
#include <vector>
using ll = long long;

class MerkleTree {
private:
  std::vector<std::string> m_tree;
  ll m_numLeaves;

  std::string computeHash(const std::string &data) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(data));
  }

  void buildTree(const std::vector<std::string> &leaves) {
    if (leaves.empty())
      return;

    m_numLeaves = leaves.size();

    std::vector<std::string> currentLevel = leaves;

    std::vector<std::vector<std::string>> levels;
    levels.push_back(currentLevel);

    while (currentLevel.size() > 1) {
      std::vector<std::string> nextLevel;
      for (size_t i = 0; i < currentLevel.size(); i += 2) {
        std::string left = currentLevel[i];
        std::string right = (i + 1 < currentLevel.size()) ? currentLevel[i + 1]
                                                          : currentLevel[i];
        nextLevel.push_back(computeHash(left + right));
      }
      levels.push_back(nextLevel);
      currentLevel = nextLevel;
    }

    for (auto it = levels.rbegin(); it != levels.rend(); it++) {
      m_tree.insert(m_tree.end(), it->begin(), it->end());
    }
  }

public:
  MerkleTree(const std::vector<std::string> &transactions) {
    std::vector<std::string> hashedLeaves;
    for (const auto &tx : transactions) {
      hashedLeaves.push_back(computeHash(tx));
    }
    buildTree(hashedLeaves);
  }

  std::string getRoot() const {
    if (m_tree.empty())
      return "";
    return m_tree[0];
  }

  void printTree() const {
    if (m_tree.empty()) {
      std::println("Empty Tree");
      return;
    }

    std::println("Merkle Root: {}", getRoot());
    std::println("Tree levels (Root to Leaves):");

    ll levelSize = 1;
    ll index = 0;

    while (index < m_tree.size()) {
      for (ll i = 0; i < levelSize && index < m_tree.size(); i++) {
        std::print("[{}] ", m_tree[index++]);
      }
      std::println();
      levelSize *= 2;
    }
  }
};

int main() {
  std::vector<std::string> transactions = {
      "Tx1: Alice pays Bob 5 BTC", "Tx2: Bob pays Charlie 2 BTC",
      "Tx3: Charlie pays Dave 1 BTC", "Tx4: Dave pays Eve 0.5 BTC"};

  MerkleTree tree(transactions);

  std::println();
  tree.printTree();

  return 0;
}
