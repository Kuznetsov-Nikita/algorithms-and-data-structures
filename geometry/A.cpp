#include <iostream>
#include <cmath>

struct point {
    int x = 0, y = 0;

    point(int x = 0, int y = 0): x(x), y(y) {}
    point(const point& another): x(another.x), y(another.y) {}

    point& operator+=(const point& another) {
        x += another.x;
        y += another.y;
        return *this;
    }

    point& operator-=(const point& another) {
        x -= another.x;
        y -= another.y;
        return *this;
    }

    point& operator*=(int k) {
        x *= k;
        y *= k;
        return *this;
    }

    double len() const {
        return sqrt(x * x + y * y);
    }
};

point operator+(const point& first, const point& second) {
    point copy = first;
    copy += second;
    return copy;
}

point operator-(const point& first, const point& second) {
    point copy = first;
    copy -= second;
    return copy;
}

point operator*(const point& p, int k) {
    point copy = p;
    copy *= k;
    return copy;
}

int dot_product(const point& first, const point& second) {
    return first.x * second.x + first.y * second.y;
}

int cross_product(const point& first, const point& second) {
    return first.x * second.y - first.y * second.x;
}

std::istream& operator>>(std::istream& in, point& p) {
    int x1, x2, y1, y2;
    in >> x1 >> y1 >> x2 >> y2;

    p.x = x2 - x1;
    p.y = y2 - y1;

    return in;
}

std::ostream& operator<<(std::ostream& out, const point& p) {
    out << p.x << ' ' << p.y;
    return out;
}

int main() {
    point first, second;
    std::cin >> first >> second;

    std::cout.precision(10);
    std::cout << first.len() << ' ' << second.len() << '\n';
    std::cout << first + second << '\n';
    std::cout << dot_product(first, second) << ' ' << cross_product(first, second) << '\n';
    std::cout << abs(cross_product(first, second)) / 2.0;

    return 0;
}