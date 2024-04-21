#include <iostream>
#include <stdexcept>
#include <exception>
#include "Database.h"
#include <fstream>

using namespace std;
using namespace Records;

int displayMenu();
void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void doDemote(Database& db);
void doSave(Database& db);
void doLoad(Database& db);

int main()
{
	Database employeeDB;

	bool done = false;
	while (!done) {
		int selection = displayMenu();
		switch (selection) {
		case 0:
			done = true;
			break;
		case 1:
			doHire(employeeDB);
			break;
		case 2:
			doFire(employeeDB);
			break;
		case 3:
			doPromote(employeeDB);
			break;
		case 4:
			employeeDB.displayAll();
			break;
		case 5:
			employeeDB.displayCurrent();
			break;
		case 6:
			employeeDB.displayFormer();
			break;
        case 7:
            doSave(employeeDB);
            break;
        case 8:
            doLoad(employeeDB);
            break;

		default:
			cerr << "Unknown command." << endl;
			break;
		}
	}

	return 0;
}

int displayMenu()
{
	// Note:
	//		One important note is that this code assumes that the user will
	//		"play nice" and type a number when a number is requested.
	//		When you read about I/O in Chapter 13, you will learn how to
	//		protect against bad input.

    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Save database to file" << endl;
    cout << "8) Load database from file" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";
    
	cin >> selection;
    
	return selection;
}

void doHire(Database& db)
{
    string firstName, middleName, lastName, address;

    cout << "First name? ";
    cin >> firstName;
    cout << "Middle name? ";
    cin >> middleName;
    cout << "Last name? ";
    cin >> lastName;
    cout << "Address? ";
    cin.ignore();  // Ignore the newline left in the input buffer
    getline(cin, address);  // Use getline to handle spaces in the address

    db.addEmployee(firstName, middleName, lastName, address);
    cout << "Employee hired successfully!" << endl;
}

void doFire(Database& db)
{
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
    } catch (const std::logic_error& exception) {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
    }
}

void doPromote(Database& db)
{
    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cout << "How much of a raise? ";
    cin >> raiseAmount;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);
    } catch (const std::logic_error& exception) {
        cerr << "Unable to promote employee: " << exception.what() << endl;
    }
}

void doSave(Database& db) {
    string filename;
    cout << "Enter filename to save the database: ";
    cin >> filename;

    // Check if the file exists
    ifstream fileCheck(filename);
    if (fileCheck) {
        char choice;
        cout << "File already exists. Overwrite? (y/n): ";
        cin >> choice;
        if (tolower(choice) != 'y') {
            cout << "Operation cancelled.\n";
            return;
        }
    }
    fileCheck.close();

    try {
        db.saveToFile(filename);
        cout << "Database saved to '" << filename << "' successfully.\n";
    } catch (const std::exception& e) {
        cerr << "Failed to save the database: " << e.what() << endl;
    }
}

void doLoad(Database& db) {
    string filename;
    cout << "Enter filename to load the database from: ";
    cin >> filename;

    try {
        db.loadFromFile(filename);
        cout << "Database loaded from '" << filename << "' successfully.\n";
    } catch (const std::exception& e) {
        cerr << "Failed to load the database: " << e.what() << endl;
    }
}
