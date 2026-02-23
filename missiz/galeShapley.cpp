#include <iostream>
#include <print>
#include <queue>
#include <vector>
using ll = long long;

int main() {
  ll n;
  std::cin >> n;

  std::vector<std::vector<ll>> A_prefs(n + 1, std::vector<ll>(n + 1)),
      B_prefs(n + 1, std::vector<ll>(n + 1));

  for (ll i = 1; i < n + 1; i++)
    for (ll j = 1; j < n + 1; j++)
      std::cin >> A_prefs[i][j];

  for (ll i = 1; i < n + 1; i++)
    for (ll j = 1; j < n + 1; j++)
      std::cin >> B_prefs[i][j];

  std::vector<std::vector<ll>> acceptorRanks(n + 1, std::vector<ll>(n + 1));
  for (int w = 1; w < n + 1; w++) {
    for (int i = 1; i < n + 1; i++) {
      int m = B_prefs[w][i];
      acceptorRanks[w][m] = i;
    }
  }

  std::queue<ll> proposers;
  std::vector<ll> prop_ptrs(n + 1, 1);

  std::vector<ll> matchForB(n + 1, -1);

  for (ll i = 1; i < n + 1; i++)
    proposers.push(i);

  while (!proposers.empty()) {
    ll curr = proposers.front();
    proposers.pop();

		if (prop_ptrs[curr] > n) continue;

    ll w = A_prefs[curr][prop_ptrs[curr]];
    prop_ptrs[curr]++;

    if (matchForB[w] == -1)
      matchForB[w] = curr;
    else {
      ll a = matchForB[w];

      if (acceptorRanks[w][curr] < acceptorRanks[w][a]) {
        matchForB[w] = curr;
        proposers.push(a);
      } else {
        proposers.push(curr);
      }
    }
  }

  std::println("B - A");

  for (int i = 1; i < n + 1; i++) {
    std::println("{} - {}", i, matchForB[i]);
  }
}
