#pragma once
#include"Commodity.h"

class Snacks :public Commodity {
public:
	Snacks() { c_type = "Snacks"; c_description = "总之就是好吃的"; }
	Snacks(string name, int id, double price, int count, string description = "总之就是好吃的", string type = "Snacks", string deliveryMode = "商店自提") :
		Commodity(name, id, price, count, description, type, deliveryMode) {}
};