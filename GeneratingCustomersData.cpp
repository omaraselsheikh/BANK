#include "includes.h"
#include "readdata.h"

void displayRunSimulationMenu()
{
    cout << "========================================" << endl;
    cout << "Run Simulation selected." << endl;
    cout << "========================================" << endl;
    cout << "1. Run daily simulation" << endl;
    cout << "2. Run weekly simulation" << endl;
    cout << "3. Run full year simulation" << endl;
    cout << "4. Back to Main Menu" << endl;
    cout << "========================================" << endl;
}

int dailycustomernumber(int avg)
{
    static bool flag = true;

    if (flag)
        return (avg + rand() % 20);
    else
        return (avg - rand() % 20);

    flag = !flag;
}

YearlyCustomerTarget yct;
int totalcustomers = dailycustomernumber(yct.dailyavg);

string converttostring(int totalMinutes)

{
    int hour = totalMinutes / 60;
    int minutes = totalMinutes % 60;

    string hourStr = to_string(hour);
    string minStr = to_string(minutes);

    // Add leading zero to hour if needed
    if (hour < 10)
        hourStr = "0" + hourStr;

    // Add leading zero to minutes if needed
    if (minutes < 10)
        minStr = "0" + minStr;

    return hourStr + ":" + minStr;
}

vector<string> getArrivalTime()
{
    vector<string> arrivaltime;
    int numcustomer = totalcustomers;
    WorkingHours h = readingWorkingHours();
    int timeinterval = h.total / numcustomer;
    int arrivalhour = HourstoMinutes(h.opening) + rand() % timeinterval;
    string time = converttostring(arrivalhour);
    arrivaltime.push_back(time);
    for (int i = 1; i < numcustomer; i++)
    {
        int arrivalhours = arrivalhour + rand() % timeinterval;
        string time = converttostring(arrivalhour);
        arrivaltime.push_back(time);
        arrivalhour = arrivalhours;
    }
    return arrivaltime;
}

struct CustomerData
{
    string id;
    string arrivaltime;
    string transactionname;
};

void generatingcustomers()
{
    CustomerData customer;
    vector<CustomerData> allcustomers;
    vector<string> IDs = getIDs(totalcustomers);
    vector<Transaction> transactionPool = readtransaction();
    vector<string> arrivaltimepool = getArrivalTime();

    ofstream file("customerdata.txt", ios::trunc);
    file << left << setw(40) << "Customer Id" << left << setw(40) << "Arrival Time" << "Transaction type" << endl;
    file << "========================================================================================================================" << endl;
    file << "Total Customers= " << totalcustomers << endl;

    for (int i = 0; i < totalcustomers; i++)
    {
        customer.id = IDs[i];
        customer.arrivaltime = arrivaltimepool[i];

        int randomIndex = rand() % transactionPool.size();
        customer.transactionname = transactionPool[randomIndex].type;
        allcustomers.push_back(customer);

        file << left << setw(40) << customer.id << left << setw(40) << customer.arrivaltime << customer.transactionname << endl;
    }

    file.close();
}
