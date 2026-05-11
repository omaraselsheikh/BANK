#pragma once

#include "includes.h"

// The Struct definition stays in the header
struct Transaction
{
    int duration;
    string type;
};

// Function Prototypes (tell the compiler these exist elsewhere)
vector<Transaction> readtransaction();

struct Teller
{
    int numtellers;
    string day;
};

struct YearlyCustomerTarget
{
    int yearlyTarget;
    int dailyavg;
};

YearlyCustomerTarget readingYearlyCustomerTarget();

struct WorkingHours
{
    string opening;
    string closing;
    int total;
};

WorkingHours readingWorkingHours();

// 2. Function Prototypes (Declarations)
// These tell the compiler the "names" and "types" of your functions
vector<Teller> readingalltellers();

string formatToThreeDigits(int x);
vector<string> getIDs(int n);
int HourstoMinutes(string time);
