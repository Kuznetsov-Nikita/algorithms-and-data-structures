#include <iostream>
#include <cmath>
#include <string>
#include <vector>

class BigInteger {
private:
    int length = 0;
    int sign = 1;
    std::vector<char> number;

    friend std::istream& operator>>(std::istream&, BigInteger&);
    friend bool operator==(const BigInteger&, const BigInteger&);
    friend bool operator!=(const BigInteger&, const BigInteger&);
    friend bool operator<(const BigInteger&, const BigInteger&);
    friend bool operator>(const BigInteger&, const BigInteger&);
    friend bool operator<=(const BigInteger&, const BigInteger&);
    friend bool operator>=(const BigInteger&, const BigInteger&);
public:
    //Конструктор по умолчанию
    BigInteger() = default;

    //Конструктор от int
    BigInteger(int src_number) {
        sign = (src_number < 0) ? -1 : 1;
        src_number = abs(src_number);

        do {
            number.push_back(src_number % 10);
            src_number /= 10;
            ++length;
        } while (src_number != 0);
    }

    BigInteger(size_t src_number) {
        sign = 1;

        do {
            number.push_back(src_number % 10);
            src_number /= 10;
            ++length;
        } while (src_number != 0);
    }

    //Копирующий конструктор
    BigInteger(const BigInteger& src_big_int): length(src_big_int.length), sign(src_big_int.sign), number(src_big_int.number) {}

    //Оператор присваивания
    BigInteger& operator=(const BigInteger& src_big_int) {
        BigInteger copy = src_big_int;
        swap(copy);
        return *this;
    }

    void swap(BigInteger& big_int) {
        std::swap(length, big_int.length);
        std::swap(sign, big_int.sign);
        std::swap(number, big_int.number);
    }

    //Неявное преобразование в bool
    explicit operator bool() {
        return *this != 0;
    }

    //Метод toString
    std::string toString() const {
        std::string str_big_int = "";

        if (sign == -1) {
            str_big_int += '-';
        }

        for (int i = length - 1; i >= 0; --i) {
            str_big_int += number[i] + '0';
        }

        return str_big_int;
    }

    //Составное присваивание +=
    BigInteger& operator+=(const BigInteger& big_int) {
        if (big_int != 0 && *this != 0) {
            if (sign == big_int.sign) {
                char carry = 0;

                for (int i = 0; i < std::max(length, big_int.length) || carry != 0; ++i) {
                    char new_digit = carry;
                    if (i < length) {
                        new_digit += number[i];
                    }
                    if (i < big_int.length) {
                        new_digit += big_int.number[i];
                    }

                    if (i >= length) {
                        number.push_back(0);
                        ++length;
                    }

                    number[i] = new_digit % 10;
                    carry = new_digit / 10;
                }
            } else {
                *this -= -big_int;
            }
        } else {
            if (*this == 0) {
                *this = big_int;
            }
        }

        return *this;
    }

    //Составное присваивание -=
    BigInteger& operator-=(const BigInteger& big_int) {
        if (big_int != 0 && *this != 0) {
            if (big_int == *this) {
                *this = 0;
                return *this;
            }

            if (sign == big_int.sign) {
                if((sign >= 0 && *this < big_int) || (sign < 0 && *this > big_int)) {
                    BigInteger tmp = big_int;
                    tmp -= *this;
                    *this = tmp;
                    sign = -sign;

                    return *this;
                }

                char carry = 0;
                int i;

                for (i = 0; i < std::max(length, big_int.length); ++i) {
                    char new_digit = carry;

                    if (i < length) {
                        new_digit += number[i];
                    }
                    if (i < big_int.length) {
                        new_digit -= big_int.number[i];
                    }
                    if (new_digit < 0) {
                        new_digit += 10;
                        carry = -1;
                    } else {
                        carry = 0;
                    }

                    if (length <= i) {
                        number.push_back(0);
                        ++length;
                    }
                    number[i] = new_digit;
                }

                if (carry != 0) {
                    if (i != 0) {
                        number[0] = 10 - number[0];
                    }

                    length = (i != 0) ? 1 : 0;

                    for (int j = 1; j < i; ++j) {
                        number[j] = 9 - number[j];

                        if (number[i] != 0) {
                            length = j + 1;
                        }
                    }

                    sign *= -1;
                }

                while (length > 1 && number[length - 1] == 0) {
                    --length;
                    number.pop_back();
                }
            } else {
                *this += -big_int;
            }
        } else {
            if (*this == 0) {
                *this = -big_int;
            }
        }

        return *this;
    }

