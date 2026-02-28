#include <functional>
#include <iostream>
#include <print>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using ll = long long;

ll runBelady(ll frames, const std::vector<ll> &pages) {
  std::unordered_map<ll, std::queue<ll>> futureUses;

  for (ll i = 0; i < pages.size(); i++)
    futureUses[pages[i]].push(i);

  std::unordered_set<int> memory;
  int pageFaults = 0;

  for (ll i = 0; i < pages.size(); i++) {
    ll currentPage = pages[i];

    futureUses[currentPage].pop();

    if (memory.find(currentPage) != memory.end())
      continue;

    pageFaults++;

    if (memory.size() < frames)
      memory.insert(currentPage);
    else {
      ll pageToEvict = -1, farthestUse = -1;

      for (auto m : memory) {
        if (futureUses[m].empty()) {
          pageToEvict = m;
          break;
        }

        int nextUse = futureUses[m].front();
        if (nextUse > farthestUse) {
          farthestUse = nextUse;
          pageToEvict = m;
        }
      }

			memory.erase(pageToEvict);
			memory.insert(currentPage);
    }
  }

	return pageFaults;
}

int main() {
  ll frames, N;

  std::cin >> frames >> N;

  std::vector<ll> pages(N);

  for (auto &i : pages)
    std::cin >> i;

  ll totalFaults = runBelady(frames, pages);

  std::println("Total Page Faults: {}", totalFaults);
}
