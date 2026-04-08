#include "missiz/linkedList.hpp"
#include <iostream>
using ll = long long;

int main() {
  ll n;
  std::cin >> n;

  LinkedList<ll> list;

  for (ll i = 0; i < n; i++) {
    ll temp;
    std::cin >> temp;

    list.insertAtEnd(temp);
  }

  list.printList();

  ll temp, pos;
  std::cin >> temp >> pos;

  list.insert(temp, pos);

	list.printList();

	list.reverse();
	list.printList();
}
