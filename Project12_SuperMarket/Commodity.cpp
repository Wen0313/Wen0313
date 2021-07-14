#include"Commodity.h"

string Commodity::getName() {
	return c_name;
}

int Commodity::getId() {
	return c_id;
}

double Commodity::getPrice() {
	return c_price;
}

string Commodity::getDescription() {
	return c_description;
}

int Commodity::getCount() {
	return c_count;
}

string Commodity::getType() {
	return c_type;
}

string Commodity::getDeliveryMode() {
	return c_deliveryMode;
}

bool Commodity::operator<(const Commodity* c1)const {
	return this->c_price < c1->c_price;
}