#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

const ll MOD = 998244353;
const ll G = 3;

ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;

    while (exp > 0) {
        if (exp % 2 == 1)
            res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }

    return res;
}

ll modInverse(ll a) { return power(a, MOD - 2); }

void ntt(std::vector<ll> &a, bool invert) {
    ll n = a.size();
    for (ll i = 1, j = 0; i < n; i++) {
        ll bit = n >> 1;
        for (; j & bit; bit >>= 1) {
            j ^= bit;
        }
        j ^= bit;

        if (i < j)
            std::swap(a[i], a[j]);
    }

    for (ll len = 2; len <= n; len <<= 1) {

        ll wlen = power(G, (MOD - 1) / len);

        if (invert)
            wlen = modInverse(wlen);

        for (ll i = 0; i < n; i += len) {
            ll w = 1;

            for (ll j = 0; j < len / 2; j++) {
                ll u = a[i + j];
                ll v = (a[i + j + len / 2] * w) % MOD;

                a[i + j] = (u + v < MOD ? u + v : u + v - MOD);
                a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + MOD);

                w = (w * wlen) % MOD;
            }
        }
    }

    if (invert) {
        ll nInv = modInverse(n);
        for (auto &i : a)
            i = (i * nInv) % MOD;
    }
}

std::vector<ll> multiplyPoly(const std::vector<ll> &a,
                             const std::vector<ll> &b) {
    std::vector<ll> fa(a.begin(), a.end());
    std::vector<ll> fb(b.begin(), b.end());

    ll n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }

    fa.resize(n);
    fb.resize(n);

    ntt(fa, false);
    ntt(fb, false);

    for (ll i = 0; i < n; i++) {
        fa[i] = (fa[i] * fb[i]) % MOD;
    }

    ntt(fa, true);

    std::vector<ll> result(n);
    for (ll i = 0; i < n; i++) {
        result[i] = fa[i];
    }

    return result;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<ll> a(n), b(n);

    for (auto &i : a)
        std::cin >> i;

    for (auto &i : b)
        std::cin >> i;

	std::reverse(a.begin(),a.end());
	std::reverse(b.begin(),b.end());

    auto result = multiplyPoly(a, b);

    for (auto &i : result)
        std::cout << i << ' ';
    std::cout << '\n';
}
