#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include "MyBank.h"
using namespace std;
using namespace Bankfuns;


enum eATMOp {QuickWithdraw = 1, NormalWithdraw = 2, ATMDeposit = 3 , CheckBalance = 4, ATMLogout = 5};

sClient CurentClient;

sClient ReadClientTwoInfo()
{
    sClient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    return Client;
}

bool FindClientBYAccountNameAndPinCode(sClient &FoundClient, vector <sClient> veClients)
{

    for (sClient& Client : veClients)
    {
        if (Client.AccountNumber == FoundClient.AccountNumber && Client.PinCode == FoundClient.PinCode)
        {
            FoundClient = Client;
            return true;
        }

    }
    return false;
}

void ShowScreenATM(eATMOp ATMOp)
{
    system("cls");
    cout << "==================================================\n";
    cout << "\t";
    switch (ATMOp)
    {
    case QuickWithdraw:
        cout << "Quick Wthdraw";
        break;
    case NormalWithdraw:
        cout << "Normal Withdraw";
        break;
    case ATMDeposit:
        cout << "Deposit";
        break;
    case CheckBalance:
        cout << "Check Balance";
        break;
    case ATMLogout:
        cout << "Logout";
        break;
    default:
        break;
    }
    cout << " Screen\n";
    cout << "==================================================\n";

}

void ShowATMMainManue()
{
    system("cls");
    cout << "==================================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "==================================================\n";
    cout << "\t" << "[1] Quick withdraw.\n";
    cout << "\t" << "[2] Normal Withdraw.\n";
    cout << "\t" << "[3] Deposit.\n";
    cout << "\t" << "[4] Check Balance.\n";
    cout << "\t" << "[5] Logout.\n";
    cout << "==================================================\n";

}

void QuickWithdrawF()
{
    short Chois;
    char CChois;
    short arr[] = { 20, 50, 100, 200, 400, 600, 800, 1000 };
    for (short i = 0; i < 7; )
    {
        cout << "\t" << "[" << i << "]" << arr[i++];
        cout << "\t" << "[" << i << "]" << arr[i++];
        cout << endl;
    }
    cout << "\t" << "[9] Exit\n";
    cout << "==================================================\n";
    cout << "Your Balance is " << CurentClient.AccountBalance << endl;
    cout << "Choose what to withdraw from [1] to [8] ?";
    cin >> Chois;
    while (Chois < 0 || Chois > 8 )
    {
        cout << "Invalid Number Please enter another Number?";
        cin >> Chois;
    }

    while (CurentClient.AccountBalance < arr[Chois])
    {
        cout << "The Amount exceeds your balance, make another choice.\n";
        system("Pause");
        system("cls");
        ShowScreenATM(QuickWithdraw);
        for (short i = 0; i < 7; )
        {
            cout << "\t" << "[" << i  << "]" << arr[i++];
            cout << "\t" << "[" << i  << "]" << arr[i++];
            cout << endl;
        }
        cout << "\t" << "[9] Exit\n";
        cout << "==================================================\n";
        cout << "Your Balance is " << CurentClient.AccountBalance << endl;
        cout << "Choose what to withdraw from [1] to [8] ?";
        cin >> Chois;
       
    }

    if (Chois == 9)
    {
        
        return;
    }
        
    cout << "\nAre you sure you want perform this transaction? y/n?";
    cin >> CChois;
    if (toupper(CChois) == 'Y')
    {
        CurentClient.AccountBalance -= arr[Chois-1];
        cout << "Done Secsesfully, New balance is: " << CurentClient.AccountBalance << "\n";
    }
    
}

void CheckBalanceF()
{
    cout << "Your Balance is " << CurentClient.AccountBalance << "\n\n";

}


void NormalWithdrawF()
{
    int Num = 1;
    char C;
    while(Num % 5 != 0)
    {
        cout << "Enter an amount multiplae of 5's ?";
        cin >> Num;
    }

  
    while (CurentClient.AccountBalance < Num)
    {
        cout << "The Amount exceeds your balance, make another choice.\n";
        system("Pause");
        system("cls");
        ShowScreenATM(NormalWithdraw);
        while (Num % 5 != 0 || CurentClient.AccountBalance < Num)
        {
            cout << "Enter an amount multiplae of 5's ?";
            cin >> Num;
        }
    }
    

    cout << "Are You sure you want perform this transaction? y/n?";
    cin >> C;
    if (toupper(C) == 'Y')
    {
        CurentClient.AccountBalance -= Num;
        cout << "Done Secsesfully, New balance is: " << CurentClient.AccountBalance << "\n";
    }
   

}

void ATMDepositF()
{
    int Num = -1;
    char C;

   
    while (Num < 1)
    {
        cout << "Enter a positive Deposit amount? ";
        cin >> Num;
    }
    

    cout << "Are You sure you want perform this transaction? y/n?";
    cin >> C;
    if (toupper(C) == 'Y')
    {
        CurentClient.AccountBalance += Num;
        cout << "Done Secsesfully, New balance is: " << CurentClient.AccountBalance << "\n";
    }

}

void ATMSystem(vector <sClient> veClient)
{
    short Choise;
    eATMOp ATMOp;
    do 
    {
        system("cls");
        ShowATMMainManue();
        cout << "Choose what do you want to do? [1 to 5]?";
        cin >> Choise;
        ATMOp = (eATMOp)Choise;
        switch (ATMOp)
        {
        case QuickWithdraw:
            ShowScreenATM(ATMOp);
            QuickWithdrawF();
            break;
        case NormalWithdraw:
            ShowScreenATM(ATMOp);
            NormalWithdrawF();
            break;
        case ATMDeposit:
            ShowScreenATM(ATMOp);
            ATMDepositF();
            break;
        case CheckBalance:
            ShowScreenATM(ATMOp);
            CheckBalanceF();
            break;
        case ATMLogout:
            break;
        default:
            break;
        }
        system("Pause");
        UpDataClientByAccountNumber(veClient, CurentClient);
        SaveCleintsDataToFile(ClientsFileName, veClient);
    } while (ATMOp != ATMLogout);
    

}

void Login()
{
        do
        {
            system("cls");
            LoginScreen();
            CurentClient = ReadClientTwoInfo();
            vector <sClient> veClient = LoadCleintsDataFromFile(ClientsFileName);
            while (!FindClientBYAccountNameAndPinCode(CurentClient, veClient))
            {
                system("cls");
                LoginScreen();
                cout << "Invalid Account Number/PinCode\n";
                CurentClient = ReadClientTwoInfo();
            }
            ATMSystem(veClient);

        } while (true);

}

int main()
{
    Login();
	return 0;
}