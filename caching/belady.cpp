#include <climits>
#include <iostream>
#include <print>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using ll = long long;

ll runBelady(ll frames, const std::vector<ll> &pages) {
  int n = pages.size();
  if (frames == 0 || n == 0)
    return 0;

  std::unordered_map<ll, std::queue<ll>> futureUses;

  std::vector<ll> nextUse(n, INT_MAX);
  std::unordered_map<ll, ll> lastSeenAt;

  for (ll i = n - 1; i >= 0; --i) {
    if (lastSeenAt.count(pages[i])) {
      nextUse[i] = lastSeenAt[pages[i]];
    }
    lastSeenAt[pages[i]] = i;
  }

  std::unordered_set<int> memory;
  int pageFaults = 0;

  std::set<std::pair<int, int>> activePages;

  for (ll i = 0; i < n; i++) {
    ll currentPage = pages[i];
    ll nextUseIdx = nextUse[i]; 

    if (memory.find(currentPage) != memory.end()){
			activePages.erase({i, currentPage});
      activePages.insert({nextUseIdx, currentPage});
      continue;
		}

    pageFaults++;

    if (memory.size() == frames){
			auto farthestIt = std::prev(activePages.end());
			ll pageToEvict = farthestIt->second;

			activePages.erase(farthestIt);
			memory.erase(pageToEvict);
		}

		memory.insert(currentPage);
		activePages.insert({nextUseIdx,currentPage});
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
