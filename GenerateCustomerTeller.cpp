#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include "GenerateCustomerTeller.h"
#include "readdata.h"

using namespace std;

int dailycustomernumber(int avg)
{
    static bool flag = true;
    if (flag)
    {
        flag = !flag;
        return (avg + rand() % 20);
    }
    else
    {
        flag = !flag;
        return (avg - rand() % 20);
    }
}

string converttostring(int totalMinutes)
{
    int hour = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    string hourStr = to_string(hour);
    string minStr = to_string(minutes);
    if (hour < 10)
        hourStr = "0" + hourStr;
    if (minutes < 10)
        minStr = "0" + minStr;
    return hourStr + ":" + minStr;
}

vector<string> getArrivalTime()
{
    YearlyCustomerTarget yct;
    int totalcustomers = dailycustomernumber(yct.dailyavg);
    vector<string> arrivaltime;
    WorkingHours h = readingWorkingHours();
    int timeinterval = h.total / totalcustomers;
    int arrivalhour = HourstoMinutes(h.opening) + rand() % timeinterval;
    arrivaltime.push_back(converttostring(arrivalhour));

    for (int i = 1; i < totalcustomers; i++)
    {
        arrivalhour = arrivalhour + rand() % timeinterval;
        arrivaltime.push_back(converttostring(arrivalhour));
    }
    return arrivaltime;
}

vector<CustomerData> generatingCustomers()
{
    YearlyCustomerTarget yct;
    int totalcustomers = dailycustomernumber(yct.dailyavg);
    CustomerData c;
    WorkingHours wh = readingWorkingHours();
    vector<CustomerData> allcustomers;
    vector<string> IDs = getIDs(totalcustomers);
    vector<Transaction> transactionPool = readtransaction();
    vector<string> arrivaltimepool = getArrivalTime();

    ofstream file("customerdata.txt", ios::trunc);
    file << left << setw(40) << "Customer Id" << left << setw(40) << "Arrival Time" << "Transaction type\n========================================================================================================================\n";

    for (int i = 0; i < totalcustomers; i++)
    {
        c.id = IDs[i];
        c.arrivaltime = arrivaltimepool[i];
        c.arrivalminute = HourstoMinutes(arrivaltimepool[i]) - HourstoMinutes(wh.opening);
        int randomIndex = rand() % transactionPool.size();
        c.transactionname = transactionPool[randomIndex].type;
        c.transactionduration = transactionPool[randomIndex].duration;
        c.serviceStartMinute = 0;
        c.serviceEndMinute = 0;
        c.waitingMinutes = 0;
        c.served = false;
        c.assignedTeller = 0;

        allcustomers.push_back(c);
        file << left << setw(40) << c.id << left << setw(40) << c.arrivaltime << c.transactionname << "\n";
    }
    file.close();
    return allcustomers;
}

Transaction getTransactionAt(const vector<Transaction> &list, int index)
{
    if (index >= list.size())
        index = index - list.size();
    return list[index];
}

int getDaySimulation()
{
    cout << "=========================================\n";
    for (int i = 0; i < 7; i++)
        cout << i + 1 << ". " << days[i] << "\n";
    cout << "========================================\nEnter the Day You want to Simulate: ";
    int i;
    cin >> i;
    while (i < 1 || i > 7)
    {
        cout << "Out of Range, Please Re-Enter your choice: ";
        cin >> i;
    }
    return i - 1;
}

vector<TellerData> generatingTellers(int dayIndex)
{
    Teller t;
    TellerData td;
    vector<TellerData> alltellers;
    vector<Teller> tellersperday = readingalltellers();
    int x = tellersperday[dayIndex].numtellers;
    vector<string> IDs = getIDs(x);
    vector<Transaction> transactionPool = readtransaction();

    ofstream file("tellersdata.txt", ios::trunc);
    file << left << setw(40) << "Teller Id" << left << setw(40) << "Transaction assigned type" << "Transaction assigned duration\n========================================================================================================================\n";

    for (int i = 0; i < x; i++)
    {
        td.id = IDs[i];
        Transaction current = getTransactionAt(transactionPool, i);
        td.assignedTransactionType = current.type;
        td.assignedTransactionDuration = current.duration;
        td.freeAtMinute = 0;
        td.customersServed = 0;
        td.totalServiceMinutes = 0;
        td.totalIdleMinutes = 0;
        alltellers.push_back(td);
        file << left << setw(40) << td.id << left << setw(40) << td.assignedTransactionType << td.assignedTransactionDuration << "\n";
    }
    file.close();
    return alltellers;
}