#ifndef PROJECT_MAINWINDOW_H
#define PROJECT_MAINWINDOW_H

#include <iostream>
#include <vector>
#include "BigDecimalInt.h"
using namespace std;
class MainWindow {
    vector<BigDecimalInt> numbers;
    void showWindow();
    void addNumber();
    void removeNumber();
    bool showNumbers();
    void editNumber();
    void summation();
    void subtraction();
    bool validNumber(string& number);
    static void paragraph(const string& tmp);
public:
    MainWindow();
};


#endif //PROJECT_MAINWINDOW_H