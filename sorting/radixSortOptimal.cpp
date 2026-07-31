#include <iostream>
#include <vector>

void radixSort(std::vector<int> &a) {
    const int chunks = 8;
    const int base = (1 << chunks);
    const int mask = base - 1;
    const int intSize = sizeof(int) * 8;

    int n = a.size();
    std::vector<int> buffer(n);

    std::vector<int> *in = &a;
    std::vector<int> *out = &buffer;

    for (int shift = 0; shift < intSize; shift += chunks) {
        int count[base] = {0};

        int signFlip = (shift == intSize - chunks) ? 128 : 0;

        for (int val : *in) {
            int digit = ((val >> shift) & mask) ^ signFlip;
            count[digit]++;
        }

        int sum = 0;
        for (int i = 0; i < base; i++) {
            int curr = count[i];
            count[i] = sum;
            sum += curr;
        }

        for (int val : *in) {
            int digit = ((val >> shift) & mask) ^ signFlip;
            (*out)[count[digit]++] = val;
        }

        std::swap(in, out);
    }

    if (in == &buffer) {
        a = buffer;
    }
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);

    for (auto &i : a)
        std::cin >> i;

    radixSort(a);

    for (auto i : a)
        std::cout << i << ' ';

    std::cout << '\n';
}
