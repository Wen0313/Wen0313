//#include"KMatrix.h"
#include"KMatrix_less.h"

void test1(){
	KMatrix<int> km;
	km.init(5, 6);
	KMatrix<int> km1 = km;
	cout << "[km1 = km.init(5,6)]" << endl;
	km1.print();
	cout << "km1.v.size():" << km1.getV().size() << endl;
	cout << "Rows:" << km.getRows() << endl;
	cout << "Cols:" << km.getCols() << endl;
	cout << endl;
	km.setData(0, 1, 1);
	km.setData(6, 6, 6);
	km.setData(1, 10, 10);
	km.setData(2, 3, 3);
	cout << "[after km.setData()]" << endl;
	km.print();
	cout << "km.v.size():" << km.getV().size() << endl;
	cout << "km.getData(0,1):" << km.getData(0, 1) << endl;
	cout << "km.getData(2,2):" << km.getData(2, 2) << endl;
	cout << endl;
	km.erase_row(10);
	km.erase_row(0);
	cout << "[after km.erase_row(0)]" << endl;
	km.print();
	km.erase_col(10);
	km.erase_col(3);
	cout << "[after km.erase_col(3)]" << endl;
	km.print();
	cout << "km.v.size():" << km.getV().size() << endl << endl;
}

void test2() {
	KMatrix<double> km;
	km.init(5, 6);
	KMatrix<double> km1 = km + 22.8;
	cout << "[after km + 22.8]" << endl;
	km1.print();
	KMatrix<double> km2 = km - 2.8;
	cout << "[after km - 2.8]" << endl;
	km2.print();
	km1.setData(0, 1, 10.1);
	km1.setData(0, 2, 11.2);
	km1.setData(1, 1, 30.3);
	km1.setData(2, 5, 40.4);
	km1.setData(3, 1, 50.5);
	km1.setData(4, 3, 60.6);
	cout << "[before km.transpose()]" << endl;
	km1.print();
	KMatrix<double> km3 = km1.transpose();
	cout << "[after km.transpose()]" << endl;
	km3.print();
}

void test3() {
	KMatrix<int> km,km1;
	km.init(2, 4);
	km1.init(4, 3);
	km.setData(0, 0, 1);
	km.setData(0, 1, 2);
	km.setData(0, 2, 3);
	km.setData(0, 3, 4);
	km.setData(1, 0, 5);
	km.setData(1, 1, 6);
	km.setData(1, 2, 7);
	km.setData(1, 3, 8);

	//km1.setData(0, 0, 1);
	KMatrix<int>::Iterator it(&km1, 0, 0);
	*it = 1;  //µü´úÆ÷ĞŞ¸Ä²âÊÔ
	km1.setData(0, 1, 5);
	km1.setData(0, 2, 9);
	km1.setData(1, 0, 2);
	km1.setData(1, 1, 6);
	km1.setData(1, 2, 1);
	km1.setData(2, 0, 3);
	km1.setData(2, 1, 7);
	km1.setData(2, 2, 2);
	km1.setData(3, 0, 4);
	km1.setData(3, 1, 8);
	km1.setData(3, 2, 3);
	cout << "[km]" << endl;
	km.print();
	cout << "[km1] *it(0,0) = 1" << endl;
	km1.print();
	KMatrix<int> km2 = km * km1;
	cout << "[km2 = km * km1]" << endl;
	km2.print();
}

void test4() {
	KMatrix<int> km;
	km.init(2, 4);
	km.setData(0, 0, 1);
	km.setData(0, 1, 2);
	km.setData(0, 2, 3);
	km.setData(0, 3, 4);
	km.setData(1, 0, 5);
	km.setData(1, 1, 6);
	km.setData(1, 2, 7);
	km.setData(1, 3, 8);
	KMatrix<int> km1(km);
	//km1.erase_row(1);

	cout << "[km]" << endl;
	km.print();
	cout << "[km1(km)]" << endl;
	km1.print();
	KMatrix<int> km2 = km.dotMul(km1);
	cout << "[km2 = km ¡¤ km1]" << endl;
	km2.print();
}

int main() {
	cout << "[test1:»ù´¡²âÊÔ]" << endl;
	test1();
	cout << "[test2:ÖØÔØ]" << endl;
	test2();
	cout << "[test3:²æ³Ë]" << endl;
	test3();
	cout << "[test4:µã³Ë]" << endl;
	test4();

	return 0;
}