#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

const string FileName = "Client.txt";

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkDelete = false;
};

void ShowMainMenu();
void StartBankProgramm();
void ShowClientList(string FileName);
void PrintClientsListCard(vector<stClient> vClients);

// enum enChoose
// {
//     Show = 1,
//     Add = 2,
//     Delete = 3,
//     Update = 4,
//     Find = 5,
//     Exit = 6
// };

vector<string> SplitString(string line, string separator)
{

    short pos = 0;
    string stWord = "";
    vector<string> vString;

    while ((pos = line.find(separator)) != std::string::npos)
    {
        stWord = line.substr(0, pos);

        if (stWord != "")
        {
            vString.push_back(stWord);
        }

        line.erase(0, pos + separator.length());
    }

    if (line != "")
    {
        vString.push_back(line);
    }

    return vString;
}

stClient ConvertStringToRecord(string line, string separator = "#//#")
{

    vector<string> vString = SplitString(line, separator);
    stClient Client;

    Client.AccountNumber = vString[0];
    Client.PinCode = vString[1];
    Client.Name = vString[2];
    Client.Phone = vString[3];
    Client.AccountBalance = stod(vString[4]);

    return Client;
}

vector<stClient> LoadClientsFromFile(string FileName)
{
    vector<stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string line;
        stClient Client;

        while (getline(MyFile, line))
        {
            Client = ConvertStringToRecord(line, "#//#");
            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

void PrintClientCard(stClient Client)
{

    cout << " | " << setw(18) << left << Client.AccountNumber;
    cout << " | " << setw(18) << left << Client.PinCode;
    cout << " | " << setw(35) << left << Client.Name;
    cout << " | " << setw(18) << left << Client.Phone;
    cout << " | " << setw(18) << left << Client.AccountBalance;
}

void PrintClientsListCard(vector<stClient> vClients)
{
    cout << "\t\t\t\t\t Client List (" << vClients.size() << ") Client(s).\n";
    cout << "__________________________________________________________";
    cout << "__________________________________________________________\n\n";
    cout << " | " << setw(18) << left << "Account Number";
    cout << " | " << setw(18) << left << "Pin Code";
    cout << " | " << setw(35) << left << "Client Name";
    cout << " | " << setw(18) << left << "Phone";
    cout << " | " << setw(18) << left << "Balance";
    cout << "\n__________________________________________________________";
    cout << "__________________________________________________________\n\n";

    for (stClient &c : vClients)
    {
        PrintClientCard(c);
        cout << endl;
    }

    cout << "__________________________________________________________";
    cout << "__________________________________________________________\n\n";

    cout << "Press any key to go back to Main Menue...\n";
    system("pause>0");
    ShowMainMenu();
}

void ShowClientList(string FileName)
{
    vector<stClient> vClients = LoadClientsFromFile(FileName);

    PrintClientsListCard(vClients);
}

bool CheckIfAccNumberExist(string AccNumber, vector<stClient> vClients)
{
    for (stClient &c : vClients)
    {
        if (c.AccountNumber == AccNumber)
        {
            cout << "Client with [" << AccNumber << "] already exists, Enter another Account Number? ";
            return false;
            break;
        }
    }
    return true;
}

stClient CreateNewClient(vector<stClient> vClients)
{
    stClient Client;

    cout << "---------------------------------------------\n";
    cout << "\t\t Add New Clients Screen\n";
    cout << "---------------------------------------------\n";
    cout << "Adding New Client\n";

    cout << "Enter Account Number? ";
    string AccNumber;
    bool isExist = false;
    do
    {
        getline(cin >> ws, AccNumber);
        isExist = CheckIfAccNumberExist(AccNumber, vClients);
    } while (!isExist);

    Client.AccountNumber = AccNumber;

    cout << "Enter Pin Code? ";
    getline(cin, Client.PinCode);

    cout << "Enter Client Name? ";
    getline(cin, Client.Name);

    cout << "Enter Client Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

string ConvertToString(stClient Client, string separator = "#//#")
{

    string strClient = "";
    strClient += Client.AccountNumber + separator;
    strClient += Client.PinCode + separator;
    strClient += Client.Name + separator;
    strClient += Client.Phone + separator;
    strClient += to_string(Client.AccountBalance);

    return strClient;
}

void RefreshClientsFile(vector<stClient> vClients, string FileName)
{

    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {

        string line;

        for (stClient &c : vClients)
        {
            line = ConvertToString(c, "#//#");
            MyFile << line << endl;
        }
        MyFile.close();
    }
}

void AddNewClient(string FileName)
{

    vector<stClient> vClients = LoadClientsFromFile(FileName);
    stClient Client = CreateNewClient(vClients);
    vClients.push_back(Client);

    RefreshClientsFile(vClients, FileName);

    string AddMore = "n";

    cout << "Client Added Successfully, do you want to add more clients? Y/N? ";
    cin >> AddMore;
    if (AddMore == "Y" || AddMore == "y")
    {
        AddNewClient(FileName);
    }

    cout << "Press any key to go back to Main Menue...\n";
    system("pause>0");
    ShowMainMenu();
}

string ReadAccountNumber()
{
    string AccNumber;
    cout << "Please enter AccountNumber? ";
    cin >> AccNumber;
    return AccNumber;
}

void PrintClientCardRows(stClient Client)
{
    cout << "\nThe following are the client details: \n";
    cout << "---------------------------------------------\n";
    cout << "Account Number: " << Client.AccountNumber << endl;
    cout << "Pin Code      : " << Client.PinCode << endl;
    cout << "Name          : " << Client.Name << endl;
    cout << "Phone         : " << Client.Phone << endl;
    cout << "Balance       : " << Client.AccountBalance << endl;
    cout << "---------------------------------------------";
}

void MarkClientAsDelete(string AccountNumber, vector<stClient> &vClients)
{

    for (stClient &c : vClients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            c.MarkDelete = true;
        }
    }
}

void DeleteClientFromFile(vector<stClient> vClients, string FileName)
{
    fstream MyFile;

    MyFile.open(FileName, ios::out);

    if (MyFile.is_open())
    {

        for (stClient &c : vClients)
        {
            if (c.MarkDelete == false)
            {
                string line = ConvertToString(c, "#//#");
                MyFile << line << endl;
            }
        }
        MyFile.close();
    }
}

void DeletClientFromFile(string AccountNumber, vector<stClient> vClients, string FileName)
{
    stClient Client;

    for (stClient &c : vClients)
    {
        if (AccountNumber == c.AccountNumber)
        {
            Client = c;
        }
    }

    PrintClientCardRows(Client);

    MarkClientAsDelete(AccountNumber, vClients);

    DeleteClientFromFile(vClients, FileName);

    cout << "\n\nClient Deleted Successfully.\n\n";
}

void DeleteClient(string FileName)
{

    cout << "---------------------------------------------\n";
    cout << "\t\t Delete Client Screen\n";
    cout << "---------------------------------------------\n";

    vector<stClient> vClients = LoadClientsFromFile(FileName);
    string AccNumber = ReadAccountNumber();

    bool isExist = false;
    for (stClient &c : vClients)
    {
        if (c.AccountNumber == AccNumber)
        {
            DeletClientFromFile(AccNumber, vClients, FileName);
            isExist = true;
        }
    }

    if (!isExist)
    {
        cout << "\nClient with AccountNumber (" << AccNumber << ") is Not Found!\n\n";
    }
    cout << "Press any key to go back to Main Menue...\n";
    system("pause>0");
    ShowMainMenu();
}

void UpdateClientFromFile(stClient CltStruct, vector<stClient> &vClients, string FileName)
{
    PrintClientCardRows(CltStruct);
    string SureUpdt = "n";
    cout << "\n\nAre you sure you want update this client? y/n ? \n\n";
    cin >> SureUpdt;
    stClient Client;

    if (SureUpdt == "Y" || SureUpdt == "y")
    {
        Client.AccountNumber = CltStruct.AccountNumber;

        cout << "Enter pinCode? ";
        getline(cin >> ws, Client.PinCode);

        cout << "Enter Name? ";
        getline(cin, Client.Name);

        cout << "Enter Phone? ";
        getline(cin, Client.Phone);

        cout << "Enter AccountBalance? ";
        cin >> Client.AccountBalance;

        for (stClient &c : vClients)
        {
            if (c.AccountNumber == CltStruct.AccountNumber)
            {
                c = Client;
            }
        }

        // Refresh File
        RefreshClientsFile(vClients, FileName);

        cout << "\nClient Updated Successfully.\n";
    }
    else
    {
        cout << "Press any key to go back to Main Menue...\n";
        system("pause>0");
        ShowMainMenu();
    }
}

void UpdateClient(string FileName)
{

    cout << "---------------------------------------------\n";
    cout << "\t\t Update Client Info Screen\n";
    cout << "---------------------------------------------\n";

    vector<stClient> vClients = LoadClientsFromFile(FileName);
    string AccountNumber = ReadAccountNumber();

    for (stClient &c : vClients)
    {
        if (c.AccountNumber == AccountNumber)
        {
            UpdateClientFromFile(c, vClients, FileName);
        }
    }

    cout << "Press any key to go back to Main Menue...\n";
    system("pause>0");
    ShowMainMenu();
}

void FindClient(string FileName)
{

    cout << "---------------------------------------------\n";
    cout << "\t\t Find Client Screen\n";
    cout << "---------------------------------------------\n";

    vector<stClient> vClients = LoadClientsFromFile(FileName);
    string AccNumber = ReadAccountNumber();

    bool isExist = false;
    for (stClient &c : vClients)
    {
        if (c.AccountNumber == AccNumber)
        {
            PrintClientCardRows(c);
            isExist = true;
        }
    }

    if (!isExist)
    {
        cout << "\nClient with AccountNumber (" << AccNumber << ") is Not Found!\n\n";
    }

    cout << "\n\nPress any key to go back to Main Menue...\n";
    system("pause>0");
    ShowMainMenu();
}

void EndProgram()
{
    cout << "---------------------------------------------\n";
    cout << "\t\t Program Ends :-)\n";
    cout << "---------------------------------------------\n";

    system("pause>0");
}

void StartBankProgramm()
{
    short UserChoose = 1;
    cout << "Choose what do you want to do? [1 to 6]? ";
    cin >> UserChoose;

    switch (UserChoose)
    {
    case 1:
        ShowClientList(FileName);
        break;
    case 2:
        AddNewClient(FileName);
        break;
    case 3:
        DeleteClient(FileName);
        break;
    case 4:
        UpdateClient(FileName);
        break;
    case 5:
        FindClient(FileName);
        break;
    case 6:
        EndProgram();
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

    StartBankProgramm();
}

int main()
{
    ShowMainMenu();
}