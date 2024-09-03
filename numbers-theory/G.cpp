#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

const double PI = 3.141592653589793;

void fast_fourier_transform(std::vector<std::complex<double>>& a, bool is_inverse) {
    int n = a.size();

    int k = 1;
    while (n > (1 << k)) {
        ++k;
    }

    std::vector<int> rev (n, 0);
    rev[0] = 0;
    int oldest = -1;
    for (int mask = 1; mask < (1 << k); ++mask) {
        if (!(mask & (mask - 1))) {
            ++oldest;
        }
        rev[mask] = rev[mask ^ (1 << oldest)] | (1 << (k - oldest - 1));
    }

    for (int i = 0; i < n; ++i) {
        if (i < rev[i]) {
            std::swap(a[i], a[rev[i]]);
        }
    }

    for (int i = 2; i <= n; i <<= 1) {
        std::complex<double> w;
        if (is_inverse) {
            w = std::complex<double> (cos(-2 * PI / i), sin(-2 * PI / i));
        } else {
            w = std::complex<double> (cos(2 * PI / i), sin(2 * PI / i));
        }
        for (int j = 0; j < n; j += i) {
            std::complex<double> w_pow = 1;
            for (int k = 0; k < i / 2; ++k) {
                std::complex<double> x = a[j + k];
                std::complex<double> y = a[j + k + i / 2] * w_pow;//w_pow[i][k];

                a[j + k] = x + y;
                a[j + k + i / 2] = x - y;

                w_pow *= w;
            }
        }
    }

    if (is_inverse) {
        for (int i = 0; i < n; ++i) {
            a[i] /= n;
        }
    }
}

std::vector<int> multiply(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<std::complex<double>> complex_a;
    for (int i = 0; i < a.size(); ++i) {
        complex_a.push_back(a[i]);
    }

    std::vector<std::complex<double>> complex_b;
    for (int i = 0; i < b.size(); ++i) {
        complex_b.push_back(b[i]);
    }

    int power = 1;
    while (power < complex_a.size() || power < complex_b.size()) {
        power <<= 1;
    }
    power <<= 1;

    complex_a.resize(power);
    complex_b.resize(power);

    fast_fourier_transform(complex_a, false);
    fast_fourier_transform(complex_b, false);

    for (int i = 0; i < power; ++i) {
        complex_a[i] *= complex_b[i];
    }

    fast_fourier_transform(complex_a, true);

    std::vector<int> result (power, 0);
    for (int i = 0; i < power; ++i) {
        if (complex_a[i].real() < 0) {
            result[i] = -(int)(-complex_a[i].real() + 0.5);
        } else {
            result[i] = (int)(complex_a[i].real() + 0.5);
        }
    }

    int i = result.size() - 1;
    while (result[i] == 0) {
        --i;
    }
    result.resize(i + 1);

    return result;
}

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a (n + 1, 0);
    for (int i = n; i >= 0; --i) {
        std::cin >> a[i];
    }

    int m;
    std::cin >> m;

    std::vector<int> b (m + 1, 0);
    for (int i = m; i >= 0; --i) {
        std::cin >> b[i];
    }

    std::vector<int> c = multiply(a, b);

    std::cout << c.size() - 1 << ' ';
    for (int i = c.size() - 1; i >= 0; --i) {
        std::cout << c[i] << ' ';
    }

    return 0;
}