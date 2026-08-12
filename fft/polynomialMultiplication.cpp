#include <cmath>
#include <complex>
#include <iostream>
#include <numbers>
#include <vector>

using cd = std::complex<double>;

void fft(std::vector<cd> &a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;

        if (i < j)
            std::swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {

        double angle = 2 * std::numbers::pi / len * (invert ? -1 : 1);
        cd wlen(std::cos(angle), std::sin(angle));

        for (int i = 0; i < n; i += len) {
            cd w(1);

            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;

                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;

                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd &c : a)
            c /= n;
    }
}

std::vector<int> multiplyPoly(const std::vector<int> &a,
                              const std::vector<int> &b) {
    std::vector<cd> fa(a.begin(), a.end());
    std::vector<cd> fb(b.begin(), b.end());

    int n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }

    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    fft(fa, true);

    std::vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = std::round(fa[i].real());
    }

    return result;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n), b(n);

    for (auto &i : a)
        std::cin >> i;

    for (auto &i : b)
        std::cin >> i;

    auto result = multiplyPoly(a, b);

    for (auto &i : result)
        std::cout << i << ' ';
    std::cout << '\n';
}
