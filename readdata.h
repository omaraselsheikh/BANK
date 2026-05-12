#pragma once

#include <iostream>
#include <string>
#include <vector>

// 'inline' stops the duplicate symbol error for this array
inline const std::string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

struct Transaction
{
    int duration;
    std::string type;
};

std::vector<Transaction> readtransaction();

struct Teller
{
    int numtellers;
    std::string days;
};

std::vector<Teller> readingalltellers();

struct YearlyCustomerTarget
{
    int yearlyTarget;
    int dailyavg;
};

YearlyCustomerTarget readingYearlyCustomerTarget();

struct WorkingHours
{
    std::string opening;
    std::string closing;
    int total;
};

WorkingHours readingWorkingHours();

std::string formatToThreeDigits(int x);
std::vector<std::string> getIDs(int n);
int HourstoMinutes(std::string time);