#include <iostream>

// Include ONLY headers!
#include "readdata.h"
#include "GenerateCustomerTeller.h"
#include "SystemConfig.h"
#include "RunSimulation.h"

using namespace std;

void title()
{
    std::cout << "╔════════════════════════════════════════╗\n";
    std::cout << "║     BANK CUSTOMERS QUEUING SYSTEM      ║\n";
    std::cout << "╚════════════════════════════════════════╝\n";
}

void displayMainMenu()
{
    cout << "=========================================\n";
    cout << "Welcome! " << endl;
    cout << "=========================================\n";
    cout << "Please Select an Option:" << endl;
    cout << "=========================================\n";
    cout << "1. System Configuration" << endl;
    cout << "2. Run Simulation" << endl;
    cout << "3. View Reports" << endl;
    cout << "4. View Statistics" << endl;
    cout << "5. Exit" << endl;
    cout << "========================================" << endl;
}

int main()
{
    title();
    char cmain;

    do
    {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> cmain;

        switch (cmain)
        {
        case '1':
            displaySystemConfigMenu();
            char ch1;
            cout << "Enter your choice: ";
            cin >> ch1;

            switch (ch1)
            {
            case '1':
                cout << "1. Edit Number of Tellers\n2. View Number of Tellers\nEnter your choice: ";
                char tellerChoice;
                cin >> tellerChoice;
                if (tellerChoice == '1')
                    numberofTellers();
                else if (tellerChoice == '2')
                    DisplayTellers();
                else
                    cout << "Invalid choice.\n";
                break;
            case '2':
                cout << "1. Edit Number of Working Hours\n2. View Number of Working Hours\nEnter your choice: ";
                char hoursChoice;
                cin >> hoursChoice;
                if (hoursChoice == '1')
                    setWorkingHours();
                else if (hoursChoice == '2')
                    DisplayWorkingHours();
                else
                    cout << "Invalid choice.\n";
                break;
            case '3':
                cout << "1. Change Transactions\n2. Add Transactions\n3. View Transactions\nEnter your choice: ";
                char transChoice;
                cin >> transChoice;
                if (transChoice == '1')
                    defineTransactionTypes();
                else if (transChoice == '2')
                    addTransaction();
                else if (transChoice == '3')
                    DisplayTransactions();
                else
                    cout << "Invalid choice.\n";
                break;
            case '4':
                cout << "1. Edit Yearly Customer Target\n2. View Yearly Customer Target\nEnter your choice: ";
                char targetChoice;
                cin >> targetChoice;
                if (targetChoice == '1')
                    setYearlyCustomerTarget();
                else if (targetChoice == '2')
                    DisplayYearlyCustomerTarget();
                else
                    cout << "Invalid choice.\n";
                break;
            case '5':
                viewCurrentConfiguration();
                break;
            default:
                cout << "Invalid choice. Returning to main menu.\n";
                break;
            }
            break;

        case '2':
        {
            displayRunSimulationMenu();
            cout << "Enter your choice: ";
            char ch2;
            cin >> ch2;
            if (ch2 == '1')
            {
                int dayindex = getDaySimulation();
                simulateDay(dayindex);
                cout << "========================================\nDaily Simulation done Successfully\n";
            }
            break;
        }
        case '3':
            cout << "View Reports selected.\n";
            break;
        case '4':
            cout << "View Statistics selected.\n";
            break;
        case '5':
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (cmain != '5');

    return 0;
}