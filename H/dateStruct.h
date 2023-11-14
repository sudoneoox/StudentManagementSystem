#ifndef DATESTRUCT_H
#define DATESTRUCT_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct DateStruct
{
public:
    string day;
    string month;
    string year;
    DateStruct() : day("0"), month("0"), year("0") {}                       // default constructor
    DateStruct(string d, string m, string y) : day(d), month(m), year(y) {} // overloaded constructor
    DateStruct(const DateStruct &otherDate) : day(otherDate.day), month(otherDate.month), year(otherDate.year) {}
    bool operator<(const DateStruct &RHS) const // need to overload this operator in order to add it into a map data structure
    {
        if (year != RHS.year)
            return year < RHS.year;
        if (month != RHS.month)
            return month < RHS.month;
        return day < RHS.day;
    }
};

#endif // !DATESTRUCT_H