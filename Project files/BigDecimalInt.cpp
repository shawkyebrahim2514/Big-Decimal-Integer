#include "BigDecimalInt.h"

#include <iostream>
BigDecimalInt::BigDecimalInt(int n)
{
    // append each digit from right to the class number deque
    if(n < 0) sign = false;
    else sign = true;
    n = abs(n);
    while (n)
    {
        number.push_front(n%10);
        n /= 10;
    }
}

BigDecimalInt::BigDecimalInt(std::string n)
{
    int start = isValidNumber(n);
    if(!~start) return;
    // add the sign
    if(start)
    {
        if(n[0] == '+') this->sign = 1;
        else this->sign = 0;
    }
    else this->sign = 1;
    // append each digit to the class number deque
    for (int i = start; i < n.size(); ++i)
    {
        number.push_back(n[i]-'0');
    }
    deleteZeros();
}

BigDecimalInt BigDecimalInt::operator+(BigDecimalInt a)
{
    // if the two numbers has the different sign
    // then we should do subtraction instead of summation of these two number classes
    if(this->sign != a.sign)
    {
        a.sign = this->sign;
        return (*this - a);
    }
    BigDecimalInt tmp("");
    tmp = *this;
    // make the length of the two number classes equal each other
    // the smallest size will append zeros in front of it
    equalNumberLength(tmp, a);
    tmp.doSummation(a);
    tmp.deleteZeros();
    return tmp;
}

BigDecimalInt BigDecimalInt::operator-(BigDecimalInt a)
{
    // if the two numbers has the different sign
    // then we should do summation instead of subtraction of these two number classes
    if(this->sign != a.sign)
    {
        a.sign = this->sign;
        return (*this + a);
    }
    BigDecimalInt tmp("");
    tmp = *this;
    // make the length of the two number classes equal each other
    // the smallest size will append zeros in front of it
    equalNumberLength(tmp, a);
    tmp.doSubtraction(a);
    tmp.deleteZeros();
    return tmp;
}

BigDecimalInt& BigDecimalInt::operator=(const BigDecimalInt& a)
{
    this->number = a.number;
    this->sign = a.sign;
    return *this;
}

void BigDecimalInt::equalNumberLength(BigDecimalInt &a, BigDecimalInt &b)
{
    // make the length of the two number classes equal each other
    // the smallest size will append zeros in front of it
    int dif = abs(a.number.size() - b.number.size());
    if(a.number.size() < b.number.size())
        for (int i = 0; i < dif; ++i)
            a.number.push_front(0);
    else
        for (int i = 0; i < dif; ++i)
            b.number.push_front(0);
}

bool BigDecimalInt::operator<(const BigDecimalInt& a)
{
    if(this->sign != a.sign) return this->sign < a.sign;
    return this->number < a.number;
}

bool BigDecimalInt::operator>(const BigDecimalInt& a) {
    if(this->sign != a.sign) return this->sign > a.sign;
    return this->number > a.number;
}

bool BigDecimalInt::operator==(const BigDecimalInt& a) {
    if(this->sign != a.sign) return 0;
    return this->number == a.number;
}

std::ostream &operator<<(std::ostream &output, BigDecimalInt a) {
    // if the number is 0, then we should print only 0 without any sign
    if(a.number.size() == 1 && !a.number[0])
    {
        output << 0;
        return output;
    }
    // print first the sign before the number
    output << (a.sign ? '+' : '-');
    for(auto val : a.number)
    {
        output << val;
    }
    return output;
}

void BigDecimalInt::deleteZeros() {
    // delete leading zeros from the beginning of the number (from right)
    while (this->number.size() > 1 && !this->number.front())
        this->number.pop_front();
    if(this->number.size() == 1 && !this->number[0]) this->sign = 1;
}

int BigDecimalInt::isValidNumber(std::string &number) {
    int start;
    if(number[0] == '-' || number[0] == '-') start = 1;
    else start = 0;
    for (int i = start; i < number.size(); ++i)
    {
        if(number[i] < '0' || number[i] > '9')
        {
            std::cout << "No valid number!\n";
            return -1;
        }
    }
    return start;
}

void BigDecimalInt::doSummation(BigDecimalInt& a)
{
    // do summation between digits
    int position = (int)this->number.size() - 1;
    while (position >= 0){
        this->number[position] += a.number[position];
        // if the number is greater than 9
        // we should increase the digit before ours by one
        if(this->number[position] > 9)
        {
            if(position - 1 >= 0) this->number[position - 1] ++;
            else
            {
                // if we are in the first index (0) we should append this one in the front
                this->number.push_front(1);
                this->number[1] %= 10;
                break;
            }
            this->number[position] %= 10;
        }
        position --;
    }
}

void BigDecimalInt::doSubtraction(BigDecimalInt& a) {
    // (this class) should have the smallest number
    if(this->number > a.number) swap(this->number, a.number);
    else this->sign = !this->sign;
    int position = (int)this->number.size() - 1;
    while (position >= 0)
    {
        this->number[position] = a.number[position] - this->number[position];
        if(this->number[position] < 0)
        {
            if(position)
            {
                a.number[position - 1] --;
                this->number[position] += 10;
            }
        }
        position --;
    }
}