    //Составное присваивание *=
    BigInteger& operator*=(const BigInteger& big_int) {
        if (*this == 0 || big_int == 0) {
            *this = 0;
        } else {
            std::vector<char> tmp(length + big_int.length);

            sign *= big_int.sign;

            int i, j = 0;

            for (i = 0; i < big_int.length; ++i) {
                if (big_int.number[i] != 0) {
                    char carry = 0;

                    for (j = 0; j < length || carry != 0; ++j) {
                        char new_digit = tmp[i + j] + ((j < length) ? big_int.number[i] * number[j] : 0) + carry;

                        tmp[i + j] = new_digit % 10;
                        carry = new_digit / 10;
                    }
                }
            }

            length = i + j - 1;
            number = tmp;
        }

        return *this;
    }

    //Составное присваивание /=
    BigInteger& operator/=(const BigInteger& big_int) {
        if (*this != 0) {
            sign *= big_int.sign;

            BigInteger tmp = 0;
            BigInteger n = ((big_int.sign > 0) ? big_int : -big_int);

            for (int i = length - 1; i >= 0; --i) {
                tmp *= 10;
                tmp += number[i];
                number[i] = 0;

                while (tmp >= n) {
                    tmp -= n;
                    ++number[i];
                }
            }

            while (length > 1 && number[length - 1] == 0) {
                --length;
                number.pop_back();
            }
        }

        if (length == 1 && number[0] == 0) {
            sign = 1;
        }

        return *this;
    }

    //Составное присваивание %=
    BigInteger& operator%=(const BigInteger& big_int) {
        if (*this != 0) {
            int s1 = sign, s2 = big_int.sign;

            sign *= big_int.sign;

            BigInteger tmp = 0;
            BigInteger n = ((big_int.sign > 0) ? big_int : -big_int);

            for (int i = length - 1; i >= 0; --i) {
                tmp *= 10;
                tmp += number[i];
                number[i] = 0;

                while (tmp >= n) {
                    tmp -= n;
                    ++number[i];
                }
            }

            while (length > 1 && number[length - 1] == 0) {
                --length;
                number.pop_back();
            }

            *this = tmp;

            if ((s1 == -1 && s2 == -1) || (s1 == -1 && s2 == 1)) {
                sign = -1;
            }

            if (length == 1 && number[0] == 0) {
                sign = 1;
            }
        }

        return *this;
    }

    //Унарный минус
    BigInteger operator-() const {
        if (*this != 0) {
            BigInteger copy = *this;
            copy.sign = (sign == 1) ? -1 : 1;
            return copy;
        }
        return *this;
    }

    //Префиксные инкремент и декремент
    BigInteger& operator++() {
        *this += 1;
        return *this;
    }

    BigInteger& operator--() {
        *this -= 1;
        return *this;
    }

    //Постфиксные инкремент и декремент
    BigInteger operator++(int) {
        BigInteger copy = *this;
        ++*this;
        return copy;
    }

    BigInteger operator--(int) {
        BigInteger copy = *this;
        --*this;
        return copy;
    }

    void clear() {
        number = {};
        length = 0;
        sign = 1;
    }
};

//Сложение
BigInteger operator+(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    BigInteger copy = big_int_1;
    copy += big_int_2;
    return copy;
}

//Вычитание
BigInteger operator-(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    BigInteger copy = big_int_1;
    copy -= big_int_2;
    return copy;
}

//Умножение
BigInteger operator*(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    BigInteger copy = big_int_1;
    copy *= big_int_2;
    return copy;
}

//Деление
BigInteger operator/(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    BigInteger copy = big_int_1;
    copy /= big_int_2;
    return copy;
}

//Остаток по модулю
BigInteger operator%(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    BigInteger copy = big_int_1;
    copy %= big_int_2;
    return copy;
}

//Оператор сравнения ==
bool operator==(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    if (big_int_1.sign != big_int_2.sign || big_int_1.length != big_int_2.length) {
        return false;
    } else {
        bool flag = true;

        for (int i = 0; i < big_int_1.length; ++i) {
            if (big_int_1.number[i] != big_int_2.number[i]) {
                flag = false;
                break;
            }
        }

        return flag;
    }
}

//Оператор сравнения !=
bool operator!=(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    return !(big_int_1 == big_int_2);
}

//Оператор сравнения <
bool operator<(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    if (big_int_1.sign < big_int_2.sign) {
        return true;
    } else if (big_int_1.sign > big_int_2.sign) {
        return false;
    } else {
        if (big_int_1.length < big_int_2.length) {
            if (big_int_1.sign > 0) {
                return true;
            } else {
                return false;
            }
        } else if (big_int_1.length > big_int_2.length) {
            if (big_int_1.sign > 0) {
                return false;
            } else {
                return true;
            }
        } else {
            if (big_int_1.sign > 0) {
                bool flag = false;

                for (int i = big_int_1.length - 1; i >= 0; --i) {
                    if (big_int_1.number[i] < big_int_2.number[i]) {
                        flag = true;
                        break;
                    } else if (big_int_1.number[i] > big_int_2.number[i]) {
                        break;
                    }
                }

                return flag;
            } else {
                bool flag = false;

                for (int i = big_int_1.length - 1; i >= 0; --i) {
                    if (big_int_1.number[i] > big_int_2.number[i]) {
                        flag = true;
                        break;
                    } else if (big_int_1.number[i] < big_int_2.number[i]) {
                        break;
                    }
                }

                return flag;
            }
        }
    }
}

