#include <iostream>
#include "Employee.h"

using namespace std;

namespace Records {

	Employee::Employee(const std::string& firstName, const std::string& middleName, const std::string& lastName, const std::string& address)
		: mFirstName(firstName)
		, mMiddleName(middleName)
		, mLastName(lastName)
		, mAddress(address)
	{
	}

	void Employee::promote(int raiseAmount)
	{
		setSalary(getSalary() + raiseAmount);
	}

	void Employee::demote(int demeritAmount)
	{
		setSalary(getSalary() - demeritAmount);
	}

	void Employee::hire()
	{
		mHired = true;
	}

	void Employee::fire()
	{
		mHired = false;
	}

	void Employee::display() const
	{
		cout << "Employee: " << getLastName() << ", " << getFirstName() << " " << getMiddleName() << endl;
		cout << "-------------------------" << endl;
		cout << (isHired() ? "Current Employee" : "Former Employee") << endl;
		cout << "Employee Number: " << getEmployeeNumber() << endl;
		cout << "Address: " << getAddress() << endl;// New
		cout << "Salary: $" << getSalary() << endl;
		cout << endl;
	}

	// Getters and setters
	void Employee::setFirstName(const string& firstName)
	{
		mFirstName = firstName;
	}
	
	const string& Employee::getFirstName() const
	{
		return mFirstName;
	}

	// new
	void Employee::setMiddleName(const std::string& middleName) {
    mMiddleName = middleName;
}

	const std::string& Employee::getMiddleName() const {
    return mMiddleName;
}

	void Employee::setLastName(const string& lastName)
	{
		mLastName = lastName;
	}

	const string& Employee::getLastName() const
	{
		return mLastName;
	}
// New
	void Employee::setAddress(const std::string& address) {
    	mAddress = address;
	}

	const std::string& Employee::getAddress() const {
    	return mAddress;
	}

	void Employee::setEmployeeNumber(int employeeNumber)
	{
		mEmployeeNumber = employeeNumber;
	}

	int Employee::getEmployeeNumber() const
	{
		return mEmployeeNumber;
	}

	void Employee::setSalary(int salary)
	{
		mSalary = salary;
	}

	int Employee::getSalary() const
	{
		return mSalary;
	}

	bool Employee::isHired() const
	{
		return mHired;
	}

}
