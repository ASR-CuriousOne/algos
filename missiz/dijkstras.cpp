#include <climits>
#include <functional>
#include <iostream>
#include <print>
#include <queue>
#include <string>
#include <vector>

int main() {
  int n, e;

  std::cin >> n >> e;

  std::vector<std::vector<std::pair<int, int>>> adjList(n + 1);

  for (int i = 0; i < e; i++) {
    int u, v, w;

    std::cin >> u >> v >> w;

    adjList[u].push_back({v, w});
    adjList[v].push_back({u, w});
  }

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      minHeap;
  std::vector<int> distances(n + 1, INT_MAX);

  int start = 1;
  std::cin >> start;

  distances[start] = 0;

  minHeap.push({0, start});

  while (!minHeap.empty()) {
    auto [dist, curr] = minHeap.top();
    minHeap.pop();
    if (dist > distances[curr])
      continue;
    for (auto [neighbour, weight] : adjList[curr]) {
      if (distances[neighbour] > dist + weight) {
        distances[neighbour] = dist + weight;
        minHeap.push({distances[neighbour], neighbour});
      }
    }
  }

  for (int i = 1; i < n + 1; i++) {
    std::println(
        "Vertex {} at distance {} from vertex {}", i,
        (distances[i] == INT_MAX ? "inf" : std::to_string(distances[i])),
        start);
  }
}
