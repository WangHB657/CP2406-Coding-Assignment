#include <iostream>
#include <stdexcept>
#include "Database.h"
#include <fstream>
#include <algorithm>

using namespace std;

namespace Records {

	Employee& Database::addEmployee(const string& firstName,  const string& middleName, const string& lastName, const string& address)
	{
		Employee theEmployee(firstName, middleName, lastName, address);
		theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
		theEmployee.hire();
		mEmployees.push_back(theEmployee);

		return mEmployees.back();
	}

	Employee& Database::getEmployee(int employeeNumber)
	{
		for (auto& employee : mEmployees) {
			if (employee.getEmployeeNumber() == employeeNumber) {
				return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	Employee& Database::getEmployee(const string& firstName, const string& lastName)
	{
		for (auto& employee : mEmployees) {
			if (employee.getFirstName() == firstName &&
				employee.getLastName() == lastName) {
					return employee;
			}
		}
		throw logic_error("No employee found.");
	}

	void Database::displayAll() const
	{
		for (const auto& employee : mEmployees) {
			employee.display();
		}
	}

	void Database::displayCurrent() const
	{
		for (const auto& employee : mEmployees) {
			if (employee.isHired())
				employee.display();
		}
	}

	void Database::displayFormer() const
	{
		for (const auto& employee : mEmployees) {
			if (!employee.isHired())
				employee.display();
		}
	}

	void Database::saveToFile(const string& filename) const {
    ofstream outFile(filename, ios::out); 
    if (!outFile) {
        throw runtime_error("Failed to open file for writing.");
    }
    for (const auto& employee : mEmployees) {
        outFile << employee.getFirstName() << " "
                << employee.getMiddleName() << " "
                << employee.getLastName() << " "
                << employee.getEmployeeNumber() << " "
                << employee.getAddress() << " "
                << employee.getSalary() << " "
                << (employee.isHired() ? "Hired" : "Fired") << endl;
    }
    outFile.close();
}

	void Database::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        throw std::runtime_error("Could not open file for reading.");
    }

    mEmployees.clear(); // Clear current database before loading

    std::string firstName, middleName, lastName, address;
    int employeeNumber, salary;
    bool hiredStatus;
    std::string status;

    while (inFile >> firstName >> middleName >> lastName >> employeeNumber >> address >> salary >> status) {
        Employee emp(firstName, middleName, lastName, address);
        emp.setEmployeeNumber(employeeNumber);
        emp.setSalary(salary);
        emp.setHired(status == "Hired" ? true : false);
        mEmployees.push_back(emp);
    }

    inFile.close();
}

	std::vector<Employee> Database::searchEmployees(const std::string& field, const std::string& searchTerm) {
    std::vector<Employee> results;
    std::string lowerSearchTerm = searchTerm;
    std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);  // Convert search term to lowercase

    for (auto& employee : mEmployees) {
        std::string valueToCheck;
        if (field == "first name") {
            valueToCheck = employee.getFirstName();
        } else if (field == "middle name") {
            valueToCheck = employee.getMiddleName();
        } else if (field == "last name") {
            valueToCheck = employee.getLastName();
        } else if (field == "address") {
            valueToCheck = employee.getAddress();
        }
        std::transform(valueToCheck.begin(), valueToCheck.end(), valueToCheck.begin(), ::tolower); // Convert to lowercase for case insensitive comparison

        if (valueToCheck.find(lowerSearchTerm) != std::string::npos) {
            results.push_back(employee);
        }
    }

    return results;
}

}
