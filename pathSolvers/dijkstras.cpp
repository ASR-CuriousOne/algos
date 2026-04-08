#include <climits>
#include <functional>
#include <iostream>
#include <print>
#include <queue>
#include <string>
#include <vector>

struct Edge {
  int to;
  int weight;
};

struct QueueNode {
  int dist;
  int node;

  bool operator>(const QueueNode &other) const { return dist > other.dist; }
};

constexpr int INF = std::numeric_limits<int>::max();

int main() {
  int n, e;

  std::cin >> n >> e;

  std::vector<std::vector<Edge>> adjList(n + 1);

  for (int i = 0; i < e; i++) {
    int u, v, w;

    std::cin >> u >> v >> w;

    adjList[u].push_back({v, w});
    adjList[v].push_back({u, w});
  }

  std::priority_queue<QueueNode, std::vector<QueueNode>, std::greater<>>
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

    for (const auto &edge : adjList[curr]) {
      if (distances[edge.to] > dist + edge.weight) {
        distances[edge.to] = dist + edge.weight;
        minHeap.push({distances[edge.to], edge.to});
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    if (distances[i] == INF) {
      std::println("Vertex {} at distance inf from vertex {}", i, start);
    } else {
      std::println("Vertex {} at distance {} from vertex {}", i, distances[i],
                   start);
    }
  }
}
