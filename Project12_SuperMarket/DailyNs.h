#pragma once
#include"Commodity.h"

class DailyNs :public Commodity {
public:
	DailyNs() { c_type = "DailyNs"; c_description = "就是日用品~"; }
	DailyNs(string name, int id, double price, int count, string description = "就是日用品~", string type = "DailyNs", string deliveryMode = "快递") :
		Commodity(name, id, price, count, description, type, deliveryMode) {}
};