#include "missiz/ds.hpp"
#include <iostream>
#include <print>
#include <vector>
using ll = long long;

struct WeightedDirEdge {
  ll node, weight;
};

struct WeightedUnDirEdge {
  ll u, v, weight;

  bool operator<(const WeightedUnDirEdge &v) { return weight < v.weight; }
};

int main() {
  ll n, e;
  std::cin >> n >> e;

  std::vector<std::vector<WeightedDirEdge>> adjList(n + 1);
  std::vector<WeightedUnDirEdge> edges(e);
  for (ll i = 0; i < e; i++) {
    ll u, v, w;

    std::cin >> u >> v >> w;

    edges[i] = {u, v, w};
  }

  std::sort(edges.begin(), edges.end());

  DS dsu(n);

  ll cost = 0;

  for (auto [u, v, w] : edges) {
    if (!dsu.connected(u, v)) {
      dsu.unite(u, v);
      adjList[u].push_back({v, w});
      adjList[v].push_back({u, w});
      cost += w;
    }
  }

  std::println("{}", cost);
  ll curr = 0;
  for (auto vert : adjList) {
		if(curr == 0) {curr++; continue;}
    std::print("{} | ", curr);
    for (auto [neighbour, weight] : vert) {
      std::print("{},{} ", neighbour, weight);
    }
    std::println();
    curr++;
  }
}
