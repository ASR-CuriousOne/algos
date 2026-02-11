#include <iostream>
using ll = long long;

ll gcdExtended(ll a, ll b, ll& x, ll& y) {
  if (a == 0){
    x = 0; y = 1;
    return b;
  }
  ll x1,y1;

  ll gcd = gcdExtended(b % a, a,x1,y1);

  x = y1 - (b/a)*x1;
  y = x1;
  return gcd;
}

int main() {
  ll a, b,x,y;
  std::cin >> a >> b;
  std::cout << gcdExtended(a, b,x,y) << '\n';
  std::cout << x << ' ' << y << '\n';
}
