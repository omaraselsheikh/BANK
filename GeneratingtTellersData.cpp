#include "includes.h"
#include "readdata.h"

//----Transaction-------------------------------------------------------------------

Transaction getTransactionAt(const vector<Transaction> &list, int index)
{
    if (index >= list.size())
        index = index - list.size();
    return list[index];
}

//----Teller-------------------------------------------------------------------

int numberoftellers(vector<Teller> alltellers)
{
    int i;
    cout << "========================================" << endl;
    cout << "1. Sunday\n2. Monday\n3. Tuesday\n4. Wednesday\n5. Thursday\n6. Friday\n7. Saturday\n";
    cout << "========================================" << endl;
    cout << "Enter the Day You want to Simulate: ";

    cin >> i;
    while (i < 1 || i > 7)
    {
        cout << "Out of Range, Please Re-Enter your choice: ";
        cin >> i;
    }
    return alltellers[i - 1].numtellers;
}

//----Final Data-------------------------------------------------------------------
struct TellerData
{
    string tellerID;
    string assignedTransactionType;
    int assignedTransactionDuration;
};

void generatingtellers()
{
    TellerData td;
    vector<TellerData> alltellers;
    int x = numberoftellers(readingalltellers());
    vector<string> IDs = getIDs(x);
    vector<Transaction> transactionPool = readtransaction();

    ofstream file("tellersdata.txt", ios::trunc);
    file << left << setw(40) << "Teller Id" << left << setw(40) << "Transaction assigned type" << "Transaction assigned duration" << endl;
    file << "========================================================================================================================" << endl;

    for (int i = 0; i < x; i++)
    {
        td.tellerID = IDs[i];
        Transaction current = getTransactionAt(transactionPool, i);
        td.assignedTransactionType = current.type;
        td.assignedTransactionDuration = current.duration;
        alltellers.push_back(td);
        file << left << setw(40) << td.tellerID << left << setw(40) << td.assignedTransactionType << td.assignedTransactionDuration << endl;
    }

    file.close();
}
