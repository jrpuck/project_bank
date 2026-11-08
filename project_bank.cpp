#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;
//enum Functions { ShowClients = 1, AddNewClient = 2, DeleteClient = 3, UpdateClient = 4, Exit = 5 };
string fileName = "Clients.txt";
struct sClient
{
	string NumberAccount;
	string Pincode;
	string Name;
	double balance;
	bool Mardown = false;
};
void MenuMission()
{
	cout << "===================================================================================================" << endl;
	cout << right << setw(60) << " Welcome to Menu of the Bank "  << endl;
	cout << "===================================================================================================" << endl;
	cout <<right << setw(40) << " [1]. Show account information "   << endl;
	cout << right << setw(40) << " [2]. Add New Client           "  << endl;
	cout << right << setw(40) << " [3]. Delete Client            "  << endl;
	cout << right << setw(40) << " [4]. Update Client Information"  << endl;
	cout << right << setw(40) << " [5]. Search Client Information"  <<endl;
	cout << right << setw(40) << " [6]. Exit                     "  << endl;
	cout << "===================================================================================================" << endl;

}

vector<string>splitingString(string str, string seperator = "#//#") {
	vector<string> vString;
	short pos = 0;
	string token;
	while ((pos = str.find(seperator)) != string::npos) {
		token = str.substr(0, pos);
		vString.push_back(token);
		str.erase(0, pos + seperator.length());
	}
	vString.push_back(str);
	return vString;
}

vector<sClient> LoadClientsFromFile(string FileName) {
	vector <sClient> lClients;
	ifstream MyFile(FileName);
	if (!MyFile.is_open()) {
		return lClients;
	}
	else {
		string Line;
		while (getline(MyFile, Line)) {
			sClient Client;
			vector<string> vString = splitingString(Line);
			Client.NumberAccount = vString[0];
			Client.Pincode = vString[1];
			Client.Name = vString[2];
			Client.balance = stod(vString[3]);
			Client.Mardown = stoi(vString[4]);
			lClients.push_back(Client);
		}
		MyFile.close();
	}
	return lClients;
}

void HeadingLine(string Title) {
	cout << "===================================================================================================" << endl;
	cout << setw(60) << Title << setw(80) << endl;
	cout << "===================================================================================================" << endl;
}
string ConvertRecordToLine(sClient Client, string seperator = "#//#") {
	string stClient = "";
	stClient += Client.NumberAccount + seperator;
	stClient += Client.Pincode + seperator;
	stClient += Client.Name + seperator;
	stClient += to_string(Client.balance) + seperator;
	stClient += to_string(Client.Mardown);
	return stClient;
}

void SaveClientsToFile(vector <sClient> vClients, string FileName) {
	ofstream MyFile(FileName, ios::app | ios::out);
	if (!MyFile.is_open()) {
		cout << "Error: Could not open the file for writing." << endl;
		return;
	}
	else{
		for (sClient Client : vClients) {
			MyFile << ConvertRecordToLine(Client) << endl;
		}
		MyFile.close();
	}
	
}
void SaveClientsToFileUpdate(vector <sClient> vUpdatedClients,string FileName) {
	ofstream MyFile(fileName,ios::out);
	if (!MyFile.is_open()) {
		cout << "Error: Could not open the file for writing." << endl;
		return;
	}
	else {
		for (sClient Client : vUpdatedClients) {
			MyFile << ConvertRecordToLine(Client) << endl;
		}
		MyFile.close();
	}


}
void ShowHeading(int numClients)
{
	// توسيط العنوان بطريقة أبسط
	cout << "\n\t\t\t\tClient list (" << numClients << ") Clients\n";
	cout << "___________________________________________________________________________________________________\n";

	// استخدام left للمحاذاة لليسار، وتوحيد أحجام الأعمدة
	cout << "| " << left << setw(15) << "Account Number"
		<< "| " << left << setw(10) << "Pincode"
		<< "| " << left << setw(35) << "Name"
		<< "| " << left << setw(15) << "Balance" << endl;

	cout << "___________________________________________________________________________________________________\n";
}
bool FindClientByAccountNumber(string AccountNumber, sClient& FoundClient) {
	vector<sClient> vClients = LoadClientsFromFile(fileName);
	if (vClients.empty() ) {
		return false;
	}
	for (sClient Client : vClients) {
		if (Client.NumberAccount == AccountNumber) {
			FoundClient = Client;
			return true;
		}
	}
	return false;
}
void PrintClientInfo(sClient Client) {
	cout << "____________________________________________________________________________________________________\n";
	cout << "Account Number: " << Client.NumberAccount << endl;
	cout << "Pincode: " << Client.Pincode << endl;
	cout << "Name: " << Client.Name << endl;
	cout << "Balance: " << Client.balance << endl;
	cout << "____________________________________________________________________________________________________\n";
}

//Function Principal
//This function is responsible for adding new clients to the file

vector <sClient> AddClients(vector <sClient>& vClients,string adding = "Adding New Client: ") {
	sClient Client;
	cout << adding << endl;
	cout << "Enter Account Number: ";
	getline(cin >> ws, Client.NumberAccount);
	if (FindClientByAccountNumber(Client.NumberAccount, Client) ) {
		cout << "Error: Account Number already exists. Please enter a unique Account Number." << endl;
		return vClients; // Return without adding the client
	}
	else {
		cout << "Enter Pincode: ";
		getline(cin, Client.Pincode);
		cout << "Enter Name: ";
		getline(cin, Client.Name);
		cout << "Enter Balance: ";
		cin >> Client.balance;
		vClients.push_back(Client);
	}

	return vClients;
}
void AddNewClientTofile() {
	char AddMore = 'Y';
	system("cls");
	HeadingLine("Adding New Client");
	vector <sClient> vClients;
	do {
		vClients = AddClients(vClients);
		cout << "Client added successfully!" << endl;
		cout << "Do you want to add another client? (Y/N): ";
		cin >> AddMore;
	} while (AddMore == 'Y' || AddMore == 'y');
	SaveClientsToFile(vClients, fileName);
}

