#pragma once
#include<iostream>
#include<string>
using namespace std;

class Commodity {
public:
	virtual ~Commodity() = 0 {};

	string getName();
	int getId();
	double getPrice();
	string getDescription();
	int getCount();
	string getType();
	string getDeliveryMode();
	void setName(string name) { c_name = name; }
	void setId(int id) { c_id = id; }
	void setPrice(double price) { c_price = price; }
	void setDescription(string d) { c_description = d; }
	void setCount(int n) { c_count = n; }
	bool operator<(const Commodity* c1)const;

protected:
	Commodity() { c_id = 0; c_price = 0; c_count = 0; }
	Commodity(string name, int id, double price, int count, string description = " ", string type = " ",string deliveryMode = " ") :c_name(name),
		c_id(id), c_price(price), c_description(description), c_count(count), c_type(type), c_deliveryMode(deliveryMode) {}

	string c_name;
	int c_id=0;
	double c_price=0;
	string c_description;
	int c_count=0;
	string c_type;
	string c_deliveryMode;
};