//Оператор сравнения >
bool operator>(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    return big_int_2 < big_int_1;
}

//Оператор сравнения <=
bool operator<=(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    return (big_int_1 == big_int_2) || (big_int_1 < big_int_2);
}

//Оператор сравнения >=
bool operator>=(const BigInteger& big_int_1, const BigInteger& big_int_2) {
    return big_int_2 <= big_int_1;
}

//Ввод из потока
std::istream& operator>>(std::istream& in, BigInteger& big_int) {
    big_int.clear();

    std::string in_big_int;
    in >> in_big_int;

    if (!in_big_int.empty()) {
        int first_no_null, size = in_big_int.size();

        if (!isdigit(in_big_int[0])) {
            big_int.sign = (in_big_int[0] == '+') ? 1 : -1;
            first_no_null = 1;
        } else {
            first_no_null = 0;
        }

        while (first_no_null < size && in_big_int[first_no_null] == '0') {
            ++first_no_null;
        }

        if (first_no_null == size) {
            big_int.number.push_back(0);
            ++big_int.length;
        } else {
            for (int i = size - 1; i >= first_no_null; --i) {
                big_int.number.push_back(in_big_int[i] - '0');
                ++big_int.length;
            }
        }
    }

    if (big_int.length == 1 && big_int.number[0] == 0) {
        big_int.sign = 1;
    }

    return in;
}

//Вывод в поток
std::ostream& operator<<(std::ostream& out, const BigInteger& big_int) {
    out << big_int.toString();
    return out;
}

bool correct(int mask1, int mask2, int m) {
    for (int i = 0; i < m - 1; ++i) {
        if (bool((1 << i) & mask1) == bool((1 << i) & mask2) && bool((1 << i) & mask1) == bool((1 << (i + 1)) & mask1) && bool((1 << i) & mask1) == bool((1 << (i + 1)) & mask2)) {
            return false;
        }
    }

    return true;
}

std::vector<std::vector<int>> calculate(std::vector<std::vector<int>> a, BigInteger n, int m, int mod) {
    std::vector<std::vector<int>> res ((1 << m), std::vector<int> ((1 << m), 0));
    for (int i = 0; i < (1 << m); ++i) {
        res[i][i] = 1;
    }

    std::vector<std::vector<int>> p = a;

    while (n > 0) {
        if (n % 2 == 1) {
            for (int i = 0; i < (1 << m); ++i) {
                std::vector<int> new_row;
                for (int j = 0; j < (1 << m); ++j) {
                    int value = 0;
                    for (int k = 0; k < (1 << m); ++k) {
                        value = (value + res[i][k] * p[k][j]) % mod;
                    }
                    new_row.push_back(value);
                }
                res[i] = new_row;
            }
        }

        std::vector<std::vector<int>> p_old = p;
        for (int i = 0; i < (1 << m); ++i) {
            std::vector<int> new_row;
            for (int j = 0; j < (1 << m); ++j) {
                int value = 0;
                for (int k = 0; k < (1 << m); ++k) {
                    value = (value + p[i][k] * p_old[k][j]) % mod;
                }
                new_row.push_back(value);
            }
            p[i] = new_row;
        }

        n /= 2;
    }

    return res;
}

int main() {
    BigInteger n;
    int m, mod;

    std::cin >> n >> m >> mod;

    std::vector<int> dp0 ((1 << m), 1);
    std::vector<std::vector<int>> matrix ((1 << m), std::vector<int> ((1 << m), 0));

    for (int mask0 = 0; mask0 < (1 << m); ++mask0) {
        for (int mask1 = 0; mask1 < (1 << m); ++mask1) {
            if (correct(mask0, mask1, m)) {
                matrix[mask0][mask1] = 1;
            }
        }
    }

    std::vector<std::vector<int>> matrix_pow = calculate(matrix, n - 1, m, mod);
    int ans = 0;

    for (int i = 0; i < (1 << m); ++i) {
        int p = 0;
        for (int j = 0; j < (1 << m); ++j) {
            p = (p + matrix_pow[i][j] * dp0[j]) % mod;
        }
        ans = (ans + p) % mod;
    }

    std::cout << ans;

    return 0;
}
