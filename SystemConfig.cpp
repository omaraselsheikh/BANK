#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>
#include <algorithm>
#include "readdata.h"
#include "SystemConfig.h"

using namespace std;

void displaySystemConfigMenu()
{
    cout << "========================================\nSystem Configuration selected.\n========================================\n1. Number of Tellers\n2. Working Hours\n3. Transaction Types\n4. Yearly Customer Target\n5. View Current Configuration\n6. Back to Main Menu\n========================================\n";
}

void saveToFile(const string daysArr[], const int numoftellers[], int size)
{
    ofstream file("tellers.txt");
    file << "Number_of_Tellers_Data\n";
    for (int i = 0; i < size; i++)
    {
        file << daysArr[i] << "\n"
             << numoftellers[i] << "\n";
    }
    file.close();
}

bool isValidNumber(int num) { return num >= 1 && num <= 10; }

void numberofTellers()
{
    int numTellers[7];
    for (int i = 0; i < 7; i++)
    {
        cout << "Enter the number of tellers on day " << days[i] << ": ";
        while (!(cin >> numTellers[i]) || !isValidNumber(numTellers[i]))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR\nPLEASE RE-ENTER A POSSIBLE NUMBER: ";
        }
    }
    saveToFile(days, numTellers, 7);
}

void DisplayTellers()
{
    cout << "=========================================\nCurrent Number of Tellers Configuration:\n=========================================\n";
    ifstream file("tellers.txt");
    string d[7];
    int numTellers[7];
    string header;
    int i = 0, totalTellers = 0;
    getline(file, header);
    while (i < 7 && getline(file, d[i]))
    {
        if (file >> numTellers[i])
        {
            totalTellers += numTellers[i];
            i++;
            file.ignore();
        }
    }
    file.close();
    cout << left << setw(15) << "Day" << "Number of Tellers\n-----------------------------------\n";
    for (int j = 0; j < i; j++)
        cout << left << setw(15) << d[j] << numTellers[j] << "\n";
    cout << "-----------------------------------\nTotal Tellers: " << totalTellers << "\n";
}

void saveToFile(string opening, string closing)
{
    ofstream file("workinghours.txt");
    file << "Working_hours_Data\n"
         << opening << "\n"
         << closing;
    file.close();
}

bool isValidTime(string time)
{
    if (time.length() != 5 || time[2] != ':')
        return false;
    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');
    return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
}

void setWorkingHours()
{
    string opening, closing;
    do
    {
        cout << "ENTER OPENING TIME IN THIS FORMAT (HH:MM) 24_HR Format:\n";
        cin >> opening;
        while (!isValidTime(opening))
        {
            cout << "ERROR\nPLEASE RE-ENTER A VALID TIME\n";
            cin >> opening;
        }
        cout << "ENTER CLOSING TIME IN THIS FORMAT (HH:MM) 24_HR Format:\n";
        cin >> closing;
        while (!isValidTime(closing))
        {
            cout << "ERROR\nPLEASE RE-ENTER A VALID TIME\n";
            cin >> closing;
        }
        if (HourstoMinutes(closing) <= HourstoMinutes(opening))
            cout << "ERROR\nCLOSING TIME SHOULD BE AFTER OPENING TIME\nPLEASE RE-ENTER THEM\n";
        saveToFile(opening, closing);
    } while (HourstoMinutes(closing) <= HourstoMinutes(opening));
}

void DisplayWorkingHours()
{
    cout << "=========================================\nCurrent Working Hours Configuration:\n=========================================\n";
    ifstream file("workinghours.txt");
    string header, opening, closing;
    getline(file, header);
    getline(file, opening);
    getline(file, closing);
    cout << "Opening Time : " << opening << "\nClosing Time : " << closing << "\nTotal Working Minutes : " << HourstoMinutes(closing) - HourstoMinutes(opening) << "\n";
    file.close();
}

void saveToFile(const vector<string> &names, const vector<int> &durations)
{
    ofstream file("transactions.txt");
    file << "Transactions_Data\n";
    for (size_t i = 0; i < names.size(); ++i)
    {
        file << names[i] << "\n"
             << durations[i] << "\n";
    }
    file.close();
}

bool alreadyExists(const vector<string> &names, const string &name)
{
    return find(names.begin(), names.end(), name) != names.end();
}

string getValidTransactionName(const vector<string> &existingNames)
{
    string name;
    while (true)
    {
        cout << "Enter transaction name (or 'done' to finish): ";
        if (!getline(cin, name) || name == "done")
            return "done";
        if (name.empty())
        {
            cout << "ERROR: Name cannot be empty.\n";
            continue;
        }
        if (alreadyExists(existingNames, name))
        {
            cout << "ERROR: '" << name << "' already exists.\n";
            continue;
        }
        return name;
    }
}

int getValidTransactionDuration()
{
    int duration;
    cout << "Enter average duration in minutes: ";
    while (!(cin >> duration) || duration <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "ERROR: Please enter a valid positive integer: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return duration;
}

void defineTransactionTypes()
{
    vector<string> names;
    vector<int> durations;
    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while ((name = getValidTransactionName(names)) != "done")
    {
        names.push_back(name);
        durations.push_back(getValidTransactionDuration());
    }
    saveToFile(names, durations);
    cout << "-------------------------------\nTransactions Changed successfully!\n";
}

void addTransaction()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> names;
    vector<int> durations;
    while (true)
    {
        string name = getValidTransactionName(names);
        if (name == "done")
            break;
        names.push_back(name);
        durations.push_back(getValidTransactionDuration());
    }
    ofstream file("transactions.txt", ios::app);
    for (size_t i = 0; i < names.size(); ++i)
    {
        file << names[i] << "\n"
             << durations[i] << "\n";
    }
    file.close();
    cout << "-------------------------------\nTransactions Added successfully!\n";
}

void DisplayTransactions()
{
    cout << "=========================================\nCurrent Transactions Configuration:\n=========================================\n";
    ifstream file("transactions.txt");
    string header, name;
    int duration;
    getline(file, header);
    cout << left << setw(30) << "Transaction" << "Duration\n----------------------------------------------\n";
    while (getline(file, name) && file >> duration)
    {
        cout << left << setw(30) << name << duration << " mins\n";
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    file.close();
}

void setYearlyCustomerTarget()
{
    int target;
    while (true)
    {
        cout << "Enter target number of customers per year: ";
        if (!(cin >> target) || target < 30000)
        {
            cout << "Error: Value must be > 30,000\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cout << "------------------------------------------------------------------------\nTarget set successfully! (~" << target / 360 << " customers/day)\n";
            break;
        }
    }
    ofstream file("yearlytarget.txt");
    file << target << "\n"
         << target / 360 << "\n";
    file.close();
}

void DisplayYearlyCustomerTarget()
{
    cout << "=========================================\nCurrent Yearly Customer Target:\n=========================================\n";
    ifstream file("yearlytarget.txt");
    int target, avg;
    while (file >> target >> avg)
        cout << "Yearly Customer Target: " << target << "\nAverage Customers per Day: " << avg << "\n";
    file.close();
}

void viewCurrentConfiguration()
{
    cout << "=========================================\nCurrent System Configuration:\n=========================================\n";
    DisplayTellers();
    DisplayWorkingHours();
    DisplayTransactions();
    DisplayYearlyCustomerTarget();
}