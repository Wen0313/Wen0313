#pragma once
#include"Commodity.h"

class Snacks :public Commodity {
public:
	Snacks() { c_type = "Snacks"; c_description = "��֮���ǺóԵ�"; }
	Snacks(string name, int id, double price, int count, string description = "��֮���ǺóԵ�", string type = "Snacks", string deliveryMode = "�̵�����") :
		Commodity(name, id, price, count, description, type, deliveryMode) {}
};