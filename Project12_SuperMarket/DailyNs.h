#pragma once
#include"Commodity.h"

class DailyNs :public Commodity {
public:
	DailyNs() { c_type = "DailyNs"; c_description = "��������Ʒ~"; }
	DailyNs(string name, int id, double price, int count, string description = "��������Ʒ~", string type = "DailyNs", string deliveryMode = "���") :
		Commodity(name, id, price, count, description, type, deliveryMode) {}
};