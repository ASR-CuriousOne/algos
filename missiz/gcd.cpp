#include <iostream>
#include <print>
using ll = long long;

struct GcdResult {
  ll gcd;
  ll x;
  ll y;
};

GcdResult gcdExtended(ll a, ll b) {
  if (a == 0) {
    return {b, 0, 1};
  }

  auto [gcd, x1, y1] = gcdExtended(b % a, a);

  ll x = y1 - (b / a) * x1;
  ll y = x1;

  return {gcd, x, y};
}

int main() {
  ll a, b;
  if (std::cin >> a >> b) {
    auto [gcd, x, y] = gcdExtended(a, b);

    std::println("{}", gcd);
    std::println("{} {}", x, y);
  }
}
