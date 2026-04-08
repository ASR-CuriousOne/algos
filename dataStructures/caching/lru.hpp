#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

template <typename Key, typename Value> class LRU {
  private:
    std::size_t m_capacity;

    using LRUList = std::list<std::pair<Key, Value>>;
    LRUList m_cacheList;

    std::unordered_map<Key, typename LRUList::iterator> m_cacheMap;

  public:
    LRU(std::size_t cap) : m_capacity(cap) {}

    std::optional<Value> get(Key const &key) {
        if (m_cacheMap.find(key) == m_cacheMap.end()) {
            return std::nullopt;
        }

        auto nodeIt = m_cacheMap[key];

        m_cacheList.splice(m_cacheList.begin(), m_cacheList, nodeIt);

        return nodeIt->second;
    }

    void put(Key const &key, Value const &value) {
        if (m_cacheMap.find(key) != m_cacheMap.end()) {
            auto nodeIt = m_cacheMap[key];

            nodeIt->second = value;

            m_cacheList.splice(m_cacheList.begin(), m_cacheList, nodeIt);

            return;
        }

        if (m_cacheMap.size() == m_capacity) {
            int lru_key = m_cacheList.back().first;

            m_cacheList.pop_back();
            m_cacheMap.erase(lru_key);
        }

        m_cacheList.push_front({key, value});
        m_cacheMap[key] = m_cacheList.begin();
    }
};
