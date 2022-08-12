#include <bits/stdc++.h>

using u64 = uint64_t;

u64 mul(u64 a, u64 b, u64 m) {
    int64_t ret = a * b - m * u64(1.L / m * a * b);
    return ret + m * (ret < 0) - m * (ret >= int64_t(m));
}

u64 pow(u64 a, u64 p, u64 m) {
    u64 ret = 1;
    for (; p; p >>= 1) {
        if (p & 1) ret = mul(ret, a, m);
        a = mul(a, a, m);
    }
    return ret;
}

namespace A {
    bool is_prime(u64 n) {
        auto time = clock();
        for (u64 i = 2; i < n; i++) {
            if (n % i == 0) {
                std::cout << (clock() - time) << " : ";
                return false;
            }
        }
        std::cout << (clock() - time) << " : ";
        return true;
    }
}

namespace B {
    bool is_prime(u64 n) {
        auto time = clock();
        for (u64 i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                std::cout << (clock() - time) << " : ";
                return false;
            }
        }
        std::cout << (clock() - time) << " : ";
        return true;
    }
}

class Fermats {
public:
    bool is_prime(u64 n, int k = 5) {
        auto time = clock();
        if (n < 4) {
            std::cout << (clock() - time) << " : ";
            return n == 2 || n == 3;
        }
        for (int i = 0; i < k; i++) {
            u64 a = 2 + rand() % (n - 3);
            if (pow(a, n - 1, n) != 1 && std::gcd(a, n) == 1) {
                std::cout << (clock() - time) << " : ";
                return false;
            }
        }
        std::cout << (clock() - time) << " : ";
        return true;
    }
} C;

class MillerRabin {
public:
    bool is_prime(u64 n) {
        auto time = clock();
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;

        const auto &base = n < 4759123141ULL ? base_small : base_large;
        const int s = __builtin_ctzll(n - 1);
        const u64 d = n >> s;

        for (const auto &b: base) {
            if (b >= n) break;
            if (check_composite(n, b, d, s)) {
                std::cout << (clock() - time) << " : ";
                return false;
            }
        }
        std::cout << (clock() - time) << " : ";
        return true;
    }

private:
    const std::vector<u64> base_small = {2, 7, 61}, base_large = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    static bool check_composite(u64 n, u64 x, u64 d, int s) {
        x = pow(x, d, n);
        if (x == 1 || x == n - 1) return false;
        while (--s) {
            x = mul(x, x, n);
            if (x == n - 1) return false;
        }
        return true;
    };
} D;

int main() {
    // 543876131 * 870248209
    // u64 n = 473307228920599379LL;

    // 소수
    // u64 n = (1LL << 31) - 1;

    // 카마이클 수 - 소수 판별 방법 C 는 실패
    u64 n = 561;

    std::cout << A::is_prime(n) << "\n"
              << B::is_prime(n) << "\n"
              << C.is_prime(n) << "\n"
              << D.is_prime(n) << "\n";
}
