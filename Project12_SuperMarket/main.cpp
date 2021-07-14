#include"SupermarketManager.h"

int main() {
	system("mode con:cols=120 lines=40");
	SupermarketManager SM;
	char choice;
	while (true) {
		system("cls");
		SM.showMenu();
		SM.showCenter("请选择：");
		string s;
		cin >> s;
		if (!SM.isInt(s)) {
			SM.showCenter("输入错误，稍后返回主菜单");
			Sleep(1500);
			continue;
		}
		int choice = SM.getInt(s);
		switch (choice) {
		case 1:
			SM.addCommodity();
			break;
		case 2:
			SM.deleteCommodity();
			break;
		case 3:
			SM.modifyCommodity();
			break;
		case 4: { //重载[]的选项 //为了展示效果写在这里
			if (SM.getV().empty()) {
				SM.showCenter("没有商品，稍后返回主菜单");
				Sleep(1500);
				break;
			}
			SM.showCenter("搜索的商品类型(Drinks/Greens/DailyNs/Fruits/Snacks):\t");
			string name;
			cin >> name;
			SM[name]; //在这里
			break;
		}
		case 5:
			SM.sortCommodities();
			break;
		case 6:
			SM.topFiveCommodities();
			break;
		case 7:
			SM.delivery();
			break;
		case 8: { //为了展示效果写在这里
			if (SM.getV().empty()) {
				SM.showCenter("没有商品，稍后返回主菜单");
				Sleep(1500);
				break;
			}
			SM.showCenter("|-----------商品信息----------|");
			SM.showAllCommodities();
			SM.backToMenu();
			break;
		}
		case 0:
			SM.exitSystem();
			break;
		default:
			SM.showCenter("输入错误,稍后刷新主菜单");
			Sleep(1500);
			break;
		}
	}

	return 0;
}