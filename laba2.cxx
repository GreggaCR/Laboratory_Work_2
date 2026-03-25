#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Ordinary {
public:
    Ordinary();
    Ordinary(long long n, long long d);

    void print() const;
    void printWithInfo() const;
    double toDecimal() const;

    Ordinary operator+(const Ordinary& other) const;
    Ordinary operator-(const Ordinary& other) const;
    Ordinary operator*(const Ordinary& other) const;
    Ordinary operator/(const Ordinary& other) const;

private:
    long long num;
    long long den;
    bool wasReduced;   // флаг сокращения

    void reduce();
    long long gcd(long long a, long long b) const;
};



int main() {

    cout << "Ввод первой дроби" << endl;
    Ordinary A;

    cout << "Ввод второй дроби" << endl;
    Ordinary B;

 
    cout << "РЕЗУЛЬТАТЫ ОПЕРАЦИЙ" << endl;
    

    Ordinary add = A + B;
    cout << "Сложение: ";
    add.printWithInfo();
    cout << "Десятичный вид: " << add.toDecimal() << "\n\n";

    Ordinary sub = A - B;
    cout << "Вычитание: ";
    sub.printWithInfo();
    cout << "Десятичный вид: " << sub.toDecimal() << "\n\n";

    Ordinary mul = A * B;
    cout << "Умножение: ";
    mul.printWithInfo();
    cout << "Десятичный вид: " << mul.toDecimal() << "\n\n";

    Ordinary div = A / B;
    cout << "Деление: ";
    div.printWithInfo();
    cout << "Десятичный вид: " << div.toDecimal() << "\n\n";


    return 0;
}



Ordinary::Ordinary() {
    cout << "Введите числитель и знаменатель через пробел: ";
    cin >> num >> den;

    if (den == 0) {
        cout << "Ошибка! Деление на ноль!" << endl;
        exit(1);
    }

    wasReduced = false;
    reduce();
}

Ordinary::Ordinary(long long n, long long d) {
    num = n;
    den = d;

    if (den == 0) {
        cout << "Ошибка! Деление на ноль!" << endl;
        exit(1);
    }

    wasReduced = false;
    reduce();
}


long long Ordinary::gcd(long long a, long long b) const {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return abs(a);
}

void Ordinary::reduce() {


    long long divisor = gcd(num, den);

    if (divisor > 1)
        wasReduced = true;

    num /= divisor;
    den /= divisor;

    // Нормализация знака
    if (den < 0) {
        num = -num;
        den = -den;
    }
}


void Ordinary::print() const {
    cout << num << "/" << den << endl;
}

void Ordinary::printWithInfo() const {
    cout << num << "/" << den;

    if (wasReduced)
        cout << "  (дробь была сокращена)";

    cout << endl;
}

double Ordinary::toDecimal() const {
    return static_cast<double>(num) / den;
}



Ordinary Ordinary::operator+(const Ordinary& other) const {
    long long new_num = num * other.den + other.num * den;
    long long new_den = den * other.den;
    return Ordinary(new_num, new_den);
}

Ordinary Ordinary::operator-(const Ordinary& other) const {
    long long new_num = num * other.den - other.num * den;
    long long new_den = den * other.den;
    return Ordinary(new_num, new_den);
}


Ordinary Ordinary::operator*(const Ordinary& other) const {
    long long new_num = num * other.num;
    long long new_den = den * other.den;
    return Ordinary(new_num, new_den);
}

Ordinary Ordinary::operator/(const Ordinary& other) const {
    if (other.num == 0) {
        cout << "Ошибка! Деление на ноль!" << endl;
        exit(1);
    }

    long long new_num = num * other.den;
    long long new_den = den * other.num;
    return Ordinary(new_num, new_den);
}
