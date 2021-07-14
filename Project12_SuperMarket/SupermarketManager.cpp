#include"SupermarketManager.h"
#include<algorithm>
#include<conio.h> 
#include<stdio.h>

SupermarketManager::SupermarketManager() {
	//v.clear();
	//����
	Commodity* c1 = new Drinks("01", 1, 1.1, 1);
	Commodity* c2 = new Greens("05", 5, 5.5, 5);
	Commodity* c3 = new Fruits("03", 3, 3.3, 3);
	Commodity* c4 = new DailyNs("04", 4, 4.4, 4);
	Commodity* c5 = new Snacks("06", 6, 6.6, 6);
	Commodity* c6 = new DailyNs("02", 2, 2.2, 2);
	Commodity* c7 = new Drinks("09", 9, 9.9, 9);
	Commodity* c8 = new Snacks("07", 7, 7.7, 7);
	Commodity* c9 = new Fruits("08", 8, 8.8, 8);
	v.push_back(c1);
	v.push_back(c2);
	v.push_back(c3);
	v.push_back(c4);
	v.push_back(c5);
	v.push_back(c6);
	v.push_back(c7);
	v.push_back(c8);
	v.push_back(c9);
}

//default
void SupermarketManager::showMenu() {
	showCenter("|---------SuperMarket---------|");
	showCenter("|                             |");
	showCenter("|      1.������Ʒ��Ϣ         |");
	showCenter("|      2.ɾ����Ʒ��Ϣ         |");
	showCenter("|      3.�޸���Ʒ��Ϣ         |");
	showCenter("|      4.��Ʒ��Ϣ����         |");
	showCenter("|      5.���۸��������       |");
	showCenter("|      6.����۸�ǰ�����Ʒ   |");
	showCenter("|      7.�ͻ�                 |");
	showCenter("|      *8.չʾ������Ʒ��Ϣ    |");
	showCenter("|      0.�˳�ϵͳ             |");
	showCenter("|                             |");
	showCenter("|-----------------------------|");
}

void SupermarketManager::showCenter(string message) {
	int len = message.size();
	int len_space = (120 - len) / 2;
	cout << endl;
	for (int i = 0; i < len_space; ++i) cout << " ";
	cout << message;
}

//case 0
void SupermarketManager::exitSystem() {
	cout << endl;
	showCenter("��ӭ�´�ʹ�ã��ټ�");
	exit(0);
}

