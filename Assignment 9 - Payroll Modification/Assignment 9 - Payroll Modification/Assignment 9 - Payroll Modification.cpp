// Assignment 9 - Payroll Modification.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "LinkedList.h"
using namespace std;

//Function prototypes
void getEmployeeIds(LinkedList<long> &);
void displayWages(LinkedList<long> &, LinkedList<double> &);
void getData(long idNum, int &, double &, double &);
void getEmployeeInfo(LinkedList<long> &, LinkedList<int> &, LinkedList<double> &, LinkedList<double> &);

int main()
{
	LinkedList<long> empId;
	LinkedList<int> hours;
	LinkedList<double> payRate;
	LinkedList<double> wages;
	char again = 'y';
	do{
		getEmployeeIds(empId);
		getEmployeeInfo(empId, hours, payRate, wages);
		displayWages(empId, wages);
		system("pause");
		// Query the user to see if they would like to repeat the program.
		cout << "\n\nWell, that was fun.\nWould you like to run the program again? (enter 'y' for 'yes' and any other input for 'no')\n\n>>>>>>   ";
		cin >> again;
		// Clear the console if they wish to repeat the program. 
		if (tolower(again) == 'y')
			system("cls");
	// Close the while loop. 
	}while(tolower(again)=='y');
	return 0;
}

// Define 'getEmployeeIds function, 
// Stores employee ID numbers in LinkedList

void getEmployeeIds(LinkedList<long> &eid)
{
	char another = 'y';
	long id;

	do{
		cout << "\nEnter an employee ID number: ";
		cin >> id;
		eid.appendNode(id);
		cin.ignore();
		cout << "\nWould you like to enter another id? ";
		cin >> another;
		cin.ignore();
	}while(tolower(another)=='y');
}

// Define function displayWages. 
// Receives 2 parallel arrays (one for IDs and one for gross wages)
// then displays the contents side by side in a format not entirely unlike a chart. 

void displayWages(LinkedList<long> &emp, LinkedList<double> &pay)
{
	long idNum;
	double grossPay;

	cout << fixed << showpoint << setprecision(2) << endl;
	cout << "******************************\n";
	cout << "Employee                 Wages\n";
	cout << "******************************\n";

	if (emp.getFirst(idNum) && pay.getFirst(grossPay))
	{
		cout << "Employee #" << idNum << "   $";
		cout << setw(7) << grossPay << endl;
		while (emp.getNext(idNum) && pay.getNext(grossPay))
		{
			cout << "Employee #" << idNum << "   $";
			cout << setw(7) << grossPay << endl;
		}
	}
}

// Define function getData
// Used to obtain necessary employee info and then calculate gross pay. 

void getData(long idNum, int &hours, double &payRate, double &grossPay)
{
	// Ask the user for # of hours worked then validate the input.
	cout << "Enter the requested data for employee number " << idNum << ".\n";
	cout << "\tHours worked: ";
	cin >> hours;
	while(hours < 0)
	{
		cout << "Very funny, moron. This time, enter a non-negative number: ";
		cin >> hours;
	}
	// Ask user for hourly pay rate and validate the input.
	cout << "\tPay rate: $";
	cin >> payRate;
	while (payRate < 6.00)
	{
		cout << "You know that's illegal in this state, right? The hourly rate has to be above minimum wage.\n Please re-enter the Pay rate: ";
		cin >> payRate;
	}

	// Calculate gross pay
	grossPay = payRate * hours;
}

// Define getEmployeeInfo, which takes 4 arrays as input to calculate gross pay for employee IDs
// (stored in the first array) by multiplying the hours worked (2nd array) by the hourly rate
// (3rd array) and storing the result in the 4th array. 

void getEmployeeInfo(LinkedList<long> &emp, LinkedList<int> &hrs, LinkedList<double> &rate, LinkedList<double> &pay)
{
	long idNum;
	int hours;
	double payRate, grossPay;
	if(emp.getFirst(idNum))
	{
		// Pull employee's data
		getData(idNum, hours, payRate, grossPay);
		// Store the data in the appropriate list.
		hrs.appendNode(hours);
		rate.appendNode(payRate);
		pay.appendNode(grossPay);

		// Get next ID number & data for another employee.
		while(emp.getNext(idNum))
		{
			//Pull employee's data
			getData(idNum, hours, payRate, grossPay);
			//Store data in appropriate lists
			hrs.appendNode(hours);
			rate.appendNode(payRate);
			pay.appendNode(grossPay);
		}
	}
	else
	{
		cout << "No ID #'s were entered. What did you even wake me up for? Jerk...\n";
	}
}

