#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

using ll = long long;
using LRUList = std::list<std::pair<ll, ll>>;

class LRU {
private:
  ll m_capacity;

  LRUList m_cacheList;

  std::unordered_map<ll, LRUList::iterator> m_cacheMap;

public:
  LRU(int cap) : m_capacity(cap) {}

  ll get(ll key) {
    if (m_cacheMap.find(key) == m_cacheMap.end()) {
      return -1;
    }

    auto nodeIt = m_cacheMap[key];

    m_cacheList.splice(m_cacheList.begin(), m_cacheList, nodeIt);

    return nodeIt->second;
  }

  void put(ll key, ll value) {
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


//TestBench made by Gemini (I just make the algos :) )
int main() {
  int capacity;
  std::cout << "Enter the capacity of the LRU Cache: ";
  if (!(std::cin >> capacity) || capacity <= 0) {
    std::cerr << "Invalid capacity. Exiting.\n";
    return 1;
  }

  LRU cache(capacity);
  std::cout << "\n[Cache created with capacity " << capacity << "]\n";
  std::cout << "Available Commands:\n";
  std::cout << "  PUT <key> <value>  (e.g., PUT 1 100)\n";
  std::cout << "  GET <key>          (e.g., GET 1)\n";
  std::cout << "  EXIT\n";

  std::string command;
  while (true) {
    std::cout << "\n> ";
    std::cin >> command;

    for (char &c : command)
      c = toupper(c);

    if (command == "EXIT") {
      std::cout << "Shutting down cache test...\n";
      break;
    } else if (command == "PUT") {
      int key, value;
      if (std::cin >> key >> value) {
        cache.put(key, value);
        std::cout << " -> Inserted/Updated Key " << key << " with Value "
                  << value << "\n";
      } else {
        std::cout
            << " -> Error: Invalid input for PUT. Expected two integers.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
      }
    } else if (command == "GET") {
      int key;
      if (std::cin >> key) {
        int result = cache.get(key);
        if (result == -1) {
          std::cout << " -> Cache Miss! Key " << key
                    << " not found or was evicted.\n";
        } else {
          std::cout << " -> Cache Hit! Value: " << result << "\n";
        }
      } else {
        std::cout
            << " -> Error: Invalid input for GET. Expected one integer.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
      }
    } else {
      std::cout << " -> Unknown command. Please use PUT, GET, or EXIT.\n";
      std::cin.ignore(10000, '\n');
    }
  }

  return 0;
}
