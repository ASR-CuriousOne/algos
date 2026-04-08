#include <climits>
#include <iostream>
#include <vector>
using ll = long long;

struct Edge {
    ll from, to, weight;
};

int main() {
    ll V, E;

    std::cin >> V >> E;

    std::vector<Edge> edges(E);

    for (ll i = 0; i < E; i++) {
        ll u, v, w;

        std::cin >> u >> v >> w;

        edges[i] = {.from = u, .to = v, .weight = w};
    }

    std::vector<ll> distances(V + 1, LONG_LONG_MAX);
    distances[1] = 0;

    for (ll i = 0; i < V; i++) {
        for (auto edge : edges) {
            if (distances[edge.from] != LONG_LONG_MAX &&
                distances[edge.from] + edge.weight < distances[edge.to]) {

                if (i == V - 1) {
                    std::cout << -1 << '\n';
                    return 0;
                }

                distances[edge.to] = edge.weight + distances[edge.from];
            }
        }
    }

    std::cout << distances[V] << '\n';
}
