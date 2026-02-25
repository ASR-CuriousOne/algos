#include "linkedList.hpp"
#include <iostream>
using ll = long long;

int main(){
	ll n;
	std::cin >> n;

	LinkedList<ll> list;
	
	for(ll i = 0; i < n; i++){
		ll temp;
		std::cin >> temp;

		list.insert(temp);
	}

	list.printList();
}

