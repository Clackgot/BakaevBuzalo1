#pragma once
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAXLEN = 500; // ������������ ����� ����� = MAXLEN*LEN
const int BASE = 10 * 10 * 10 * 10; // ��������� ��, � ������� �������� �����
const int LEN = 4; // ������ ����� ����������� �������� ����� (������� base)

struct BigInt {
    int amount; // ���������� ���� � �����
    int digits[MAXLEN] = { 0 }; // ���������� ������ ���� �����, ����� ��������
    bool isNegative; // ���� ���������������: false: ����� >= 0; true: ����� < 0

    // ����������� �� ���������
    BigInt() {
        amount = 1;
        isNegative = false;
    }

    // ��������� ������������
    BigInt(signed char c);
    BigInt(unsigned char c);
    BigInt(signed short s);
    BigInt(unsigned short s);
    BigInt(signed int i);
    BigInt(unsigned int i);
    BigInt(signed long l);
    BigInt(unsigned long l);
    BigInt(signed long long l);
    BigInt(unsigned long long l);

    // ���������� ��� ������� �� 0
    class DivideByZero : exception {};

    // ���������� ��� ���������� ����� �� ��������������
    class NegativeSqrt : exception {};

    // ������ BigInt �� ������
    void makeBigInt(string str);

    // ����-�����
    void input();
    void output();

    // ������� �����
    const BigInt operator-() const;

    // ��������������� ������� ��� �������
    void shiftRight();

    // ��������������� ������� ��� �������� ������ � "��������������" ����
    void checkNegativeZero();

