#pragma once
#include<vector>
#include"Commodity.h"
#include"Drinks.h"
#include"Greens.h"
#include"Fruits.h"
#include"Snacks.h"
#include"DailyNs.h"
#include<Windows.h>

class SupermarketManager {
public:

	SupermarketManager();
	void showMenu();

	void addCommodity();
	void deleteCommodity();
	void modifyCommodity();
	void operator[](string name);
	void sortCommodities();
	void topFiveCommodities();
	void delivery();
	void showAllCommodities();
	void exitSystem();

	void backToMenu(); //�Ƿ񷵻����˵�
	void showCommodity(Commodity* c);
	bool isExist(string name); //�Ƿ��Ѵ���
	bool isExist(int id);
	int getCount(string name);
	void showCenter(string message); //����ڿ���̨���� 
	bool isInt(string s);//Ӧ��int�Ƿ�����
	int getInt(string s);
	bool isDouble(string s); //Ӧ�Լ۸�double�ķǷ�����
	double getDouble(string s);
	vector<Commodity*> getV();

private:
	vector<Commodity*> v;
};