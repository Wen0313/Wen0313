#pragma once
#include"Commodity.h"

class Greens :public Commodity {
public:
	Greens() { c_type = "Greens"; c_description = "想吃肉？没有"; }
	Greens(string name, int id, double price, int count, string description = "想吃肉？没有", string type = "Greens", string deliveryMode = "美团骑手") :
		Commodity(name, id, price, count, description, type, deliveryMode){}
};