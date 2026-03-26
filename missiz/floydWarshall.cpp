#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>
using ll = long long;

struct dirEdge {
    ll to, weight;
};

using AdjList = std::vector<std::vector<dirEdge>>;
using DistMatrix = std::vector<std::vector<ll>>;

void display(DistMatrix distMatrix) {
    std::ios_base::fmtflags oldFlags = std::cout.flags();
    std::streamsize oldPrec = std::cout.precision();

    std::cout << std::fixed << std::setprecision(2);

    for (size_t i = 1; i < distMatrix.size(); i++) {
        std::cout << "[";
        for (size_t j = 1; j < distMatrix[0].size(); j++) {
            float val = distMatrix[i][j];

            if (std::abs(val) < 1e-5f) {
                val = 0.00f;
            }

            std::cout << std::right << std::setw(8) << val;
        }
        std::cout << " ]\n";
    }

    std::cout.flags(oldFlags);
    std::cout.precision(oldPrec);
}

int main() {
    ll n, m;
    std::cin >> n >> m;

    AdjList adjList(n + 1);

    for (ll i = 0; i < m; i++) {
        ll u, v, w;
        std::cin >> u >> v >> w;

        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
    }

    DistMatrix distMatrix(n + 1, std::vector<ll>(n + 1, LONG_LONG_MAX));

    for (ll i = 1; i < n + 1; i++) {
        distMatrix[i][i] = 0;
        for (auto edge : adjList[i]) {
            distMatrix[i][edge.to] = edge.weight;
        }
    }

    for (ll intermediate = 1; intermediate < n + 1; intermediate++) {
        for (ll source = 1; source < n + 1; source++) {
            for (ll destination = 1; destination < n + 1; destination++) {
                if (distMatrix[source][intermediate] != LONG_LONG_MAX &&
                    distMatrix[intermediate][destination] != LONG_LONG_MAX) {
                    distMatrix[source][destination] =
                        std::min(distMatrix[source][destination],
                                 distMatrix[source][intermediate] +
                                     distMatrix[intermediate][destination]);
                }
            }
        }
    }

	display(distMatrix);
}
