#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "readdata.h"

using namespace std;

vector<Transaction> readtransaction()
{
    string header;
    Transaction t;
    vector<Transaction> alltransactions;
    ifstream file("transactions.txt");
    getline(file, header);
    while (getline(file, t.type))
    {
        if (file >> t.duration)
        {
            alltransactions.push_back(t);
            file.ignore(1000, '\n');
        }
    }
    return alltransactions;
}

vector<Teller> readingalltellers()
{
    vector<Teller> alltellers;
    string header;
    ifstream file("tellers.txt");
    getline(file, header);
    Teller t;
    for (int i = 0; i < 7; i++)
    {
        file >> t.days >> t.numtellers;
        alltellers.push_back(t);
    }
    file.close();
    return alltellers;
}

YearlyCustomerTarget readingYearlyCustomerTarget()
{
    YearlyCustomerTarget yct;
    ifstream file("yearlytarget.txt");
    file >> yct.yearlyTarget;
    file.ignore(1000, '\n');
    file >> yct.dailyavg;
    file.ignore(1000, '\n');
    file.close();
    return yct;
}

int HourstoMinutes(string time)
{
    return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 + (time[3] - '0') * 10 + (time[4] - '0');
}

WorkingHours readingWorkingHours()
{
    WorkingHours h;
    string header;
    ifstream file("workinghours.txt");
    if (file.is_open())
    {
        getline(file, header);
        getline(file, h.opening);
        getline(file, h.closing);
        h.total = HourstoMinutes(h.closing) - HourstoMinutes(h.opening);
        file.close();
    }
    return h;
}

string formatToThreeDigits(int x)
{
    string s = to_string(x);
    if (s.length() == 1)
        return "00" + s;
    else if (s.length() == 2)
        return "0" + s;
    else
        return s;
}

vector<string> getIDs(int n)
{
    vector<string> ID;
    for (int i = 0; i < n; i++)
    {
        ID.push_back(formatToThreeDigits(i + 1));
    }
    return ID;
}