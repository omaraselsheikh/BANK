#pragma once

#include <vector>
#include <string>
#include "GenerateCustomerTeller.h"

struct DailyResult
{
    std::string dayName;
    int customersGenerated;
    int customersServed;
    int customersNotServed;
    double avgWaitingMinutes;
    int peakHourStart;
    int peakHourCount;
    std::vector<CustomerData> customers;
    std::vector<TellerData> tellers;
};

void displayRunSimulationMenu();
DailyResult simulateDay(int dayIndex);