#pragma once
#include"Commodity.h"

class Greens :public Commodity {
public:
	Greens() { c_type = "Greens"; c_description = "����⣿û��"; }
	Greens(string name, int id, double price, int count, string description = "����⣿û��", string type = "Greens", string deliveryMode = "��������") :
		Commodity(name, id, price, count, description, type, deliveryMode){}
};