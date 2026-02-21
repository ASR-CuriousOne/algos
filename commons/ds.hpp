#pragma once
#include <vector>
using ll = long long;

class DS {
  ll n;
  std::vector<ll> m_parents;
  std::vector<ll> m_sizes;
  ll m_componentsCount;

public:
  DS(ll n) : n(n), m_parents(n + 1), m_sizes(n + 1, 1), m_componentsCount(n) {
    for (ll i = 0; i < n + 1; i++) {
      m_parents[i] = i;
    }
  }

  ll find(ll i) {
    if (m_parents[i] == i)
      return i;
    return m_parents[i] = find(m_parents[i]);
  }

  void unite(ll u, ll v) {
    ll p1 = find(u), p2 = find(v);

    if (p1 != p2) {
      if (m_sizes[p1] < m_sizes[p2]) {
        std::swap(p1, p2);
      }

      m_parents[p2] = p1;
      m_sizes[p1] += m_sizes[p2];
      m_componentsCount--;
    }
  }

  bool connected(ll u, ll v) { return find(u) == find(v); }

  ll getSize(ll i) { return m_sizes[find(i)]; }

  ll getComponentsCount() { return m_componentsCount; }
};
