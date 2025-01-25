
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

enum enAtmMenueOptions { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, Logout = 5 };

const string ClientsFileName = "Clients.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

vector <sClient> LoadCleintsDataFromFile(string FileName);
void ShowQuickWithdrawScreen();
void ShowNormalWithdrawScreen();
void ShowAtmMainMenue();
void Login();

sClient CurrentClient;

vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

bool FindClientByAccountNumberAndPincode(string AccountNumber, string Pincode, sClient& Client)
{

    for (sClient C : vClients)
    {

        if (C.AccountNumber == AccountNumber && C.PinCode == Pincode)
        {
            Client = C;
            return true;
        }

    }
    return false;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}

void AddDataLineToFile(string FileName, string  stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open())
    {

        MyFile << stDataLine << endl;

        MyFile.close();
    }

}

void GoBackToAtmMainMenue()
{
    cout << "\n\nPress any key to go back to Atm Main Menue...";
    system("pause>0");
    ShowAtmMainMenue();

}

short ReadAtmMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

short ReadQuickWithdrawOption()
{
    cout << "Choose what do you want to do? [1 to 8]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void WithdrawAmountByAccountNumberAndAmount(string AccountNumber, short Amount)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance -= Amount;

            //Refrese the amount in the file.
            SaveCleintsDataToFile(ClientsFileName, vClients);
        }

    }
}

void DepositAmountByAccountNumberAndAmount(string AccountNumber, short Amount)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.AccountBalance += Amount;

            //Refrese the amount in the file.
            SaveCleintsDataToFile(ClientsFileName, vClients);
        }

    }
}

void PerformQuickWithdrawTransaction(short QuickOption)
{
    short QuickAmounts[10] = { 0,20,50,100,200,400,600,800,1000 };

    if (QuickOption == 9)
    {
        ShowAtmMainMenue();
    }

    if (QuickAmounts[QuickOption] > CurrentClient.AccountBalance)
    {
        cout << "The amount excees your balance, make another choice.\n";
        cout << "Press AnyKey to continue...";
        system("pause>0");

        ShowQuickWithdrawScreen();

    }

    char Answer = ' ';

    cout << "Are you sure you want perform this transaction? y/n ?";
    cin >> Answer;

    if (toupper(Answer) != 'Y')
    {
        GoBackToAtmMainMenue();
    }

    CurrentClient.AccountBalance -= QuickAmounts[QuickOption];

    // this to refresh the anmount in the file.
    WithdrawAmountByAccountNumberAndAmount(CurrentClient.AccountNumber, QuickAmounts[QuickOption]);

    cout << "Done Successfully. New balance is: " << CurrentClient.AccountBalance << endl;


}

void ShowQuickWithdrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] 20 \t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";

    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;

    PerformQuickWithdrawTransaction(ReadQuickWithdrawOption());
}

void ShowCheckBalanceScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tCheck Balance Screen";
    cout << "\n-----------------------------------\n";

    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
}

void ShowNormalWithdrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw Screen\n";
    cout << "===========================================\n";


    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;


    int Amount = 0;
    do {
        cout << "Enter an amount multiple of 5's ?";
        cin >> Amount;
    } while (Amount % 5 != 0);


    if (Amount > CurrentClient.AccountBalance)
    {
        cout << "The amount excees your balance, make another choice.\n";
        cout << "Press AnyKey to continue...";
        system("pause>0");
        ShowNormalWithdrawScreen();
    }

    char Answer = ' ';

    cout << "\n\nAre you sure you want perform this transaction? y/n ?";
    cin >> Answer;

    if (toupper(Answer) != 'Y')
    {
        GoBackToAtmMainMenue();
    }

    CurrentClient.AccountBalance -= Amount;

    // this to refresh the anmount in the file.
    WithdrawAmountByAccountNumberAndAmount(CurrentClient.AccountNumber, Amount);

    cout << "\n\nDone Successfully. New balance is: " << CurrentClient.AccountBalance << endl;


}

void ShowDepositScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tDeposit Screen\n";
    cout << "===========================================\n";

    int Amount = 0;

    do
    {
        cout << "Enter a positive Deposit Amount ?";
        cin >> Amount;

    } while (Amount < 1);

    char Answer = ' ';

    cout << "\n\nAre you sure you want perform this transaction? y/n ?";
    cin >> Answer;

    if (toupper(Answer) != 'Y')
    {
        GoBackToAtmMainMenue();
    }

    CurrentClient.AccountBalance += Amount;

    // this to refresh the anmount in the file.
    DepositAmountByAccountNumberAndAmount(CurrentClient.AccountNumber, Amount);

    cout << "\n\nDone Successfully. New balance is: " << CurrentClient.AccountBalance << endl;

}

void PerfromAtmMainMenueOption(enAtmMenueOptions AtmMenueOption)
{
    switch (AtmMenueOption)
    {
    case enAtmMenueOptions::eQuickWithdraw:

        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToAtmMainMenue();
        break;

    case enAtmMenueOptions::eNormalWithdraw:

        system("cls");
        ShowNormalWithdrawScreen();
        GoBackToAtmMainMenue();
        break;

    case enAtmMenueOptions::eDeposit:

        system("cls");
        ShowDepositScreen();
        GoBackToAtmMainMenue();
        break;

    case enAtmMenueOptions::eCheckBalance:

        system("cls");
        ShowCheckBalanceScreen();
        GoBackToAtmMainMenue();
        break;

    case enAtmMenueOptions::Logout:

        Login();
        break;
    }

}

void ShowAtmMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";


    PerfromAtmMainMenueOption((enAtmMenueOptions)ReadAtmMainMenueOption());
}

bool  LoadClientInfo(string AccountNumber, string Pincode)
{

    if (FindClientByAccountNumberAndPincode(AccountNumber, Pincode, CurrentClient))
        return true;
    else
        return false;

}

void Login()
{
    bool LoginFaild = false;

    string AcountNumber, Pincode;
    do
    {
        system("cls");

        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";

        if (LoginFaild)
        {
            cout << "Invlaid AccountNumber/Pincode!\n";
        }

        cout << "Enter AccountNumber? ";
        cin >> AcountNumber;

        cout << "Enter Pincode? ";
        cin >> Pincode;

        LoginFaild = !LoadClientInfo(AcountNumber, Pincode);

    } while (LoginFaild);

    ShowAtmMainMenue();

}

int main()

{
    Login();

    system("pause>0");
    return 0;
}