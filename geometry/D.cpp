#include <iostream>
#include <cmath>

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

int main() {
    int n;
    std::cin >> n;

    point point_1, point_2;
    std::cin >> point_1 >> point_2;

    point tmp_point_1 = point_1, tmp_point_2 = point_2;

    int sign[2] = {0, 0};

    for (int i = 2; i < n; ++i) {
        point point_3;
        std::cin >> point_3;

        if (cross_product(get_vector_from_two_points(point_1, point_2), get_vector_from_two_points(point_2, point_3)) > 0) {
            ++sign[0];
        }
        if (cross_product(get_vector_from_two_points(point_1, point_2), get_vector_from_two_points(point_2, point_3)) < 0) {
            ++sign[1];
        }

        point_1 = point_2;
        point_2 = point_3;
    }

    if (cross_product(get_vector_from_two_points(point_1, point_2), get_vector_from_two_points(point_2, tmp_point_1)) > 0) {
        ++sign[0];
    }
    if (cross_product(get_vector_from_two_points(point_1, point_2), get_vector_from_two_points(point_2, tmp_point_1)) < 0) {
        ++sign[1];
    }

    if (cross_product(get_vector_from_two_points(point_2, tmp_point_1), get_vector_from_two_points(tmp_point_1, tmp_point_2)) > 0) {
        ++sign[0];
    }
    if (cross_product(get_vector_from_two_points(point_2, tmp_point_1), get_vector_from_two_points(tmp_point_1, tmp_point_2)) < 0) {
        ++sign[1];
    }


    if (sign[0] == 0 || sign[1] == 0) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }

    return 0;
}
