#pragma once
#include"Commodity.h"

class Fruits :public Commodity {
public:
	Fruits() { c_type = "Fruits"; c_description = "����ˮ�������"; }
	Fruits(string name, int id, double price, int count, string description = "����ˮ�������", string type = "Fruits", string deliveryMode = "��������") :
		Commodity(name, id, price, count, description, type, deliveryMode) {}
};