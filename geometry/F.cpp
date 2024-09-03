#include <algorithm>
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

bool operator==(const point& first, const point& second) {
    return (first.x == second.x && first.y == second.y);
}

bool operator!=(const point& first, const point& second) {
    return !(first == second);
}

bool operator<(const point& first, const point& second) {
    return (first.x < second.x || (first.x == second.x && first.y < second.y));
}

bool operator>(const point& first, const point& second) {
    return (second < first);
}

bool operator<=(const point& first, const point& second) {
    return (first < second || first == second);
}

bool operator>=(const point& first, const point& second) {
    return (first > second || first == second);
}

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

std::vector<point> convex(std::vector<point>& set, long long int n) {
    std::sort(set.begin(), set.end());

    std::vector<point> lower_convex;
    std::vector<point> upper_convex;

    lower_convex.push_back(set[0]);
    upper_convex.push_back(set[0]);

    for (long long int i = 1; i < n; ++i) {
        if (i == n - 1 || cross_product(get_vector_from_two_points(set[0], set[i]), get_vector_from_two_points(set[i], set[n - 1])) > 0) {
            while (lower_convex.size() >= 2 &&
                   cross_product(get_vector_from_two_points(lower_convex[lower_convex.size() - 2], lower_convex[lower_convex.size() - 1]),
                                 get_vector_from_two_points(lower_convex[lower_convex.size() - 1], set[i])) <= 0) {
                lower_convex.pop_back();
            }
            lower_convex.push_back(set[i]);
        }

        if (i == n - 1 || cross_product(get_vector_from_two_points(set[0], set[i]), get_vector_from_two_points(set[i], set[n - 1])) < 0) {
            while (upper_convex.size() >= 2 &&
                   cross_product(get_vector_from_two_points(upper_convex[upper_convex.size() - 2], upper_convex[upper_convex.size() - 1]),
                                 get_vector_from_two_points(upper_convex[upper_convex.size() - 1], set[i])) >= 0) {
                upper_convex.pop_back();
            }
            upper_convex.push_back(set[i]);
        }
    }

    std::vector<point> answer;

    for (long long int i = 0; i < lower_convex.size(); ++i) {
        answer.push_back(lower_convex[i]);
    }
    for (long long int i = upper_convex.size() - 2; i > 0; --i) {
        answer.push_back(upper_convex[i]);
    }

    return answer;
}

int main() {
    long long int n;
    scanf("%lld", &n);

    std::vector<point> set (n);

    for (long long int i = 0; i < n; ++i) {
        scanf("%lld %lld", &set[i].x, &set[i].y);
    }

    std::vector<point> set_convex = convex(set, n);

    printf("%lld\n", set_convex.size());

    for (long long int i = 0; i < set_convex.size(); ++i) {
        printf("%lld %lld\n", set_convex[i].x, set_convex[i].y);
    }

    return 0;
}
