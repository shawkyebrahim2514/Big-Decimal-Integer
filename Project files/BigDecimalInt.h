#ifndef PROJECT_BIGDECIMALINT_H
#define PROJECT_BIGDECIMALINT_H
#include <deque>
#include <ostream>
#include <regex>
class BigDecimalInt {
    int size;
    bool sign;
    std::deque<int> number;
    void equalNumberLength(BigDecimalInt& a, BigDecimalInt& b);
    void deleteZeros();
    static int isValidNumber(std::string& number);
    void doSummation(BigDecimalInt& a);
    void doSubtraction(BigDecimalInt& a);
public:
    explicit BigDecimalInt(int n);
    explicit BigDecimalInt(std::string n);
    BigDecimalInt operator+ (BigDecimalInt a);
    BigDecimalInt operator- (BigDecimalInt a);
    BigDecimalInt& operator= (const BigDecimalInt& a);
    bool operator< (const BigDecimalInt& a);
    bool operator> (const BigDecimalInt& a);
    bool operator== (const BigDecimalInt& a);
    friend std::ostream& operator<<(std::ostream& output, BigDecimalInt a);
};



#endif //PROJECT_BIGDECIMALINT_H
