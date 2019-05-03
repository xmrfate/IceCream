/*
Program Name: Ice Cream App
Program Description: Ice Cream App displays lists all types of ice cream treats that our ice cream shop serves.
After the user chooses their ice cream treat they can then choose their extras (size, toppings, etc).
You may search and sort our inventory for readability--and there are several options for receipt delivery.
Thank you for using my ice cream shop application! Last edited December 9th, 2018, 1:10 AM
Programmer Name: Brandon Jinright
Revision History: Initial Release Version 1.0
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include "data.h"
#include "pch.h"

using namespace std;

//function prototypes
void adminMenu(IceCreamData data, Volume details, Extras customize);
void enterSales(IceCreamData data, Volume details, Extras customize);
void displayChoices(string*, string*, IceCreamData data, Volume details, Extras customize);
void purchaseItems(string*, string*, IceCreamData data, Volume details, Extras customize, string*);
void customizeItems(IceCreamData data, Volume details, Extras customize, string, string*);
void searchInventory(IceCreamData data, Volume details, Extras customize);
void sortInventory(IceCreamData data, Volume details, Extras customize);
void printToScreen(IceCreamData data, Volume details, Extras customize);
void printToFile(IceCreamData data, Volume details, Extras customize);
void menu(IceCreamData data, Volume details, Extras customize);
void calculateCost(IceCreamData data, Volume details, Extras customize, string*, int, string, string, string);
void bubbleSortItems(string*);
void bubbleSortToppings(string*);
void swap(string&, string&);
void searchItems(string*, IceCreamData data, Volume details, Extras customize);
void searchToppings(string*, IceCreamData data, Volume details, Extras customize);

int main()
{
	IceCreamData data;
	Volume details;
	Extras customize;
	const int SIZE = 10;
	string item[SIZE];
	string description[SIZE];

	fstream inputFile;
	inputFile.open("inventory.txt");

	for (int i = 0; i < SIZE; i++) {
		getline(inputFile, item[i]);
		data.setItemName(item, i);
		getline(inputFile, description[i]);
		data.setDescription(description, i);
	}

	inputFile.close();

	cout << "Welcome! This is an Ice Cream application designed to take your order, which can then be customized, and finalized.\n";
	cout << "Your order will then be saved and can be viewed as a receipt. The only administrator feature available right now is \n";
	cout << "the enter sales history feature in the admin panel. Thank you and I hope you enjoy!";

	menu(data, details, customize);

	return 0;
}

void displayChoices(string* items, string* descriptions, IceCreamData data, Volume details, Extras customize) {

	const int SIZE = 10;

	cout << "\nAll ice cream treats start at $5.00 for a small, and $6.50 for a large.\nThe price will vary based on size of treat (small/large) and toppings (up to 5).\n\n";

	for (int i = 0; i < SIZE; i++) {
		cout << i + 1 << ") " << items[i] << "\n" << descriptions[i] << endl;
	}
	menu(data, details, customize);
}

void purchaseItems(string* items, string* descriptions, IceCreamData data, Volume details, Extras customize, string* toppingsNames) {

	string itemName;
	const int SIZE = 10;
	int choice;

	cout << "\nAll ice cream treats start at $5.00 for a small, and $6.50 for a large.\nThe price will vary based on size of treat (small/large) and toppings (up to 5).\n\n";

	for (int i = 0; i < SIZE; i++) {
		cout << i + 1 << ") " << items[i] << endl;
	}
	do {
		cout << "\nPlease enter selection: ";
		cin >> choice;
	} while (choice < 1 || choice>10);

	if (choice == 1) {
		itemName = "Vanilla Delight";
		data.setItemChoice(itemName);
	}
	else if (choice == 2) {
		itemName = "Ice Cream Sundae";
		data.setItemChoice(itemName);
	}
	else if (choice == 3) {
		itemName = "Strawberry Shortcake Sundae";
		data.setItemChoice(itemName);
	}
	else if (choice == 4) {
		itemName = "Brownie Madness";
		data.setItemChoice(itemName);
	}
	else if (choice == 5) {
		itemName = "Cookie Dough Madness";
		data.setItemChoice(itemName);
	}
	else if (choice == 6) {
		itemName = "Brownie & Cookie Dough Blast";
		data.setItemChoice(itemName);
	}
	else if (choice == 7) {
		itemName = "Butter-finger Delight";
		data.setItemChoice(itemName);
	}
	else if (choice == 8) {
		itemName = "Pecan Pie Madness";
		data.setItemChoice(itemName);
	}
	else if (choice == 9) {
		itemName = "Banana Split";
		data.setItemChoice(itemName);
	}
	else if (choice == 10) {
		itemName = "Root-beer Float";
		data.setItemChoice(itemName);
	}
	else {
		cout << "Invalid choice!";
	}

	string item = data.getItemChoice();

	cout << "Thank you! You may now customize your " << item << ".";

	customizeItems(data, details, customize, item, toppingsNames);
}

void customizeItems(IceCreamData data, Volume details, Extras customize, string item, string* toppingsNames) {
	int selectionType;
	int selectionSize;
	int toppingQty;
	const int TOTAL_TOPPINGS = 7;
	string type;
	string typeSize;
	string toppings[5];

	cout << "Would you like a cone or a cup?\n";
	cout << "1) Cup - $0.25\n";
	cout << "2) Cone - $0.50\n";
	cin >> selectionType;

	if (selectionType == 1) {
		type = "Cup";
		customize.setType(type);
	}
	else if (selectionType == 2) {
		type = "Cone";
		customize.setType(type);
	}

	string treatType = customize.getType();

	cout << "Which size would you like?\n";
	cout << "1) Small (3 scoops) - $5.00\n";
	cout << "2) Large (5 scoops) - $6.50\n";
	cin >> selectionSize;

	if (selectionSize == 1) {
		typeSize = "Small (3 scoops)";
		details.setSize(typeSize);
	}
	else if (selectionSize == 2) {
		typeSize = "Large (5 scoops)";
		details.setSize(typeSize);
	}

	string sizeOfTreat = details.getSize();

	for (int i = 0; i < TOTAL_TOPPINGS; i++) {
		cout << "* " << toppingsNames[i] << endl;
	}

	do {
		cout << "How many toppings would you like? (up to 5)? ";
		cin >> toppingQty;
		cin.ignore();
	} while (toppingQty < 0 || toppingQty>5);

	cout << "Please type toppings below (refer to list)" << endl;
	for (int i = 0; i < toppingQty; i++) {
		cout << "Topping #" << i + 1 << ": ";
		getline(cin, toppings[i]);
		customize.setToppings(toppings, i); //set toppings
	}
	string* allToppings = customize.getToppings();

	calculateCost(data, details, customize, allToppings, toppingQty, item, treatType, sizeOfTreat);

	menu(data, details, customize);
}

void searchInventory(IceCreamData data, Volume details, Extras customize) {
	string* items = data.getItemName();
	string* toppings = data.getTreatToppings();
	int selection;

	do {
		cout << "\n\n1. Search Ice Cream Treats\n";
		cout << "2. Search Toppings\n";
		cout << "3. Back to main-menu\n\n";
		cout << "Please enter selection: ";
		cin >> selection;
	} while (selection < 1 || selection>3);

	switch (selection) {
	case 1:
		searchItems(items, data, details, customize);

	case 2:
		searchToppings(toppings, data, details, customize);

	case 3:
		menu(data, details, customize);

	}
}

void sortInventory(IceCreamData data, Volume details, Extras customize) {
	cout << "\n\nSorting inventory. . .";

	string* items = data.getItemName();
	string* toppings = data.getTreatToppings();

	bubbleSortItems(items);
	bubbleSortToppings(toppings);

	menu(data, details, customize);
}

void printToScreen(IceCreamData data, Volume details, Extras customize) {

	string itemName = data.getItemChoice();
	string treatSize = details.getSize();
	string treatType = customize.getType();
	string* toppings = customize.getToppings();
	const double COST = details.getCost();
	double treatSizeCost = details.getSizeCost();
	double toppingsCost = details.getToppingsCost();
	double treatTypeCost = details.getTreatTypeCost();
	int toppingQty = customize.getToppingQty();
	time_t now = time(0); //get system time
	char* date = ctime(&now); //convert time to string

	if (itemName == "VOID") {
		cout << "**NO ITEMS HAVE BEEN SELECTED**\n";
		cout << "**RECEIPT HAS BEEN VOIDED**\n";
	}

	cout << "Date Purchased:";
	cout << "\n" << date;
	cout << "\nItem Name  >> " << itemName << endl;
	cout << "Treat Type >> " << treatType << endl;
	cout << "Treat Size >> " << treatSize << endl;

	for (int i = 0; i < toppingQty; i++) {
		cout << "Treat Topping #" << i + 1 << " >> " << setw(10) << toppings[i] << endl;
	}

	cout << "-------------------------------------------------------" << endl;
	cout << fixed << setprecision(2) << "Type Cost     >> $" << treatTypeCost << endl;
	cout << fixed << setprecision(2) << "Toppings Cost >> $" << toppingsCost << endl;
	cout << fixed << setprecision(2) << "Size Cost     >> $" << treatSizeCost << endl;
	cout << "-------------------------------------------------------" << endl;
	cout << fixed << setprecision(2) << "Total Cost    >> $" << COST << endl;

	menu(data, details, customize);

}

void printToFile(IceCreamData data, Volume details, Extras customize) {

	cout << "\nPrinting to file . . ." << endl;

	fstream outFile;
	outFile.open("receipt.txt", iostream::out);

	string itemName = data.getItemChoice();
	string treatSize = details.getSize();
	string treatType = customize.getType();
	string* toppings = customize.getToppings();
	const double COST = details.getCost();
	double treatSizeCost = details.getSizeCost();
	double toppingsCost = details.getToppingsCost();
	double treatTypeCost = details.getTreatTypeCost();
	int toppingQty = customize.getToppingQty();
	time_t now = time(0); //get system time
	char* date = ctime(&now); //convert time to string

	if (itemName == "VOID") {
		outFile << "**NO ITEMS HAVE BEEN SELECTED**\n";
		outFile << "**RECEIPT HAS BEEN VOIDED**\n";
	}

	outFile << "Date Purchased:";
	outFile << "\n" << date;
	outFile << "\nItem Name  >> " << itemName << endl;
	outFile << "Treat Type >> " << treatType << endl;
	outFile << "Treat Size >> " << treatSize << endl;

	for (int i = 0; i < toppingQty; i++) {
		outFile << "Treat Topping #" << i + 1 << " >> " << setw(10) << toppings[i] << endl;
	}

	outFile << "-------------------------------------------------------" << endl;
	outFile << fixed << setprecision(2) << "Type Cost     >> $" << treatTypeCost << endl;
	outFile << fixed << setprecision(2) << "Toppings Cost >> $" << toppingsCost << endl;
	outFile << fixed << setprecision(2) << "Size Cost     >> $" << treatSizeCost << endl;
	outFile << "-------------------------------------------------------" << endl;
	outFile << fixed << setprecision(2) << "Total Cost    >> $" << COST << endl;

	outFile.close();

	menu(data, details, customize);
}

void menu(IceCreamData data, Volume details, Extras customize) {
	const int TOTAL_TOPPINGS = 7;
	string item = "";
	string* items = data.getItemName();
	string* descriptions = data.getDescription();
	string toppingName[TOTAL_TOPPINGS];

	fstream inFile;
	inFile.open("toppings.txt");

	for (int i = 0; i < TOTAL_TOPPINGS; i++) {
		getline(inFile, toppingName[i]);
		data.setTreatToppings(toppingName, i);
	}

	inFile.close();

	string* toppingsNames = data.getTreatToppings();

	int selection;
	const int ONE = 1,
		TWO = 2,
		THREE = 3,
		FOUR = 4,
		FIVE = 5,
		SIX = 6,
		SEVEN = 7,
		EIGHT = 8,
		NINE = 9;

	do {
		cout << "\n\n1. Display Choices of Ice Cream\n";
		cout << "2. Purchase Ice Cream\n";
		cout << "3. Customize Ice Cream\n";
		cout << "4. Search for Item\n";
		cout << "5. Sort Inventory\n";
		cout << "6. Print Receipt to screen\n";
		cout << "7. Print Receipt to file\n";
		cout << "8. Admin Panel\n";
		cout << "9. Exit\n\n";
		cout << "Please enter selection: ";
		cin >> selection;
	} while (selection < 1 || selection>9);

	switch (selection) {
	case ONE:
		displayChoices(items, descriptions, data, details, customize);

	case TWO:
		purchaseItems(items, descriptions, data, details, customize, toppingsNames);

	case THREE:
		customizeItems(data, details, customize, item, toppingsNames);

	case FOUR:
		searchInventory(data, details, customize);

	case FIVE:
		sortInventory(data, details, customize);

	case SIX:
		printToScreen(data, details, customize);

	case SEVEN:
		printToFile(data, details, customize);

	case EIGHT:
		adminMenu(data, details, customize);

	case NINE:
		exit(0);
	}

}

void calculateCost(IceCreamData data, Volume details, Extras customize, string* allToppings, int toppingQty, string item, string treatType, string sizeOfTreat) {

	const double CHARGE_PER_TOPPING = 0.60;
	double toppingsCost = toppingQty * CHARGE_PER_TOPPING; //calculate cost of toppings
	double treatTypeCost = 0;
	double sizeCost = 0;
	double totalPrice = 0;

	//calculate cost of size
	if (sizeOfTreat == "Small (3 scoops)") {
		sizeCost = 5.00;
		details.setSizeCost(sizeCost);
	}
	else if (sizeOfTreat == "Large (5 scoops)") {
		sizeCost = 6.50;
		details.setSizeCost(sizeCost);
	}

	//calculate cost of treat type (cone/cup)
	if (treatType == "Cup") {
		treatTypeCost = 0.25;
		details.setTreatTypeCost(treatTypeCost);
	}
	else if (treatType == "Cone") {
		treatTypeCost = 0.50;
		details.setTreatTypeCost(treatTypeCost);
	}

	details.setToppingsCost(toppingsCost);
	customize.setToppingQty(toppingQty);

	totalPrice = sizeCost + toppingsCost + treatTypeCost;

	details.setCost(totalPrice);

	cout << "\nCongratulations! You have successfully ordered your " << item << ". You may now view your receipt." << endl;

	printToScreen(data, details, customize);
}

void swap(string &a, string&b) {
	string temp = a;
	a = b;
	b = temp;
}

void bubbleSortItems(string* items) {
	int maxElement;
	int index;
	int size = 10;

	for (maxElement = size - 1; maxElement > 0; maxElement--) {
		for (index = 0; index < maxElement; index++) {
			if (items[index] > items[index + 1]) {
				swap(items[index], items[index + 1]);
			}
		}
	}

	cout << "\n----------------------------------";
	cout << "\nIce Cream Treats - sorted by name" << endl;
	cout << "----------------------------------\n";

	for (int i = 0; i < size; i++) {
		cout << items[i] << endl;
	}
}

void bubbleSortToppings(string* toppings) {
	int maxElement;
	int index;
	int size = 7;

	for (maxElement = size - 1; maxElement > 0; maxElement--) {
		for (index = 0; index < maxElement; index++) {
			if (toppings[index] > toppings[index + 1]) {
				swap(toppings[index], toppings[index + 1]);
			}
		}
	}

	cout << "\n---------------------------";
	cout << "\nToppings - sorted by name" << endl;
	cout << "---------------------------\n";

	for (int i = 0; i < size; i++) {
		cout << toppings[i] << endl;
	}
}

void searchItems(string* items, IceCreamData data, Volume details, Extras customize) {
	string value;
	cin.ignore();
	cout << "\n\nPlease enter ice cream treat name to search for: ";
	getline(cin, value);

	cout << "Searching for " << value << " . . .\n\n";

	const int SIZE = 10;
	int index = 0;
	int position = -1;
	bool found = false;

	//search for name
	while (index < SIZE && !found) {
		if (items[index] == value) {
			found = true;
			position = index;

			cout << "Name matches at position " << index << "." << endl;
			cout << items[index];
		} if (items[index] != value) {
			found = false;
			cout << "Name does not match at position " << index << "." << endl;
		}

		index++;
	}

	searchInventory(data, details, customize);
}

void searchToppings(string* toppings, IceCreamData data, Volume details, Extras customize) {
	string value;
	cin.ignore();
	cout << "\n\nPlease enter topping name to search for: ";
	getline(cin, value);

	cout << "Searching for " << value << " . . .\n\n";

	const int SIZE = 7;
	int index = 0;
	int position = -1;
	bool found = false;

	//search for name
	while (index < SIZE && !found) {
		if (toppings[index] == value) {
			found = true;
			position = index;

			cout << "Name matches at position " << index << "." << endl;
			cout << toppings[index];
		} if (toppings[index] != value) {
			found = false;
			cout << "Name does not match at position " << index << "." << endl;
		}

		index++;
	}

	searchInventory(data, details, customize);
}

void adminMenu(IceCreamData data, Volume details, Extras customize) {

	int selection;

	cout << "1. Enter Sales\n";
	cout << "2. Exit to menu\n";
	cin >> selection;

	do {
		switch (selection) {
		case 1:
			enterSales(data, details, customize);

		case 2:
			menu(data, details, customize);
		}
	} while (selection < 1 || selection>2);

}

void enterSales(IceCreamData data, Volume details, Extras customize) {
	enum Days { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };
	const int numDays = 7;
	double sales[numDays];
	double totalSales;
	int index;

	for (index = MONDAY; index <= SUNDAY; index++) {
		cout << "Sales for day " << index << ": ";
		cin >> sales[index];

		totalSales += sales[index];
	}

	cout << fixed << setprecision(2) << "\nMonday:    $" << sales[MONDAY] << endl;
	cout << "Tuesday:   $" << sales[TUESDAY] << endl;
	cout << "Wednesday: $" << sales[WEDNESDAY] << endl;
	cout << "Thursday:  $" << sales[THURSDAY] << endl;
	cout << "Friday:    $" << sales[FRIDAY] << endl;
	cout << "Saturday:  $" << sales[SATURDAY] << endl;
	cout << "Sunday:    $" << sales[SUNDAY] << endl;

	cout << "-------------------\n";
	cout << "Total Sales: $" << totalSales << "\n\n";

	adminMenu(data, details, customize);
}
