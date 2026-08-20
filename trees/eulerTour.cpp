#include <iostream>
#include <vector>

using AdjList = std::vector<std::vector<int>>;

void dfs(int u, int p, int &timer, std::vector<int> &inTime,
         std::vector<int> &outTime, const AdjList &adj) {
    inTime[u] = ++timer;

    for (int v : adj[u])
        if (v != p)
            dfs(v, u, timer, inTime, outTime, adj);

    outTime[u] = timer;
}

int main() {
    int n;
	std::cin >> n;

    std::vector<int> inTime(n + 1), outTime(n + 1);

    AdjList adj(n + 1);

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        std::cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

	int timer = 0;

	dfs(1, 0, timer, inTime, outTime, adj);


	for(auto i : inTime)
		std::cout << i << ' ';
	std::cout << '\n';

	for(auto i : outTime)
		std::cout << i << ' ';
	std::cout << '\n';
}
