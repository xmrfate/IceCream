#include <iostream>
#include <string>

using namespace std;

#ifndef DATA_H
#define DATA_H

class IceCreamData {
private:
	string itemName[10];
	string itemDescription[10];
	string toppings[7];
	string itemChoice;

public:
	void setItemName(string item[], int i);
	void setDescription(string description[], int i);
	void setTreatToppings(string treatToppings[], int i);
	void setItemChoice(string item);
	string* getItemName();
	string* getDescription();
	string* getTreatToppings();
	string getItemChoice();
	IceCreamData() { //constructor, initializes itemChoice to void if user did not pick a choice
		itemChoice = "VOID";
	}

	~IceCreamData() { //destructor, frees up memory
		delete[] itemName;
		delete[] itemDescription;
		delete[] toppings;
	}
};

class Volume {
private:
	string typeSize;
	double cost;
	double treatToppingsCost;
	double treatSizeCost;
	double treatTypeCost;

public:
	void setSize(string treatSize);
	void setCost(double treatCost);
	void setToppingsCost(double toppingsCost);
	void setSizeCost(double sizeCost);
	void setTreatTypeCost(double treatCost);
	string getSize();
	double getCost();
	double getToppingsCost();
	double getSizeCost();
	double getTreatTypeCost();
	Volume() { //ensures total cost will be 0 if user did not enter anything, constructor
		cost = 0;
	}
};

class Extras {
private:
	string type;
	string itemToppings[5];
	double toppingQty;

public:
	void setType(string treatType);
	void setToppings(string toppings[], int i);
	void setToppingQty(double toppingQuantity);
	string getType();
	string* getToppings();
	double getToppingQty();
};

void IceCreamData::setItemName(string item[], int i) { //set the item name
	for (int i = 0; i < 10; i++) {
		itemName[i] = item[i];
	}
}

string* IceCreamData::getItemName() { //get the item name
	return itemName;
}

void IceCreamData::setDescription(string description[], int i) { //set the item description
	for (int i = 0; i < 10; i++) {
		itemDescription[i] = description[i];
	}
}

string* IceCreamData::getDescription() {
	return itemDescription;
}

void IceCreamData::setItemChoice(string item) {
	itemChoice = item;
}

string IceCreamData::getItemChoice() {
	return itemChoice;
}

void IceCreamData::setTreatToppings(string toppingName[], int i) {
	for (int i = 0; i < 7; i++) {
		toppings[i] = toppingName[i];
	}
}

string* IceCreamData::getTreatToppings() {
	return toppings;
}

void Volume::setSize(string treatSize) {
	typeSize = treatSize;
}

void Volume::setCost(double treatCost) {
	cost = treatCost;
}

void Volume::setToppingsCost(double toppingsCost) {
	treatToppingsCost = toppingsCost;
}

void Volume::setSizeCost(double sizeCost) {
	treatSizeCost = sizeCost;
}

void Volume::setTreatTypeCost(double treatCost) {
	treatTypeCost = treatCost;
}

string Volume::getSize() {
	return typeSize;
}

double Volume::getCost() {
	return cost;
}

double Volume::getToppingsCost() {
	return treatToppingsCost;
}

double Volume::getSizeCost() {
	return treatSizeCost;
}

double Volume::getTreatTypeCost() {
	return treatTypeCost;
}

void Extras::setType(string treatType) {
	type = treatType;
}

void Extras::setToppings(string toppings[], int i) { //set the toppings
	for (int i = 0; i < 5; i++) {
		itemToppings[i] = toppings[i];
	}
}

void Extras::setToppingQty(double toppingQuantity) {
	toppingQty = toppingQuantity;
}

string Extras::getType() {
	return type;
}

string* Extras::getToppings() { //get the toppings
	return itemToppings;
}

double Extras::getToppingQty() {
	return toppingQty;
}


#endif