//End Function Adding New Client to the file

//this function is responsible for showing the information of all clients

void ShowAllClients(string fileName)
{
	vector <sClient> lClients = LoadClientsFromFile(fileName);
	ShowHeading(lClients.size());

	for (sClient c : lClients) {
		// استخدام نفس أحجام setw المطابقة للـ Heading تماماً
		cout << "| " << left << setw(15) << c.NumberAccount
			<< "| " << left << setw(10) << c.Pincode
			<< "| " << left << setw(35) << c.Name
			<< "| " << left << setw(15) << to_string(c.balance) << endl;
	}
	cout << "___________________________________________________________________________________________________\n";
}
//End Function Showing the information of all clients
 

// this function is responsible for deleting a client by account number
void DeleteClientByAccountNumber(string AccountNumber) {
	
	vector<sClient> vClients = LoadClientsFromFile(fileName);
	vector<sClient> vUpdatedClients;
	for (sClient Client : vClients) {
		if (Client.NumberAccount != AccountNumber) {
			vUpdatedClients.push_back(Client);
		}
	}
	SaveClientsToFileUpdate(vUpdatedClients, fileName);
}
void DeleteClient() {
	char choice = 'Y';
	string AccountNumber;
	HeadingLine("Delete Account of Client :");
	cout << "Enter the Account Number of the client to delete: ";
	
	getline(cin >> ws, AccountNumber);
	sClient FoundClient;
	if (FindClientByAccountNumber(AccountNumber, FoundClient)) {
		cout << "Details of the client found: " << endl;
		PrintClientInfo(FoundClient);
		cout << "Are you sure you want to delete this client? (Y/N): ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y') {
			DeleteClientByAccountNumber(AccountNumber);
			cout << "Client with Account Number " << AccountNumber << " has been deleted successfully." << endl;
		}
	}
	else {
		cout << "Error: Client with Account Number " << AccountNumber << " not found." << endl;
	}
}
//End Function Deleting Client by Account Number


//Update Client Information by Account Number
void UpdateClientByAccountNumber(string AccountNumber) {
	vector<sClient> vClients = LoadClientsFromFile(fileName);
	string add = "Update Client : ";
	vector<sClient> vUpdatedClients;
	for (sClient Client : vClients) {
		if (Client.NumberAccount == AccountNumber) {
			cout << "Enter Pincode: ";
			getline(cin>>ws, Client.Pincode);
			cout << "Enter Name: ";
			getline(cin, Client.Name);
			cout << "Enter Balance: ";
			cin >> Client.balance;
			vUpdatedClients.push_back(Client);
		}
		else {
			vUpdatedClients.push_back(Client);
		}
	}
	SaveClientsToFileUpdate(vUpdatedClients, fileName);

}
void UpdateClient() {
	char choice = 'Y';
	string AccountNumber;
	HeadingLine("Update Account of Client :");
	cout << "Enter the Account Number of the client to update: ";
	getline(cin >> ws, AccountNumber);
	sClient FoundClient;
	if (FindClientByAccountNumber(AccountNumber, FoundClient)) {
		cout << "Details of the client found: " << endl;
		PrintClientInfo(FoundClient);
		cout << "Are you sure you want to update this client? (Y/N): ";
		cin >> choice;
		if (choice == 'Y' || choice == 'y') {
			UpdateClientByAccountNumber(AccountNumber);
			cout << "Client with Account Number " << AccountNumber << " has been Update successfully." << endl;
		}
	}
	else {
		cout << "Error: Client with Account Number " << AccountNumber << " not found." << endl;
	}

}
//End Function Update Client Information by Account Number
//Search Client Information by Account Number
void SearchClientByAccountNumber(string AccountNumber) {
	sClient FoundClient;
	if (FindClientByAccountNumber(AccountNumber, FoundClient)) {
		cout << "Details of the client found: " << endl;
		PrintClientInfo(FoundClient);
	}
	else {
		cout << "Error: Client with Account Number " << AccountNumber << " not found." << endl;
	}
}
void SearchClient() {
	string AccountNumber;
	HeadingLine("Search Account of Client :");
	cout << "Enter the Account Number of the client to search: ";
	getline(cin >> ws, AccountNumber);
	SearchClientByAccountNumber(AccountNumber);
}
//End Function Search Client Information by Account Number
void returnToMenu() {
	cout << "Press any key to return to the main menu...";
	cin.ignore();
	cin.get();
}

void StartMenu() {
	short choice;
	do {
		system("cls");
		MenuMission();
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1 :
			system("cls");
			ShowAllClients(fileName);
			returnToMenu();
			break;
		case 2:
			system("cls");
			AddNewClientTofile();
			returnToMenu();
			break;
			
		case 3:
			system("cls");
			DeleteClient();
			returnToMenu();
			break;
			
		case 4:
			system("cls");
			UpdateClient();
			returnToMenu();
			break;
		case 5:
			system("cls");
			SearchClient();
			returnToMenu();
			break;
			
		case 6:
			system("cls");
			cout << "Exiting the program." << endl;
			break;
		default:
			cout << "Invalid choice. Please try again." << endl;
		}
	} while (choice != 6);
	
}

int main()
{
    //MenuMission();
	//AddNewClientTofile();
	//ShowHeading(5);
	//ShowAllClients(fileName);
	//DeleteClient();
	//UpdateClient();
	StartMenu();
	return 0;
}

