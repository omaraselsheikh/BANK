#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include "SystemConfig.cpp"

using namespace std;

// Main function to run the program
int main()
{
    MAIN m;
    m.title();
    char cmain;

    do
    {
        m.displayMainMenu();

        cout << "Enter your choice: ";
        cin >> cmain;

        switch (cmain)
        {
        case '1':
        {
            // Code to display system configuration menu and handle user choices
            m.displaySystemConfigMenu();

            char ch1;
            cout << "Enter your choice: ";
            cin >> ch1;

            switch (ch1)
            {
            case '1':
            {
                // Code to set number of tellers and save this configuration
                NumberOfTellers tellers;

                cout << "1. Edit Number of Tellers" << endl
                     << "2. View Number of Tellers" << endl;
                cout << "Enter your choice: ";
                char tellerChoice;
                cin >> tellerChoice;

                // Code to set or view number of tellers based on user choice
                if (tellerChoice == '1')
                {
                    tellers.numberofTellers();
                }
                else if (tellerChoice == '2')
                {
                    tellers.DisplayTellers();
                }
                else
                {
                    cout << "Invalid choice. Returning to System Configuration menu." << endl;
                }
                break;
            }

            case '2':
            {
                WorkingHours Hours;

                cout << "1. Edit Number of Working Hours" << endl
                     << "2. View Number of Working Hours" << endl;
                cout << "Enter your choice: ";
                char hoursChoice;
                cin >> hoursChoice;

                // Code to set or view number of working hours based on user choice
                if (hoursChoice == '1')
                {
                    Hours.setWorkingHours();
                }
                else if (hoursChoice == '2')
                {
                    Hours.DisplayWorkingHours();
                }
                else
                {
                    cout << "Invalid choice. Returning to System Configuration menu." << endl;
                }
                break;
            }

            case '3':
            { // Code for defining transaction types
                Transactions transactions;

                cout << "1. Change Transactions" << endl;
                cout << "2. Add Transactions" << endl;
                cout << "3. View Transactions" << endl;
                cout << "Enter your choice: ";
                char transChoice;
                cin >> transChoice;

                // Code to set or view transaction types based on user choice
                if (transChoice == '1')
                {
                    transactions.defineTransactionTypes();
                }
                else if (transChoice == '2')
                {
                    transactions.addTransaction();
                }
                else if (transChoice == '3')
                {
                    transactions.DisplayTransactions();
                }
                else
                {
                    cout << "Invalid choice. Returning to System Configuration menu." << endl;
                }
                break;
            }

            case '4':
            { // Code for setting yearly customer target
                YearlyCustomerTarget target;
                cout << "1. Edit Yearly Customer Target" << endl;
                cout << "2. View Yearly Customer Target" << endl;
                cout << "Enter your choice: ";
                char targetChoice;
                cin >> targetChoice;
                if (targetChoice == '1')
                {
                    target.setYearlyCustomerTarget();
                }
                else if (targetChoice == '2')
                {
                    target.DisplayYearlyCustomerTarget();
                }
                else
                {
                    cout << "Invalid choice. Returning to System Configuration menu." << endl;
                }
                break;
            }

            case '5':
            {
                viewCurrentConfiguration();
                break;
            }
            case '6':
            {
                break;
            }
            default:
            {
                cout << "Invalid choice. Returning to main menu." << endl;
                break;
            }
            }
            break;
        }

        case '2':
            cout << "Run Simulation selected." << endl;
            break;
        case '3':
            cout << "View Reports selected." << endl;
            // Code to view reports
            break;
        case '4':
            cout << "View Statistics selected." << endl;
            // Code to view statistics
            break;
        default:
            if (cmain != '5')
            {
                cout << "Invalid choice. Please try again." << endl;
            }
            break;
        }
    } while (cmain != '5');
    return 0;
}

// Pretty Code :)