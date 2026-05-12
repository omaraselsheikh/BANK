#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include "readdata.h"
#include "GenerateCustomerTeller.h"
#include "RunSimulation.h"

using namespace std;

void displayRunSimulationMenu()
{
    cout << "========================================\nRun Simulation selected.\n========================================\n1. Run daily simulation\n2. Run weekly simulation\n3. Run full year simulation\n4. Back to Main Menu\n========================================\n";
}

vector<TellerData> assignedTellers(vector<CustomerData> customers, vector<TellerData> tellers)
{
    vector<TellerData> asstellers;
    for (auto &customer : customers)
    {
        bool foundTeller = false;
        for (auto &teller : tellers)
        {
            if (teller.assignedTransactionType == customer.transactionname)
            {
                asstellers.push_back(teller);
                foundTeller = true;
                break;
            }
        }
        if (!foundTeller)
            cout << "No teller currently handles " << customer.transactionname << "\n";
    }
    return asstellers;
}

static void processQueue(vector<CustomerData> &customers, vector<TellerData> &tellers)
{
    WorkingHours wh = readingWorkingHours();
    int wMin = wh.total;
    int n = (int)customers.size();

    for (int i = 0; i < n; i++)
    {
        CustomerData &c = customers[i];
        vector<TellerData> asstellers = assignedTellers(customers, tellers);
        if (asstellers.empty())
            continue;

        int bestT = 0;
        for (size_t t = 1; t < asstellers.size(); t++)
            if (asstellers[t].freeAtMinute < asstellers[bestT].freeAtMinute)
                bestT = t;

        int startMin = max(c.arrivalminute, tellers[bestT].freeAtMinute);
        int duration = c.transactionduration;
        int endMin = startMin + duration;

        if (endMin > wMin)
        {
            c.served = false;
            break;
        }
        if (tellers[bestT].freeAtMinute < startMin)
            tellers[bestT].totalIdleMinutes += startMin - tellers[bestT].freeAtMinute;

        c.served = true;
        c.serviceStartMinute = startMin;
        c.serviceEndMinute = endMin;
        c.waitingMinutes = startMin - c.arrivalminute;
        c.assignedTeller = stoi(tellers[bestT].id);

        tellers[bestT].freeAtMinute = endMin;
        tellers[bestT].customersServed++;
        tellers[bestT].totalServiceMinutes += duration;
    }

    for (auto &t : tellers)
        if (t.freeAtMinute < wMin)
            t.totalIdleMinutes += wMin - t.freeAtMinute;
}

string formatTime(int openingtimeinmin, int offsetMinutes)
{
    int total = openingtimeinmin + offsetMinutes;
    int h = total / 60, m = total % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << h << ":" << std::setw(2) << std::setfill('0') << m;
    return oss.str();
}

static void findPeakHour(const vector<CustomerData> &customers, int wMin, int &peakStart, int &peakCount)
{
    peakStart = 0;
    peakCount = 0;
    for (int s = 0; s < wMin - 60; s++)
    {
        int cnt = 0;
        for (auto &c : customers)
            if (c.arrivalminute >= s && c.arrivalminute < s + 60)
                cnt++;
        if (cnt > peakCount)
        {
            peakCount = cnt;
            peakStart = s;
        }
    }
}

DailyResult simulateDay(int dayIndex)
{
    WorkingHours wh = readingWorkingHours();
    DailyResult result;
    result.customers = generatingCustomers();
    result.tellers = generatingTellers(dayIndex);
    result.customersGenerated = (int)result.customers.size();
    result.dayName = days[dayIndex];

    cout << "========================================\n";
    cout << "Simulating " << days[dayIndex] << "...\n";
    cout << "========================================\n";
    cout << "Customers Generated: " << result.customersGenerated << "\nProcessing customers...\n[========================================] 100%";

    processQueue(result.customers, result.tellers);

    result.customersServed = 0;
    result.customersNotServed = 0;
    double totalWait = 0;

    for (auto &c : result.customers)
    {
        if (c.served)
        {
            result.customersServed++;
            totalWait += c.waitingMinutes;
        }
        else
            result.customersNotServed++;
    }
    result.avgWaitingMinutes = result.customersServed > 0 ? totalWait / result.customersServed : 0.0;
    findPeakHour(result.customers, wh.total, result.peakHourStart, result.peakHourCount);

    cout << "\n=== Daily Summary ===\nCustomers Served:     " << result.customersServed << "\nCustomers Not Served: " << result.customersNotServed << "\n";
    cout << fixed << setprecision(1) << "Average Waiting Time: " << result.avgWaitingMinutes << " minutes\n";
    cout << "Peak Hour: " << formatTime(HourstoMinutes(wh.opening), result.peakHourStart) << " - "
         << formatTime(HourstoMinutes(wh.opening), result.peakHourStart + 60) << " (" << result.peakHourCount << " customers)\n";

    return result;
}