    // ���������
    friend bool operator==(const BigInt& lhs, const BigInt& rhs);
    friend bool operator!=(const BigInt& lhs, const BigInt& rhs);
    friend bool operator>(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<(const BigInt& lhs, const BigInt& rhs);
    friend bool operator>=(const BigInt& lhs, const BigInt& rhs);
    friend bool operator<=(const BigInt& lhs, const BigInt& rhs);

    // ����������
    friend BigInt operator+(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator-(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator*(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator/(const BigInt& lhs, const BigInt& rhs);
    friend BigInt operator%(const BigInt& lhs, const BigInt& rhs);

    // ���������� � �������������
    BigInt& operator+=(const BigInt& value);
    BigInt& operator-=(const BigInt& value);
    BigInt& operator*=(const BigInt& value);
    BigInt& operator/=(const BigInt& value);
    BigInt& operator%=(const BigInt& value);

    // ��������� � ���������
    const BigInt operator--();
    const BigInt operator--(int);
    const BigInt operator++();
    const BigInt operator++(int);

    // ������ � �������� �����/������
    friend ostream& operator<<(ostream& os, const BigInt& bigInt);
    friend istream& operator>>(istream& is, BigInt& bigInt);

    // �������� ��������/����������
    bool isOdd() const;
    bool isEven() const;

    // �������������� �������
    friend BigInt pow(BigInt a, BigInt n);
    friend BigInt fact(BigInt a);
    friend BigInt sqrt(const BigInt& a);
    friend BigInt abs(BigInt a);
};

// �������������� ������ � �����
void BigInt::makeBigInt(string str) {
    int pos = 0; // ��� ������� �� ������� � �������

    // ��������� ����, ��� ������������� ��������� ���� � �������� ������ �� ������
    if (str[0] == '-') {
        this->isNegative = true;
        str.erase(0, 1);
    }

    for (int i = str.size() - 1; i >= 0; i -= LEN) { // �������� � ��������� ����� � ��� � �������� �������
        // ��������� �� len ���� �� ���, ����� �� � LEN-��������� ������
        int start = i - LEN + 1;

        // �������� ������ �� ������� �������
        if (start < 0) {
            start = 0;
        }

        // ���������� ����� �� ������ � ����� � ������
        string dig = str.substr(start, i - start + 1);
        digits[pos++] = atoi(dig.c_str());
    }

    amount = pos; // ��������� ���������� ���� � �����

    checkNegativeZero();
}

// ���������� ������ � BigInt
void BigInt::input() {
    string str; // ������, � ������� ����������� �����
    cin >> str; // ��������� ����� � ������
    makeBigInt(str); // �������� �������������� ������ � �����
}

// �����
void BigInt::output() {
    // ��� ��������� base �������� ����� ����� �� ����������� base-���������
    // ������� � ����� �������� � ����������� ������, �� ������ ����� ��� �� ��������
    // ������� ����� ���� ��� ������������� �����
    if (isNegative) {
        cout << '-';
    }

    cout << digits[amount - 1];

    for (int i = amount - 2; i >= 0; i--) {
        cout << setfill('0') << setw(LEN) << digits[i];
    }
}

// ����� ����� �����
const BigInt BigInt::operator-() const {
    BigInt tmp = *this;
    if (this != 0) {
        tmp.isNegative = !tmp.isNegative;
    }
    return tmp;
}

// ����� �������� �� 1 ������ (�������� ����� �� BASE) - ��������������� ������� ��� �������
void BigInt::shiftRight() {
    for (int i = amount; i >= 1; i--) {
        digits[i] = digits[i - 1];
    }

    if (digits[amount]) {
        amount++;
    }
}

// ���������, ����� �� ����� ���� � ���������� ���� � ���� ������
void BigInt::checkNegativeZero() {
    if (this == 0) {
        this->isNegative = false;
    }
}

// �������������� ����� � BigInt
BigInt::BigInt(signed char c) {
    this->isNegative = c < 0;

    string str = to_string(abs(c));
    makeBigInt(str);
}

BigInt::BigInt(unsigned char c) {
    this->isNegative = false;
    string str = to_string(c);
    makeBigInt(str);
}

BigInt::BigInt(signed short s) {
    this->isNegative = s < 0;

    string str = to_string(abs(s));
    makeBigInt(str);
}

BigInt::BigInt(unsigned short s) {
    this->isNegative = false;
    string str = to_string(s);
    makeBigInt(str);
}

BigInt::BigInt(signed int i) {
    this->isNegative = i < 0;

    string str = to_string(abs(i));
    makeBigInt(str);
}

BigInt::BigInt(unsigned int i) {
    this->isNegative = false;
    string str = to_string(i);
    makeBigInt(str);
}

BigInt::BigInt(signed long l) {
    this->isNegative = l < 0;

    string str = to_string(abs(l));
    makeBigInt(str);
}

BigInt::BigInt(unsigned long l) {
    this->isNegative = false;
    string str = to_string(l);
    makeBigInt(str);
}

BigInt::BigInt(signed long long l) {
    this->isNegative = l < 0;

    string str = to_string(abs(l));
    makeBigInt(str);
}

BigInt::BigInt(unsigned long long l) {
    this->isNegative = false;
    string str = to_string(l);
    makeBigInt(str);
}

// ����������� ����������
BigInt operator+(const BigInt& lhs, const BigInt& rhs) {
    if (lhs.isNegative) {
        if (rhs.isNegative) {
            return -((-lhs) + (-rhs));
        }
        else {
            return rhs - (-lhs);
        }
    }
    else if (rhs.isNegative) {
        return lhs - (-rhs);
    }

    BigInt res;
    res.amount = max(lhs.amount, rhs.amount);
    int overflow = 0; // ������ �� �������������

    if (lhs.isNegative && rhs.isNegative) {
        res.isNegative = true;
    }

    for (int i = 0; i < res.amount || overflow; i++) {
        res.digits[i] = lhs.digits[i] + rhs.digits[i] + overflow;
        if (res.digits[i] >= BASE) {
            res.digits[i] -= BASE;
            overflow = 1;
        }
        else {
            overflow = 0;
        }
    }

    if (res.digits[res.amount]) {
        res.amount++;
    }

    return res;
}

BigInt operator-(const BigInt& lhs, const BigInt& rhs) {
    if (rhs.isNegative) {
        return lhs + (-rhs);
    }
    else if (lhs.isNegative) {
        return -(-lhs + rhs);
    }
    else if (lhs < rhs) {
        return -(rhs - lhs);
    }

    BigInt res = lhs;

    if (rhs > lhs) {
        res = rhs - lhs;
        res.isNegative = true;
    }

    for (int i = 0; i < res.amount; i++) {
        res.digits[i] -= rhs.digits[i];
        if (res.digits[i] < 0) {
            res.digits[i] += BASE;
            res.digits[i + 1]--;
        }
    }

    // �������� ���������� �����
    int pos = res.amount;

    while (pos && !res.digits[pos]) {
        pos--;
    }

    res.amount = pos + 1;

    return res;
}

BigInt operator*(const BigInt& lhs, const BigInt& rhs) {
    BigInt res;

    if (!(!lhs.isNegative && !rhs.isNegative) || (lhs.isNegative && rhs.isNegative)) {
        res.isNegative = true;
    }

    for (int i = 0; i < lhs.amount; i++) {
        int overflow = 0;

        for (int j = 0; j < rhs.amount || overflow; j++) {
            res.digits[i + j] += lhs.digits[i] * rhs.digits[j] + overflow;
            overflow = res.digits[i + j] / BASE;
            res.digits[i + j] -= overflow * BASE;
        }
    }

    // �������� ���������� �����
    int pos = lhs.amount + rhs.amount;

    while (pos > 0 && !res.digits[pos]) {
        pos--;
    }

    res.amount = pos + 1;

    res.checkNegativeZero();

    return res;
}

BigInt operator/(const BigInt& lhs, const BigInt& rhs) {
    // ������� ������ ��� ������� �� 0
    if (rhs == 0) {
        throw BigInt::DivideByZero();
    }

    if (rhs.isNegative) { // �� ���������, ��� �������
        return lhs / (-rhs);
    }

    BigInt res;
    BigInt curValue;

    if (!(!lhs.isNegative && !rhs.isNegative) || (lhs.isNegative && rhs.isNegative)) {
        res.isNegative = true;
    }

    // ��������� ������� � �������, ������� �� ������� ������� � ��������� �������� �����
    for (int i = lhs.amount - 1; i >= 0; i--) {
        curValue.shiftRight();
        curValue.digits[0] = lhs.digits[i];

        // ��������� ����� part, ��� rhs*part <= curValue
        int part = 0;
        int lBorder = 0;
        int rBorder = BASE;

        while (lBorder <= rBorder) {
            int median = (lBorder + rBorder) / 2;
            BigInt cur = rhs * median;

            if (cur < curValue || cur == curValue) {
                part = median;
                lBorder = median + 1;
            }
            else {
                rBorder = median - 1;
            }
        }

        res.digits[i] = part;
        curValue -= rhs * part;
    }

    // �������� ���������� �����
    int pos = lhs.amount;

    while (pos >= 0 && !res.digits[pos]) {
        pos--;
    }

    res.amount = pos + 1;

    res.checkNegativeZero();

    return res;
}

BigInt operator%(const BigInt& lhs, const BigInt& rhs) {
    BigInt res;

    res = lhs - (lhs / rhs) * rhs;

    if (res.isNegative) {
        res = res + rhs;
    }

    res.isNegative = false;

    return res;
}

// ���������� � �������������
BigInt& BigInt::operator+=(const BigInt& value) {
    return *this = (*this + value);
}

BigInt& BigInt::operator-=(const BigInt& value) {
    return *this = (*this - value);
}

BigInt& BigInt::operator*=(const BigInt& value) {
    return *this = (*this * value);
}

BigInt& BigInt::operator/=(const BigInt& value) {
    return *this = (*this / value);
}

BigInt& BigInt::operator%=(const BigInt& value) {
    return *this = (*this % value);
}

// ���������� ���������
const BigInt BigInt::operator--() {
    return *this -= 1;
}

// ����������� ���������
const BigInt BigInt::operator--(int) {
    *this -= 1;
    return *this + 1;
}

// ���������� ���������
const BigInt BigInt::operator++() {
    return *this += 1;
}

// ����������� ���������
const BigInt BigInt::operator++(int) {
    *this += 1;
    return *this - 1;
}

// ����������� ��������� ���������
bool operator==(const BigInt& lhs, const BigInt& rhs) {
    if (lhs.amount != rhs.amount) {
        return false;
    }

    if (lhs.isNegative != rhs.isNegative) {
        return false;
    }

    for (int i = 0; i < lhs.amount; i++) {
        if (lhs.digits[i] != rhs.digits[i]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs == rhs);
}

bool operator>(const BigInt& lhs, const BigInt& rhs) {
    if (!lhs.isNegative && rhs.isNegative) {
        return true;
    }

    if (lhs.isNegative && !rhs.isNegative) {
        return false;
    }

    if (!lhs.isNegative && !rhs.isNegative && (lhs.amount != rhs.amount)) {
        return lhs.amount > rhs.amount;
    }

    if (lhs.isNegative && rhs.isNegative && (lhs.amount != rhs.amount)) {
        return lhs.amount < rhs.amount;
    }

    for (int i = lhs.amount - 1; i >= 0; i--) {
        if ((lhs.digits[i] != rhs.digits[i]) && (!lhs.isNegative && !rhs.isNegative)) {
            return lhs.digits[i] > rhs.digits[i];
        }
        else if ((lhs.digits[i] != rhs.digits[i]) && (lhs.isNegative && rhs.isNegative)) {
            return lhs.digits[i] < rhs.digits[i];
        }
    }

    return false;
}

bool operator<(const BigInt& lhs, const BigInt& rhs) {
    if (!lhs.isNegative && rhs.isNegative) {
        return false;
    }

    if (lhs.isNegative && !rhs.isNegative) {
        return true;
    }

    if (!lhs.isNegative && !rhs.isNegative && (lhs.amount != rhs.amount)) {
        return lhs.amount < rhs.amount;
    }

    if (lhs.isNegative && rhs.isNegative && (lhs.amount != rhs.amount)) {
        return lhs.amount > rhs.amount;
    }

    for (int i = lhs.amount - 1; i >= 0; i--) {
        if ((lhs.digits[i] != rhs.digits[i]) && (!lhs.isNegative && !rhs.isNegative)) {
            return lhs.digits[i] < rhs.digits[i];
        }
        else if ((lhs.digits[i] != rhs.digits[i]) && (lhs.isNegative && rhs.isNegative)) {
            return lhs.digits[i] > rhs.digits[i];
        }
    }

    return false;
}

bool operator>=(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs < rhs);
}

bool operator<=(const BigInt& lhs, const BigInt& rhs) {
    return !(lhs > rhs);
}

// ������ ����� � ����� ������
ostream& operator<<(ostream& os, const BigInt& bigInt) {
    if (bigInt.isNegative) {
        os << '-';
    }

    os << bigInt.digits[bigInt.amount - 1];

    for (int i = bigInt.amount - 2; i >= 0; i--) {
        os << setfill('0') << setw(LEN) << bigInt.digits[i];
    }

    return os;
}

// ������ ����� � ����� �����
istream& operator>>(istream& is, BigInt& bigInt) {
    string str;
    is >> str;

    int pos = 0; // ��� ������� �� ������� � �������

    // ��������� ����, ��� ������������� ��������� ���� � �������� ������ �� ������
    if (str[0] == '-') {
        bigInt.isNegative = true;
        str.erase(0, 1);
    }

    for (int i = str.size() - 1; i >= 0; i -= LEN) { // �������� � ��������� ����� � ��� � �������� �������
        // ��������� �� len ���� �� ���, ����� �� � LEN-��������� ������
        int start = i - LEN + 1;

        // �������� ������ �� ������� �������
        if (start < 0) {
            start = 0;
        }

        // ���������� ����� �� ������ � ����� � ������
        string dig = str.substr(start, i - start + 1);
        bigInt.digits[pos++] = atoi(dig.c_str());
    }

    bigInt.amount = pos; // ��������� ���������� ���� � �����

    return is;
}

// �������� ����������/��������
bool BigInt::isOdd() const {
    if (this->amount == 0) {
        return false;
    }
    return this->digits[0] & 1;
}

bool BigInt::isEven() const {
    return !this->isOdd();
}

// ������� (��������) ���������� � �������, �������� ������ � �������������� ���������
BigInt pow(BigInt a, BigInt n) {
    if (n.isNegative) {
        return pow(a, -n);
    }

    // ��� ������� ����������� ����� ��� ���������� �������������� ����� � ������/�������� �������
    bool minus = false;
    if (a.isNegative) {
        minus = n.isOdd();
    }

    BigInt res = 1;

    while (n >= 0) {
        if (n.isOdd()) {
            res *= a;
        }
        a *= a;
        n /= 2;
    }

    res.isNegative = minus;

    return res;
}

// ���������, ����������
BigInt fact(BigInt a) {
    if (a.isNegative) {
        return 0;
    }

    if (a == 0) {
        return 1;
    }

    return a * fact(a - 1);
}

// ���������� ����� (�����, ������� �������� �� ����������� ������) �������� ��������
BigInt sqrt(const BigInt& a) {
    if (a.isNegative) {
        throw BigInt::NegativeSqrt();
    }

    BigInt res;
    BigInt lBorder, rBorder;
    rBorder = a;

    while (lBorder <= rBorder) {
        BigInt median = (lBorder + rBorder) / 2;

        if (median * median <= a) {
            res = median;
            lBorder = median + 1;
        }
        else {
            rBorder = median - 1;
        }
    }

    return res;
}

BigInt abs(BigInt a) {
    a.isNegative = false;
    return a;
}
