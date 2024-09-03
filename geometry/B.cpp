#include <iostream>
#include <cmath>

const double EPS = 1e-10;

struct point {
    int x = 0, y = 0;

    point(int x = 0, int y = 0): x(x), y(y) {}
    point(const point& another): x(another.x), y(another.y) {}

    point operator-() const {
        return point(-x, -y);
    }

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

bool operator==(const point& first, const point& second) {
    return (first.x == second.x) && (first.y == second.y);
}

bool operator!=(const point& first, const point& second) {
    return !(first == second);
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

point get_vector_from_two_points(const point& first, const point& second) {
    return point(second.x - first.x, second.y - first.y);
}

struct line {
    int a, b, c;

    line(int a, int b, int c): a(a), b(b), c(c) {}
    line(int k, int b): a(k), b(-1), c(b) {}
    line(const line& another): a(another.a), b(another.b), c(another.c) {}

    line(const point& first_p, const point& second_p) {
        a = first_p.y - second_p.y;
        b = second_p.x - first_p.x;
        c = cross_product(first_p, second_p);
    }

    point normal_vector() const {
        return point(a, b);
    }

    point direction_vector() const {
        return point(-b, a);
    }
};

bool operator==(const line& first, const line& second) {
    if ((first.a == 0 && second.a == 0) && (first.c == 0 && second.c == 0)) {
        return true;
    }
    if ((first.b == 0 && second.b == 0) && (first.c == 0 && second.c == 0)) {
        return true;
    }
    if ((second.b != 0) && (second.c != 0) && (first.a == 0 && second.a == 0) && (fabs(first.b / second.b - first.c / second.c) < EPS)) {
        return true;
    }
    if ((second.a != 0) && (second.c != 0) && (first.b == 0 && second.b == 0) && (fabs(first.a / second.a - first.c / second.c) < EPS)) {
        return true;
    }
    if ((second.a != 0) && (second.b != 0) && (first.c == 0 && second.c == 0) && (fabs(first.a / second.a - first.b / second.b) < EPS)) {
        return true;
    }
    if ((second.a != 0) && (second.b != 0) && (fabs(first.a / second.a - first.b / second.b) < EPS) && (fabs(first.a / second.a - first.c / second.c) < EPS)) {
        return true;
    }
    return false;
}

bool operator!=(const line& first, const line& second) {
    return !(first == second);
}

std::istream& operator>>(std::istream& in, line& l) {
    in >> l.a >> l.b >> l.c;
    return in;
}

std::ostream& operator<<(std::ostream& out, const line& l) {
    out << l.a << ' ' << l.b << ' ' << l.c;
    return out;
}


bool is_parallel_or_equal(const line& first, const line& second) {
    return first.a * second.b - first.b * second.a == 0;
}

bool is_parallel(const line& first, const line& second) {
    return is_parallel_or_equal(first, second) && first != second;
}

double dist(const point& first, const point& second) {
    return sqrt((first.x - second.x) * (first.x - second.x) + (first.y - second.y) * (first.y - second.y));
}

double dist(const point& p, const line& line) {
    return fabs((line.a * p.x + line.b * p.y + line.c) / line.normal_vector().len());
}

double dist(const line& first, const line& second) {
    if (!is_parallel_or_equal(first, second) || first == second) {
        return 0;
    }

    double x, y;
    if (first.a == 0) {
        x = 0;
        y = -first.c / (double)first.b;
    } else {
        x = -first.c / (double)first.a;
        y = 0;
    }

    return fabs((second.a * x + second.b * y + second.c) / second.normal_vector().len());
}

std::pair<double, double> get_intersection(const line& first, const line& second) {
    if (is_parallel_or_equal(first, second)) {
        throw;
    }
    return std::make_pair((-first.c * second.b + second.c * first.b) / (double)(first.a * second.b - first.b * second.a),
                          (-first.a * second.c + second.a * first.c) / (double)(first.a * second.b - first.b * second.a));
}

int main() {
    line first(0, 0, 0), second(0, 0, 0);
    std::cin >> first >> second;

    std::cout.precision(6);
    std::cout << first.direction_vector() << '\n' << second.direction_vector() << '\n';

    if (is_parallel_or_equal(first, second)) {
        if (first == second) {
            std::cout << 0;
        } else {
            std::cout << dist(first, second);
        }
    } else {
        std::cout << get_intersection(first, second).first << ' ' << get_intersection(first, second).second;
    }

    return 0;
}
