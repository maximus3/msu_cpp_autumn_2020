#pragma once

#include <iostream>

size_t getSizeByLength(size_t length);

class BigInt {
private:
    size_t size = 0, length = 0;
    int sign = 1;
    char* data = nullptr;

    int getEq(const BigInt& bi, bool abs=false) const;
public:
    BigInt(int value=0);
    BigInt(const std::string& value);
    BigInt(const BigInt& bi);
    BigInt(BigInt&& bi);

    BigInt& operator=(int value);
    BigInt& operator=(const BigInt &bi);
    BigInt& operator=(BigInt&& bi);

    const char& operator[] (size_t i) const;

    friend BigInt operator+(const BigInt &bi1, const BigInt &bi2);
    friend BigInt operator-(const BigInt &bi1, const BigInt &bi2i);
    friend BigInt operator*(const BigInt &bi1, const BigInt &bi2);
    BigInt operator-() const;

    bool operator<(const BigInt &bi) const;
    bool operator<=(const BigInt &bi) const;
    bool operator>(const BigInt &bi) const;
    bool operator>=(const BigInt &bi) const;
    bool operator==(const BigInt &bi) const;
    bool operator!=(const BigInt &bi) const;

    friend std::ostream& operator<< (std::ostream& out, const BigInt& bi);
    friend std::istream& operator>> (std::istream& input, BigInt& bi);

    ~BigInt();
};

