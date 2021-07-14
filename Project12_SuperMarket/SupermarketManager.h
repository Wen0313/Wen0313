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

	void backToMenu(); //是否返回主菜单
	void showCommodity(Commodity* c);
	bool isExist(string name); //是否已存在
	bool isExist(int id);
	int getCount(string name);
	void showCenter(string message); //输出在控制台中心 
	bool isInt(string s);//应对int非法输入
	int getInt(string s);
	bool isDouble(string s); //应对价格double的非法输入
	double getDouble(string s);
	vector<Commodity*> getV();

private:
	vector<Commodity*> v;
};