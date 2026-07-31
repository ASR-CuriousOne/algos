#include <algorithm>
#include <iostream>
#include <vector>

void countingSort(std::vector<int> &a, int exp) {
    std::vector<int> count(10, 0);

    for (auto i : a) {
        i /= exp;
        count[i % 10]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    std::vector<int> output(a.size(), 0);

   for (auto rit = a.rbegin(); rit != a.rend(); ++rit) {
        int val = *rit;

        int digit = (val / exp) % 10;
        output[count[digit] - 1] = val;
        count[digit]--;
    }

    for (int i = 0; i < a.size(); i++)
        a[i] = output[i];
}

void radixSort(std::vector<int> &a) {
    int maxVal = *std::max_element(a.begin(), a.end());

    for (int exp = 1; (maxVal / exp) > 0; exp *= 10) {
        countingSort(a, exp);
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);

    for (auto &i : a)
        std::cin >> i;

	radixSort(a);

	for(auto i : a) 
		std::cout << i << ' ';

	std::cout << '\n';
}
