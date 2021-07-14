#include"SupermarketManager.h"

int main() {
	system("mode con:cols=120 lines=40");
	SupermarketManager SM;
	char choice;
	while (true) {
		system("cls");
		SM.showMenu();
		SM.showCenter("��ѡ��");
		string s;
		cin >> s;
		if (!SM.isInt(s)) {
			SM.showCenter("��������Ժ󷵻����˵�");
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
		case 4: { //����[]��ѡ�� //Ϊ��չʾЧ��д������
			if (SM.getV().empty()) {
				SM.showCenter("û����Ʒ���Ժ󷵻����˵�");
				Sleep(1500);
				break;
			}
			SM.showCenter("��������Ʒ����(Drinks/Greens/DailyNs/Fruits/Snacks):\t");
			string name;
			cin >> name;
			SM[name]; //������
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
		case 8: { //Ϊ��չʾЧ��д������
			if (SM.getV().empty()) {
				SM.showCenter("û����Ʒ���Ժ󷵻����˵�");
				Sleep(1500);
				break;
			}
			SM.showCenter("|-----------��Ʒ��Ϣ----------|");
			SM.showAllCommodities();
			SM.backToMenu();
			break;
		}
		case 0:
			SM.exitSystem();
			break;
		default:
			SM.showCenter("�������,�Ժ�ˢ�����˵�");
			Sleep(1500);
			break;
		}
	}

	return 0;
}