#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

const string FileName = "Client.txt";

void ShowMainMenu();

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    bool MarkDelete = false;
    double AccountBalance;
};

enum enMainMenuOptions
{
    eShowClients = 1,
    eAddClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eExitClient = 6
};

short ReadMainMenuOption()
{
    short Option;
    cout << "Choose what do you want to do? [1 to 6]? ";
    cin >> Option;
    return Option;
}

vector<string> SplitString(string line, string separator)
{
    vector<string> vStrClient;
    string stWord = "";
    short pos = 0;

    while ((pos = line.find(separator)) != std::string::npos)
    {
        stWord = line.substr(0, pos);

        if (stWord != "")
        {
            vStrClient.push_back(stWord);
        }

        line.erase(0, pos + separator.length());
    }

    if (line != "")
    {
        vStrClient.push_back(line);
    }

    return vStrClient;
}

stClient ConvertLineToRecored(string line, string separator = "#//#")
{
    stClient Client;
    vector<string> vStrClient = SplitString(line, separator);

    Client.AccountNumber = vStrClient[0];
    Client.PinCode = vStrClient[1];
    Client.Name = vStrClient[2];
    Client.Phone = vStrClient[3];
    Client.AccountBalance = stod(vStrClient[4]);

    return Client;
}

vector<stClient> LoadClientsFromFile()
{
    fstream MyFile;
    vector<stClient> vClients;

    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {

        string line;
        stClient Client;
        while (getline(MyFile, line))
        {
            Client = ConvertLineToRecored(line);
            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

void PrintClientLine(stClient Client)
{
    cout << " | " << setw(15) << left << Client.AccountNumber;
    cout << " | " << setw(12) << left << Client.PinCode;
    cout << " | " << setw(35) << left << Client.Name;
    cout << " | " << setw(15) << left << Client.Phone;
    cout << " | " << setw(15) << left << to_string(Client.AccountBalance);
}

void ShowClientsScreen()
{
    vector<stClient> vClients = LoadClientsFromFile();
    cout << "\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
    cout << "____________________________________________________________";
    cout << "_____________________________________________\n\n";
    cout << " | " << setw(15) << left << "Account Number";
    cout << " | " << setw(12) << left << "Pin Code";
    cout << " | " << setw(35) << left << "Client Name";
    cout << " | " << setw(15) << left << "Phone";
    cout << " | " << setw(15) << left << "Balance";
    cout << "\n____________________________________________________________";
    cout << "_____________________________________________\n\n";

    if (vClients.size() == 0)
        cout << "No Clients In The system!\n";
    else
        for (stClient Client : vClients)
        {
            PrintClientLine(Client);
            cout << endl;
        }
    cout << "____________________________________________________________";
    cout << "_____________________________________________\n\n";
}

void GoToMainMenuScreen()
{
    cout << "\nPress any key to go back to Main Menu...\n";
    system("pause>0");
    ShowMainMenu();
}

bool ClientIsExistByAccountNumber(string AccountNumber, vector<stClient> vClients)
{

    for (stClient Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            return true;
        }
    }

    return false;
}

string ConverRecordToString(stClient Client, string separator = "#//#")
{
    string line;
    line += Client.AccountNumber + separator;
    line += Client.PinCode + separator;
    line += Client.Name + separator;
    line += Client.Phone + separator;
    line += to_string(Client.AccountBalance);

    return line;
}

void SaveClientsInFile(vector<stClient> vClients)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {

        for (stClient Client : vClients)
        {
            if (Client.MarkDelete == false)
            {

                string line = ConverRecordToString(Client);
                MyFile << line << endl;
            }
        }

        MyFile.close();
    }
}

void AddClientToFile(string line)
{

    fstream MyFile;

    MyFile.open(FileName, ios::app);
    if (MyFile.is_open())
    {
        MyFile << line << endl;

        MyFile.close();
    }
}

stClient ReadNewClient()
{
    stClient Client;
    vector<stClient> vClients = LoadClientsFromFile();

    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.AccountNumber);

    while (ClientIsExistByAccountNumber(Client.AccountNumber, vClients))
    {
        cout << "Client with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter Pin Code? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

void AddNewClient()
{
    stClient Client = ReadNewClient();

    AddClientToFile(ConverRecordToString(Client));
}

void AddNewClients()
{
    char Answer = 'n';

    do
    {
        cout << "Adding New Client: \n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more Clients? Y/N? \n";
        cin >> Answer;
    } while (Answer == 'Y' || Answer == 'y');
}

void ShowAddClientScreen()
{
    cout << "----------------------------------------------------\n";
    cout << "\t\tAdd New Clients Screen\n";
    cout << "----------------------------------------------------\n";

    AddNewClients();
}

string ReadAccountNumber()
{
    string AccountNumber;
    cout << "Please enter AccountNumber? ";
    getline(cin >> ws, AccountNumber);
    return AccountNumber;
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClient> vClients, stClient &Client)
{

    for (stClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

void PrintClientCard(stClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "Account Number          : " << Client.AccountNumber << endl;
    cout << "Pin Code                : " << Client.PinCode << endl;
    cout << "Name                    : " << Client.Name << endl;
    cout << "Phone                   : " << Client.Phone << endl;
    cout << "Account Balance         : " << to_string(Client.AccountBalance) << endl;
}

void MarkClientForDelete(vector<stClient> &vClients, string AccountNumber)
{

    for (stClient &Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            Client.MarkDelete = true;
        }
    }
}

void DeleteClient(string AccountNumber, vector<stClient> &vClients)
{
    char Answer = 'n';
    stClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        char SureDelete = 'n';
        cout << "\nAre you sure you want delete this client? Y/N ? ";
        cin >> SureDelete;

        if (SureDelete == 'y' || SureDelete == 'Y')
        {

            MarkClientForDelete(vClients, AccountNumber);

            SaveClientsInFile(vClients);

            vClients = LoadClientsFromFile();

            cout << "\nClient Deleted Successfully.\n\n";
        }
    }
    else
    {
        cout << "Client with Account Number (" << AccountNumber << ") is Not Found!\n";
    }
}

void ShowDeleteClientScreen()
{
    cout << "----------------------------------------------------\n";
    cout << "\t\tDelete Client Screen\n";
    cout << "----------------------------------------------------\n";

    vector<stClient> vClients = LoadClientsFromFile();
    string AccountNumber = ReadAccountNumber();
    DeleteClient(AccountNumber, vClients);
}

stClient ChangeClient(string AccountNumber)
{
    stClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin >> ws, Client.Name);

    cout << "Enter Phone? ";
    getline(cin >> ws, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

void UpdateClient(string AccountNumber, vector<stClient> &vClients)
{

    char Answer = 'n';
    stClient Client;

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);

        cout << "Are you sure you want update this client? Y/N ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {

            for (stClient &c : vClients)
            {

                if (c.AccountNumber == AccountNumber)
                {
                    c = ChangeClient(AccountNumber);
                    break;
                }
            }

            SaveClientsInFile(vClients);

            vClients = LoadClientsFromFile();

            cout << "\nClient Updated Successfully.\n\n";
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!\n\n";
    }
}

void ShowUpdateClientScreen()
{
    cout << "----------------------------------------------------\n";
    cout << "\t\tUpdate Client Screen\n";
    cout << "----------------------------------------------------\n";

    vector<stClient> vClients = LoadClientsFromFile();
    string AccountNumber = ReadAccountNumber();
    UpdateClient(AccountNumber, vClients);
}

void FindClient(string AccountNumber, vector<stClient> vClients)
{

    bool FoundClient = false;

    for (stClient Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
        {
            PrintClientCard(Client);
            FoundClient = true;
            break;
        }
    }

    if (!FoundClient)
        cout << "\nClient with Account Number [" << AccountNumber << "] is Not Found!\n";
}

void ShowFindClientScreen()
{

    cout << "----------------------------------------------------\n";
    cout << "\t\tFind Client Screen\n";
    cout << "----------------------------------------------------\n";

    vector<stClient> vClients = LoadClientsFromFile();
    string AccountNumber = ReadAccountNumber();
    FindClient(AccountNumber, vClients);
}

void ShowEndProgramScreen()
{
    cout << "----------------------------------------------------\n";
    cout << "\t\tProgram Ends :-)\n";
    cout << "----------------------------------------------------\n";
}

void PerfoemMainMenuOption(enMainMenuOptions MainMenuOption)
{
    switch (MainMenuOption)
    {
    case enMainMenuOptions::eShowClients:
        system("cls");
        ShowClientsScreen();
        GoToMainMenuScreen();
        break;
    case enMainMenuOptions::eAddClient:
        system("cls");
        ShowAddClientScreen();
        GoToMainMenuScreen();
        break;
    case enMainMenuOptions::eDeleteClient:
        system("cls");
        ShowDeleteClientScreen();
        GoToMainMenuScreen();
        break;
    case enMainMenuOptions::eUpdateClient:
        system("cls");
        ShowUpdateClientScreen();
        GoToMainMenuScreen();
        break;
    case enMainMenuOptions::eFindClient:
        system("cls");
        ShowFindClientScreen();
        GoToMainMenuScreen();
        break;
    case enMainMenuOptions::eExitClient:
        system("cls");
        ShowEndProgramScreen();
        break;
    }
}

void ShowMainMenu()
{

    cout << "================================================================\n";
    cout << "\t\t\t Main Menu Screen\n";
    cout << "================================================================\n";
    cout << "\t\t [1] Show Client List.\n";
    cout << "\t\t [2] Add New Client.\n";
    cout << "\t\t [3] Delete Client.\n";
    cout << "\t\t [4] Update Client Info.\n";
    cout << "\t\t [5] Find Client.\n";
    cout << "\t\t [6] Exit.\n";
    cout << "================================================================\n";
    PerfoemMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
}

int main()
{

    ShowMainMenu();
}