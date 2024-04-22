#include <iostream>
#include <stdexcept>
#include <exception>
#include "Database.h"
#include <fstream>
#include <limits>

using namespace std;
using namespace Records;

enum Role { MANAGER, EMPLOYEE };

int displayMenu(Role role);

void doHire(Database& db);
void doFire(Database& db);
void doPromote(Database& db);
void doDemote(Database& db);
void doSave(Database& db);
void doLoad(Database& db);
void doEdit(Database& db);
void doSearch(Database& db);


int main()
{
	Database employeeDB;
    Role userRole;

    string roleChoice;
    cout << "Are you a Manager or an Employee? (M/E): ";
    cin >> roleChoice;

    if (roleChoice == "M" || roleChoice == "m") {
        userRole = MANAGER;
    } else {
        userRole = EMPLOYEE;
    }

	bool done = false;
	while (!done) {
		int selection = displayMenu(userRole);
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
        case 9:
            doEdit(employeeDB);
            break;
        case 10:
            doSearch(employeeDB);
            break;

		default:
			cerr << "Unknown command." << endl;
			break;
		}
	}

	return 0;
}

int displayMenu(Role role)
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
    if (role == MANAGER) {
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Save database to file" << endl;
    cout << "8) Load database from file" << endl;
    cout << "9) Edit employee" << endl;
    cout << "10) Search employee" << endl;
    }  
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

void doEdit(Database& db) {
    int employeeNumber;
    cout << "Enter employee number: ";
    cin >> employeeNumber;

    try {
        Employee& emp = db.getEmployee(employeeNumber);
        cout << "Editing Employee: " << employeeNumber << endl;
        emp.display();

        string newAddress;
        int newSalary;
        char hiredStatus;

        cout << "New Address (blank to skip): ";
        cin.ignore();  // To consume any leftover newline characters
        getline(cin, newAddress);
        if (!newAddress.empty()) {
            emp.setAddress(newAddress);
        }

        cout << "New Salary (0 to skip): ";
        cin >> newSalary;
        if (newSalary > 0) {
            emp.setSalary(newSalary);
        }

        cout << "Is the employee hired or fired? (h/f, blank to skip): ";
        cin >> hiredStatus;
        if (hiredStatus == 'h' || hiredStatus == 'H') {
            emp.hire();
        } else if (hiredStatus == 'f' || hiredStatus == 'F') {
            emp.fire();
        }

        cout << "Employee updated successfully.\n";
        emp.display();  // Display the updated details
    } catch (const std::logic_error& ex) {
        cerr << "Failed to find employee: " << ex.what() << endl;
    }
}

void doSearch(Database& db) {
    string field, searchTerm;
    cout << "Enter field to search by (first name, middle name, last name, address): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore leftover newline
    getline(cin, field);
    cout << "Enter search term: ";
    getline(cin, searchTerm);

    vector<Employee> found = db.searchEmployees(field, searchTerm);
    if (found.empty()) {
        cout << "No results found." << endl;
    } else {
        for (const auto& emp : found) {
            emp.display();
        }
    }
}

