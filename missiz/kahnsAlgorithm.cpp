#include <iostream>
#include <queue>
#include <vector>

using ll = long long;

using AdjList = std::vector<std::vector<ll>>;

int main() {
    ll n, m;
    std::cin >> n >> m;

    AdjList adj(n + 1);
    std::vector<ll> inDegree(n + 1, 0);

    for (ll i = 0; i < m; i++) {
        ll u, v;

        std::cin >> u >> v;

        adj[u].push_back(v);
        inDegree[v]++;
    }

    std::queue<ll> q;
    std::vector<ll> order;

    for (ll i = 1; i <= n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
            order.push_back(i);
        }
    }

    while (!q.empty()) {
        ll u = q.front();
        q.pop();

        for (auto v : adj[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                q.push(v);
                order.push_back(v);
            }
        }
    }

    if (order.size() != n) {
        std::cout << -1 << '\n';
        return 0;
    }

    for (auto &i : order) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}