//case 1
void SupermarketManager::addCommodity() {
	showCenter("|-----------������Ʒ----------|");
	showCenter("��ѡ������(1.Drink 2.Greens 3.DailyNs 4.Fruits 5.Snacks):\t");
	string s2;
	cin >> s2;
	if (!isInt(s2)) {
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	int type = getInt(s2);
	Commodity* newC;
	switch (type) {
	case 1:
		newC = new Drinks();
		showCenter("���ͣ�Drinks");
		break;
	case 2:
		newC = new Greens();
		showCenter("���ͣ�Greens");
		break;
	case 3:
		newC = new DailyNs();
		showCenter("���ͣ�DailyNs");
		break;
	case 4:
		newC = new Fruits();
		showCenter("���ͣ�Fruits");
		break;
	case 5:
		newC = new Snacks();
		showCenter("���ͣ�Snacks");
		break;
	default:
		showCenter("�������");
		Sleep(1500);
		return;
	}
	showCenter("��������Ʒ����");
	string s;
	cin >> s;
	if (isExist(s)) {
		showCenter("��Ʒ�Ѵ���");
		showCenter("��������ӵ�������");
		string s1;
		cin >> s1;
		if (!isInt(s1)) {
			showCenter("��������Ժ󷵻����˵�");
			Sleep(1500);
			return;
		}
		int increase = getInt(s1);
		for (auto c : v) {
			if (c->getName() == s) c->setCount(c->getCount() + increase);
		}
		showCenter("...");
		showCenter("��Ʒ��ӳɹ�");
		backToMenu();
		return;
	}
	newC->setName(s);
	showCenter("��������ƷID��");
	string s1;
	cin >> s1;
	if (!isInt(s1)) {
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	int i = getInt(s1);
	if (isExist(i)) {
		showCenter("id���Ѵ���,�Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	newC->setId(i);
	showCenter("�����ü۸�");
	string pp;
	cin >> pp;
	if (!isDouble(pp)) {
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	double p = getDouble(pp);
	newC->setPrice(p);
	showCenter("������������");
	cin >> s1;
	if (!isInt(s1)) {
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	int c = getInt(s1);
	newC->setCount(c);
	v.push_back(newC);
	showCenter("...");
	showCenter("��Ʒ��ӳɹ�");
	backToMenu();
}

//case 2
void SupermarketManager::deleteCommodity() {
	if (v.empty()) {
		showCenter("û����Ʒ���Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	showCenter("|-----------ɾ����Ʒ----------|");
	showAllCommodities();
	showCenter("������Ҫɾ������Ʒ����:");
	string name;
	cin >> name;
	if (!isExist(name)) {
		showCenter("û�и���Ʒ���Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	showCenter("������Ҫɾ��������:");
	string s;
	cin >> s;
	if (!isInt(s)) {
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	int count = getInt(s);
	if (count <= 0 || count > getCount(name)) {
		if (count <= 0) showCenter("��������Ժ󷵻����˵�");
		else showCenter("��������,�Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	int loc = -1;
	bool flag = false; //�����Ƿ�=0
	for (auto c : v) {
		loc++;
		if (c->getName() == name) {
			int left = c->getCount() - count;
			if (left <= 0) {
				flag = true;
				break;
			}
			c->setCount(left);
			break;
		}
	}
	showCenter("ɾ���ɹ�������");
	auto it = v.begin();
	for (int i = 0; i < loc; i++) it++;
	if (flag) v.erase(it);
	backToMenu();
}

//case 3 
void SupermarketManager::modifyCommodity() {
	if (v.empty()) {
		showCenter("û����Ʒ���Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	showCenter("|-----------�޸���Ʒ----------|");
	showAllCommodities();
	showCenter("������Ҫ�޸ĵ���Ʒid:");
	string s1;
	cin >> s1;
	if (!isInt(s1)) {
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	int id = getInt(s1);
	if (!isExist(id)) {
		showCenter("û�и���Ʒ���Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	showCenter("�޸��1.�۸� 2.��������");
	cin >> s1;
	if (!isInt(s1)) {
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	int choice = getInt(s1);
	switch(choice) {
	case 1: {
		showCenter("�¼۸�");
		string pp;
		cin >> pp;
		if (!isDouble(pp)) {
			showCenter("��������Ժ󷵻����˵�");
			Sleep(1500);
			return;
		}
		double price = getDouble(pp);
		for (auto c : v) {
			if (c->getId() == id) {
				c->setPrice(price);
				break;
			}
		}
		showCenter("�۸��޸ĳɹ�");
		backToMenu();
		break;
	}
	case 2: {
		showCenter("��������");
		string d;
		cin >> d;
		for (auto c : v) {
			if (c->getId() == id) {
				c->setDescription(d);
				break;
			}
		}
		showCenter("�����޸ĳɹ�");
		backToMenu();
		break;
	}
	default:
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
}

//case 4
void SupermarketManager::operator[](string name) {
	cout << endl;
	int count = 0;
	for (auto c : v) {
		if (c->getType() == name) {
			showCommodity(c);
			count++;
		}
	}
	if (!count) showCenter("�ƺ�û��������ƷŶ~");
	backToMenu();
}

//case 5
void SupermarketManager::sortCommodities() {
	if (v.empty()) {
		showCenter("û����Ʒ���Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	sort(v.begin(), v.end(), [](Commodity* c1, Commodity* c2)->bool {return !(*c1 < c2); });
	showCenter("��ѡ���������ͣ�1.�ɸߵ��� 2.�ɵ͵��ߣ���");
	string s;
	cin >> s;
	if (!isInt(s)) {
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	int choice = getInt(s);
	switch (choice) {
	case 1: 
		showAllCommodities();
		break;
	case 2: 
		reverse(v.begin(), v.end());
		showAllCommodities();
		break;
	default:
		showCenter("�������");
		Sleep(1500);
		return;
	}
	backToMenu();
}

//case 6
void SupermarketManager::topFiveCommodities() {
	if (v.empty()) {
		showCenter("û����Ʒ���Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	if (v.size() <= 5) {
		showCenter("û��5��������Ʒ��������Ʒ����(��ѡ��case 5����)��");
		showAllCommodities();
		backToMenu();
		return;
	}
	sort(v.begin(), v.end(), [](Commodity* c1, Commodity* c2)->bool {return !(*c1 < c2); });
	showCenter("|--------�۸�ǰ����Ʒ---------|");
	cout << endl;
	for (int i = 0; i < 5; i++) {
		showCommodity(v[i]);
	}
	backToMenu();
}

//case 7
void SupermarketManager::delivery() {
	if (v.empty()) {
		showCenter("û����Ʒ���Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	showAllCommodities();
	showCenter("��������Ҫ���͵���Ʒ���֣�");
	string name;
	cin >> name;
	if (!isExist(name)) {
		showCenter("û�и���Ʒ���Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	showCenter("��������Ҫ���͵�������");
	string s;
	cin >> s;
	if (!isInt(s)) {
		showCenter("��������Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	int count = getInt(s);
	if (count > getCount(name)) {
		showCenter("����ʧ�ܣ���Ʒ���㣬�Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	string str_deliveryMode,str_type;
	int loc = -1;
	bool flag = false; //�����Ƿ�=0
	for (auto c : v) {
		loc++;
		if (c->getName() == name) {
			str_deliveryMode = c->getDeliveryMode();
			str_type = c->getType();
			int left = c->getCount() - count;
			if (left <= 0) {
				flag = true;
				break;
			}
			c->setCount(left);
			break;
		}
	}
	auto it = v.begin();
	for (int i = 0; i < loc; i++) it++;
	if (flag) v.erase(it);
	char ss[100];
	showCenter("�������ַ��");
	cin >> s;
	sprintf_s(ss, "���ͳɹ���%s��Ʒ��ʹ��%s�ͳ�", str_type.c_str(), str_deliveryMode.c_str());
	showCenter(ss);
	backToMenu();
}

//case *8
void SupermarketManager::showAllCommodities() {
	if (v.empty()) {
		showCenter("û����Ʒ���Ժ󷵻����˵�");
		Sleep(1500);
		return;
	}
	cout << endl;
	for (auto c : v) {
		showCommodity(c);
	}
	cout << endl;
}

void SupermarketManager::backToMenu() {
	cout << endl;
	showCenter("�Ƿ񷵻����˵�(y����,n�˳�):");
	char ch = _getch();
	if (ch == 'y') {
		return;
	}
	else if (ch == 'n') {
		exitSystem();
	}
	else {
		showCenter("�������,�Ժ󷵻����˵�");
		Sleep(1500);
	}
}

void SupermarketManager::showCommodity(Commodity* c) {
	cout << "[" << "type��" << c->getType() << "\t"
		<< "name: " << c->getName() << "\t"
		<< "id: " << c->getId() << "\t"
		<< "price: " << c->getPrice() << "\t"
		<< "description: " << c->getDescription() << "\t"
		<< "count: " << c->getCount() << "]" << endl;
}

bool SupermarketManager::isExist(string name) {
	for (auto c : v) {
		if (c->getName() == name) return true;
	}
	return false;
}

bool SupermarketManager::isExist(int id) {
	for (auto c : v) {
		if (c->getId() == id) return true;
	}
	return false;
}

int SupermarketManager::getCount(string name) {
	for (auto c : v) {
		if (c->getName() == name) return c->getCount();
	}
}

//�Ƿ�������
bool SupermarketManager::isInt(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] < '0' || s[i]>'9') return false;
	}
	return true;
}

int SupermarketManager::getInt(string s) {
	int len = s.size();
	int res = 0;
	for (int i = 0; i < len; i++) {
		int num = s[i] - '0';
		res = res * 10 + num;
	}
	return res;
}

bool SupermarketManager::isDouble(string s) {
	char* end = 0;
	double val = strtod(s.c_str(), &end);
	return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
}

double SupermarketManager::getDouble(string s) {
	if (isInt(s)) return (double)getInt(s);
	int loc = s.find('.');
	double res = 0;
	for (int i = 0; i < loc; i++) {
		int num = s[i] - '0';
		res = res * 10 + num;
	}
	double end = 0;
	int count = 0;
	for (int i = loc + 1; i < s.size(); i++) {
		count++;
		int num = s[i] - '0';
		end += num / pow(10, count);
	}
	res += end;
	return res;
}

vector<Commodity*> SupermarketManager::getV() {
	return v;
}