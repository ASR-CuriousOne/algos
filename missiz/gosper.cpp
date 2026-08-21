#include <iostream>
#include <bitset>

int main(){
	int n,k;
	std::cin >> n >> k;

	int mask = (1 << k) - 1;
	int limit = (1 << n);

	
	while(mask < limit){
		std::cout << std::bitset<8>(mask) << '\n';

		int c = mask & -mask;
		int r = mask + c;

		mask = (((r ^ mask) >> 2) / c) | r;
	}

}
