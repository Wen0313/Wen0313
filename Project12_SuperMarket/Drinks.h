#pragma once
#include"Commodity.h"

class Drinks :public Commodity {
public:
	Drinks() { c_type = "Drinks"; c_description = "�úȾ�������"; }
	Drinks(string name, int id, double price, int count, string description = "�úȾ�������", string type = "Drinks", string deliveryMode = "�̵�����")
		:Commodity(name, id, price, count, description, type, deliveryMode){}
};