#include <iostream>
#include <utility>
using ll = long long;

void printPermutation(const std::string &s) {
  std::cout << s << '\n';
}

template<typename T>
void heapsAlgo(ll k,T &a) {
  if (k == 1) {
    printPermutation(a);
    return;
  }

  for (ll i = 0; i < k; i++) {
    heapsAlgo<T>(k - 1, a);

    if (i < k - 1) {
      if (k % 2 == 0) {
        std::swap(a[i], a[k - 1]);
      } else {
        std::swap(a[0], a[k - 1]);
      }
    }
  }
}

int main() {
  ll n;

  std::cin >> n;
	
	std::string s;

  std::cin >> s;

	std::cout << '\n';
	heapsAlgo<std::string>(n, s);
}
