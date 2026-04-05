#include <cmath>
#include <print>
#include <vector>

template <typename T> class BloomFilter {
    std::vector<bool> m_bitset;
    size_t m_size;
    size_t m_numOfHashes;

    std::hash<T> m_hasher1;

    size_t getHash2(size_t hash1) const {
        std::hash<size_t> intHasher;
        return intHasher(hash1);
    }

  public:
    BloomFilter(size_t expectedElements, double falsePositiveRate) {
        m_size = std::ceil(-(expectedElements * std::log(falsePositiveRate)) /
                           (std::log(2) * std::log(2)));

        m_numOfHashes = std::ceil(
            (m_size / static_cast<double>(expectedElements)) * std::log(2));

        m_bitset.resize(m_size, false);
    }

    void insert(const T &item) {
        size_t hash1 = m_hasher1(item);
        size_t hash2 = getHash2(hash1);

        for (size_t i = 0; i < m_numOfHashes; i++) {
            size_t combinedHash = (hash1 + i * hash2) % m_size;
            m_bitset[combinedHash] = true;
        }
    }

    bool contains(const T &item) const {
        size_t hash1 = m_hasher1(item);
        size_t hash2 = getHash2(hash1);

        for (size_t i = 0; i < m_numOfHashes; i++) {
            size_t combinedHash = (hash1 + i * hash2) % m_size;
            if (!m_bitset[combinedHash]) {
                return false;
            }
        }
        return true;
    }

    void printStats() const {
        std::println("Allocated bits (m): {}", m_size);
        std::println("Hash functions (k): {}", m_numOfHashes);
        std::println("Memory Usage: {} bytes\n", m_size / 8);
    }
};
