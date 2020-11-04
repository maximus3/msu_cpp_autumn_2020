#include "bigint.h"

size_t
getSizeByLength(size_t length=0) {
    size_t size = 16;
    if (length < 16) {
        return size;
    }
    size = 1;
    while (length > 0) {
        size <<= 1;
        length >>= 1;
    }
    return size;
}

BigInt::BigInt(int value) {
    size = getSizeByLength();
    data = new char[size];
    for (size_t i = 0; i < size; i++) {
        data[i] = '0';
    }
    if (value < 0) {
        sign = -sign;
        value = -value;
    }
    while (value > 0) {
        data[length++] = '0' + value % 10;
        value /= 10;
    }
}

BigInt::BigInt(const std::string& value) {
    size_t k = 1;
    length = value.length();
    if (length > 0 && (value[0] < '0' || value[0] > '9')) { 
        if (value[0] == '-') {
            sign = -sign;
        }
        length--;
        k--;
    }

    size_t j = 1 - k;
    while (j != value.length() && value[j] == '0') {
        j++;
        k--;
        length--;
    }

    size = getSizeByLength(length);
    data = new char[size];
    for (size_t i = 0; i < size; i++) {
        data[i] = '0';
    }
    for(size_t i = 0; i < length; i++) {
        data[i] = value[length - i - k];
    }

    if (getEq(BigInt(), true) == 0) {
        sign = 1;
    }
}

BigInt::BigInt(const BigInt& bi) {
    length = bi.length;
    size = bi.size;
    sign = bi.sign;
    data = new char[size];
    std::copy(bi.data, bi.data + size, data);
}

BigInt::BigInt(BigInt&& moved) {
    size = std::move(moved.size);
    sign = std::move(moved.sign);
    length = std::move(moved.length);
    data = moved.data;
    moved.data = nullptr;
    moved.size = 0;
    moved.length = 0;
    moved.sign = 1;
}

BigInt&
BigInt::operator=(int value) {
    char* tmp = new char[getSizeByLength()];
    this->~BigInt();
    data = tmp;
    length = 0;
    size = getSizeByLength();
    for (size_t i = 0; i < size; i++) {
        data[i] = '0';
    }
    if (value < 0) {
        sign = -sign;
        value = -value;
    }
    while (value > 0) {
        data[length++] = '0' + value % 10;
        value /= 10;
    }
    return *this;
}

BigInt&
BigInt::operator=(const BigInt& bi) {
    if (this == &bi) {
        return *this;
    }
    char* tmp = new char[bi.size];
    this->~BigInt();
    size = bi.size;
    sign = bi.sign;
    length = bi.length;
    data = tmp;
    std::copy(bi.data, bi.data + size, data);
    return *this;
}

BigInt&
BigInt::operator=(BigInt&& moved) {
    if (this == &moved) {
        return *this;
    }
    this->~BigInt();
    size = std::move(moved.size);
    sign = std::move(moved.sign);
    length = std::move(moved.length);
    data = moved.data;
    moved.data = nullptr;
    moved.size = 0;
    moved.length = 0;
    return *this;
}

const char&
BigInt::operator[] (size_t i) const {
    return data[i];
}

BigInt
operator+(const BigInt &bi1, const BigInt &bi2) {
    char sign1 = bi1.sign;
    char sign2 = bi2.sign;
    bool is_negative;

    if (sign1 * sign2 < 0) {
        int eq = bi1.getEq(bi2, true);
        if (eq < 0) {
            is_negative = bi1.sign > 0 ? true : false;
            sign1 = -1;
            sign2 = -sign1;
        } else if (eq > 0) {
            is_negative = bi1.sign > 0 ? false : true;
            sign1 = 1;
            sign2 = -sign1;
        } else {
            return BigInt("0");
        }
    } else {
        is_negative = bi1.sign > 0 ? false : true;
        sign1 = 1;
        sign2 = 1;
    }

    std::string num_ans;
    size_t max_length = std::max(bi1.length, bi2.length);
    char prev = 0;
    for (size_t i = 0; i < max_length; i++) {
        int c1 = i >= bi1.length ? 0 : (bi1[i] - '0') * sign1;
        int c2 = i >= bi2.length ? 0 : (bi2[i] - '0') * sign2;
        int c = c1 + c2 + prev;
        if (c > 9) {
            c %= 10;
            prev = 1;
        } else if (c < 0) {
            c += 10;
            prev = -1;
        } else {
            prev = 0;
        }
        char to_add = '0' + c;
        num_ans = to_add + num_ans;
    }
    if (prev == 1) {
        num_ans = "1" + num_ans;
    }
    if (is_negative) {
        num_ans = "-" + num_ans;
    }

    BigInt ans = BigInt(num_ans);

    if (ans.getEq(BigInt(), true) == 0) {
        ans.sign = 1;
    }

    return ans;
}

