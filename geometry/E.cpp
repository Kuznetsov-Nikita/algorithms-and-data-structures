#include <iostream>
#include <cmath>
#include <vector>

struct point {
    long long int x = 0, y = 0;

    point(long long int x = 0, long long int y = 0): x(x), y(y) {}
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

    point& operator*=(long long int k) {
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

long long int dot_product(const point& first, const point& second) {
    return first.x * second.x + first.y * second.y;
}

long long int cross_product(const point& first, const point& second) {
    return first.x * second.y - first.y * second.x;
}

point get_vector_from_two_points(const point& first, const point& second) {
    return point(second.x - first.x, second.y - first.y);
}

std::istream& operator>>(std::istream& in, point& p) {
    in >> p.x >> p.y;
    return in;
}

std::ostream& operator<<(std::ostream& out, const point& p) {
    out << p.x << ' ' << p.y;
    return out;
}

bool is_inside(std::vector<point>& polygon, long long int n, const point& p) {
    bool ans = false;
    long long int cnt = 0;

    polygon.push_back(polygon[0]);
    for (long long int i = 0; i < n; ++i) {
        point a = polygon[i];
        point b = polygon[i + 1];

        if (a.y > b.y) {
            std::swap(a, b);
        }

        if (cross_product(get_vector_from_two_points(a, p), get_vector_from_two_points(b, a)) == 0 &&
           ((p.x >= a.x && p.x <= b.x) || (p.x >= b.x && p.x <= a.x)) && ((p.y >= a.y && p.y <= b.y) || (p.y >= b.y && p.y <= a.y))) {
            ans = true;
            break;
        }

        if (b.y <= p.y || a.y > p.y) {
            continue;
        }

        if (cross_product(get_vector_from_two_points(a, p), get_vector_from_two_points(b, a)) < 0) {
            ++cnt;
        }
    }

    if (!ans) {
        if (cnt % 2 == 1) {
            ans = true;
        } else {
            ans = false;
        }
    }

    return ans;
}

int main() {
    long long int n;
    scanf("%lld", &n);

    point p;
    scanf("%lld %lld", &p.x, &p.y);

    std::vector<point> polygon (n);

    for (long long int i = 0; i < n; ++i) {
        scanf("%lld %lld", &polygon[i].x, &polygon[i].y);
    }

    if (is_inside(polygon, n, p)) {
        printf("YES");
    } else {
        printf("NO");
    }

    return 0;
}
