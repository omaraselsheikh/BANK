#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "readdata.h"

struct CustomerData
{
    std::string id;
    std::string arrivaltime;
    std::string transactionname;
    int transactionduration;
    int arrivalminute;
    int serviceStartMinute;
    int serviceEndMinute;
    int waitingMinutes;
    bool served;
    int assignedTeller;
};

struct TellerData
{
    std::string id;
    std::string assignedTransactionType;
    int assignedTransactionDuration;
    int freeAtMinute;
    int customersServed;
    int totalServiceMinutes;
    int totalIdleMinutes;
};

int dailycustomernumber(int avg);
std::string converttostring(int totalMinutes);
std::vector<std::string> getArrivalTime();
std::vector<CustomerData> generatingCustomers();

Transaction getTransactionAt(const std::vector<Transaction> &list, int index);
std::vector<TellerData> generatingTellers(int dayIndex);
int getDaySimulation();