BigInt
operator-(const BigInt &bi1, const BigInt &bi2) {
    return bi1 + (-bi2);
}

BigInt
operator*(const BigInt &bi1, const BigInt &bi2) {
    BigInt ans;
    for (size_t i = 0; i < bi1.length; i++) {

         int c1 = bi1[i] - '0';

        std::string num_ans_add;
        int prev = 0;
        for (size_t j = 0; j < bi2.length; j++) {
            int c2 = bi2[j] - '0';
            int c = c1 * c2 + prev;
            if (c > 9) {
                prev = c / 10;
                c %= 10;
            } else {
                prev = 0;
            }
            char to_add = '0' + c;
            num_ans_add = to_add + num_ans_add;
        }
        if (prev > 0) {
            char to_add = '0' + prev;
            num_ans_add = to_add + num_ans_add;
        }
        
        for (size_t j = 0; j < i; j++) {
            num_ans_add = num_ans_add + "0";
        }

        ans = ans + BigInt(num_ans_add);
    }
    if (bi1.sign * bi2.sign < 0) {
        ans = -ans;
    }

    if (ans.getEq(BigInt(), true) == 0) {
        ans.sign = 1;
    }

    return ans;
}

BigInt
BigInt::operator-() const {
    BigInt bi(*this);
    if (bi != 0) {
        bi.sign = -bi.sign;
    }
    return bi;
}

int
BigInt::getEq(const BigInt& bi, bool abs) const {
    if (!abs && sign * bi.sign < 0) {
        return sign;
    }
    int lo = abs ? -1 : -1 * sign;
    int eq = 0;
    int gt = abs ? 1 : 1 * sign;
    if (size != bi.size) {
        return size < bi.size ? lo : gt;
    }
    for (size_t i = 0; i < size; i++) {
        char cur_c = data[size - i - 1];
        char bi_c = bi[size - i - 1];
        if (cur_c != bi_c) {
            return cur_c < bi_c ? lo : gt;
        }
    }
    return eq;
}

bool
BigInt::operator<(const BigInt &bi) const {
    return getEq(bi) < 0 ? true : false;
}

bool
BigInt::operator<=(const BigInt &bi) const {
    return getEq(bi) <= 0 ? true : false;
}

bool
BigInt::operator>(const BigInt &bi) const {
    return getEq(bi) > 0 ? true : false;
}

bool
BigInt::operator>=(const BigInt &bi) const {
    return getEq(bi) >= 0 ? true : false;
}

bool
BigInt::operator==(const BigInt &bi) const {
    return getEq(bi) == 0 ? true : false;
}

bool
BigInt::operator!=(const BigInt &bi) const {
    return getEq(bi) != 0 ? true : false;
}

BigInt::~BigInt() {
    delete[] data;
}

std::ostream&
operator<< (std::ostream& out, const BigInt& bi) {
    if (bi.sign < 0) {
        std::cout << "-";
    }
    size_t k = bi.size;
    while (k > 1 && bi[k - 1] == '0') {
        k--;
    }
    for (size_t i = k - 1; i > 0; i--) {
        out << bi[i];
    }
    out << bi[0];
    return out;
}

std::istream&
operator>> (std::istream& input, BigInt& bi) {
    std::string num;
    input >> num;
    bi = BigInt(num);
    return input;
}