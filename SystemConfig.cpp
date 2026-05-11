#include "includes.h"

using namespace std;

void displaySystemConfigMenu()
{
    cout << "========================================" << endl;
    cout << "System Configuration selected." << endl;
    cout << "========================================" << endl;
    cout << "1. Number of Tellers" << endl;
    cout << "2. Working Hours" << endl;
    cout << "3. Transaction Types" << endl;
    cout << "4. Yearly Customer Target" << endl;
    cout << "5. View Current Configuration" << endl;
    cout << "6. Back to Main Menu" << endl;
    cout << "========================================" << endl;
}

//----Teller-------------------------------------------------------------------

void saveToFile(const string days[], const int numoftellers[], int size)
{

    ofstream file("tellers.txt");

    file << "Number_of_Tellers_Data" << endl;

    for (int i = 0; i < size; i++)
    {
        file << days[i] << "\n"
             << numoftellers[i] << endl;
    }

    file.close();
}

// Function to validate the number of tellers
bool isValidNumber(int num)
{
    return num >= 1 && num <= 10;
}

// Code to set number of tellers and save this configuration
void numberofTellers()
{
    string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
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

// Function to display the number of tellers from the saved configuration
void DisplayTellers()
{
    cout << "=========================================\n";
    cout << "Current Number of Tellers Configuration:\n";
    cout << "=========================================\n";

    ifstream file("tellers.txt");

    string days[7] = {};
    int numTellers[7] = {};
    string header;
    int i = 0;
    int totalTellers = 0;

    getline(file, header);

    while (i < 7 && getline(file, days[i]))
    {
        if (file >> numTellers[i])
        {
            totalTellers += numTellers[i];
            i++;
            file.ignore(); // Clear the newline after the number
        }
    }

    file.close();

    cout << left << setw(15) << "Day" << "Number of Tellers" << endl;
    cout << "-----------------------------------\n";
    for (int j = 0; j < i; j++) // Use 'i' to only print what was actually read
    {
        cout << left << setw(15) << days[j] << numTellers[j] << "\n";
    }
    cout << "-----------------------------------\n";
    cout << "Total Tellers: " << totalTellers << endl;
    ;
}

//----Working Hours-------------------------------------------------------------------

void saveToFile(string opening, string closing)
{

    ofstream file("workinghours.txt");

    file << "Working_hours_Data" << endl;

    file << opening << "\n"
         << closing;

    file.close();
}

int HourstoMinutes(string time)
{
    return ((time[0] - '0') * 10 + (time[1] - '0')) * 60 + (time[3] - '0') * 10 + (time[4] - '0');
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
            cout << "ERROR\n"
                 << "PLEASE RE-ENTER A VALID TIME\n";
            cin >> opening;
        }

        cout << "ENTER CLOSING TIME IN THIS FORMAT (HH:MM) 24_HR Format:\n";
        cin >> closing;

        while (!isValidTime(closing))
        {
            cout << "ERROR\n"
                 << "PLEASE RE-ENTER A VALID TIME\n";
            cin >> closing;
        }

        if (HourstoMinutes(closing) <= HourstoMinutes(opening))
            cout << "ERROR\nCLOSING TIME SHOULD BE AFTER OPENING TIME\nPLEASE RE-ENTER THEM\n";

        saveToFile(opening, closing);

    } while (HourstoMinutes(closing) <= HourstoMinutes(opening));
}

void DisplayWorkingHours()
{
    cout << "=========================================\n";
    cout << "Current Working Hours Configuration:\n";
    cout << "=========================================\n";

    ifstream file("workinghours.txt");

    string header, opening, closing;

    getline(file, header);
    getline(file, opening);
    getline(file, closing);

    cout << "Opening Time : " << opening << endl;
    cout << "Closing Time : " << closing << endl;
    cout << "Total Working Minutes : " << HourstoMinutes(closing) - HourstoMinutes(opening) << endl;

    file.close();
}

//----Transaction-------------------------------------------------------------------

void saveToFile(const vector<string> &names, const vector<int> &durations)
{

    ofstream file("transactions.txt");

    file << "Transactions_Data" << endl;

    for (int i = 0; i < names.size(); ++i)
    {
        file << names[i] << "\n"
             << durations[i] << endl;
    }

    file.close();
}

// Bool to check for duplicates
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

        // Use getline to allow names with spaces
        if (!getline(cin, name) || name == "done")
        {
            return "done";
        }

        if (name.empty())
        {
            cout << "ERROR: Name cannot be empty.\n";
            continue;
        }

        if (alreadyExists(existingNames, name))
        {
            cout << "ERROR: '" << name << "' already exists. Enter a unique name: \n";
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
        cin.clear();                                         // Clear error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
        cout << "ERROR: Please enter a valid positive integer for duration: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clean buffer for next getline
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
        int duration = getValidTransactionDuration();
        names.push_back(name);
        durations.push_back(duration);
    }

    saveToFile(names, durations);
    cout << "-------------------------------\n";
    cout << "Transactions Changed successfully!" << endl;
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

        int duration = getValidTransactionDuration();

        names.push_back(name);
        durations.push_back(duration);
    }

    ofstream file("transactions.txt", ios::app);

    for (int i = 0; i < names.size(); ++i)
    {
        file << names[i] << "\n"
             << durations[i] << endl;
    }

    file.close();
    cout << "-------------------------------\n";
    cout << "Transactions Added successfully!" << endl;
}

void DisplayTransactions()
{
    cout << "=========================================\n";
    cout << "Current Transactions Configuration:\n";
    cout << "=========================================\n";
    ifstream file("transactions.txt");
    string header, name;
    int duration;

    getline(file, header); // If file doesn't exist, this fails silently

    cout << left << setw(30) << "Transaction" << "Duration" << endl;
    cout << "----------------------------------------------\n";

    while (getline(file, name) && file >> duration)
    {
        cout << left << setw(30) << name << duration << " mins" << endl;

        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    file.close();
}

//----Yearly Customer Target-------------------------------------------------------------------

void setYearlyCustomerTarget()
{
    int target;
    while (true)
    {
        cout << "Enter target number of customers per year: ";
        if (!(cin >> target) || target < 30000)
        {
            cout << "Error: Value must be an integer greater than 30,000" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            int avgPerDay = target / 360;
            cout << "------------------------------------------------------------------------\n";
            cout << "Target set successfully! (Average ~" << avgPerDay << " customers/day)" << endl;
            break;
        }
    }

    ofstream file("yearlytarget.txt");
    file << target << endl;
    file << target / 360 << endl;
    file.close();
}

void DisplayYearlyCustomerTarget()
{

    cout << "=========================================\n";
    cout << "Current Yearly Customer Target Configuration:\n";
    cout << "=========================================\n";

    ifstream file("yearlytarget.txt");
    int target, avg;

    while (file >> target >> avg)
    {
        cout << "Yearly Customer Target: " << target << endl;
        cout << "Average Customers per Day: " << avg << endl;
    }

    file.close();
}

//----View Configuration-------------------------------------------------------------------

void viewCurrentConfiguration()
{
    cout << "=========================================\n";
    cout << "Current System Configuration:\n";
    cout << "=========================================\n";

    // Code to read and display current configuration from saved files
    DisplayTellers();
    DisplayWorkingHours();
    DisplayTransactions();
    DisplayYearlyCustomerTarget();
}
