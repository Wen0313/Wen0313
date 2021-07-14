#pragma once
#include"Commodity.h"

class Drinks :public Commodity {
public:
	Drinks() { c_type = "Drinks"; c_description = "好喝就完事了"; }
	Drinks(string name, int id, double price, int count, string description = "好喝就完事了", string type = "Drinks", string deliveryMode = "商店自提")
		:Commodity(name, id, price, count, description, type, deliveryMode){}
};