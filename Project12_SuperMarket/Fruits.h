#pragma once
#include"Commodity.h"

class Fruits :public Commodity {
public:
	Fruits() { c_type = "Fruits"; c_description = "爱吃水果身体好"; }
	Fruits(string name, int id, double price, int count, string description = "爱吃水果身体好", string type = "Fruits", string deliveryMode = "美团骑手") :
		Commodity(name, id, price, count, description, type, deliveryMode) {}
};