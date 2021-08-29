#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

template<class T>
struct Node {
	Node(int a, int b, T c) :row(a), col(b), val(c) {}
	int row;
	int col;
	T val; //非零数
};

template<class T>
class KMatrix {
public:
	KMatrix();
	KMatrix(const KMatrix<T>& km);
	KMatrix<T>& operator=(const KMatrix<T>& km);

	void init(int row_count, int col_count);
	int getRows()const;
	int getCols()const;
	void setData(int row, int col, T value);
	T getData(int row, int col)const;
	void erase_row(int row);
	void erase_col(int col);
	KMatrix<T> operator+(T val);
	KMatrix<T> operator-(T val);
	KMatrix<T> operator*(const KMatrix<T>& km); //叉乘  M×N * N×K = M×K
	KMatrix<T> dotMul(const KMatrix<T>& km); //点乘 每个对应元素的逐个相乘
	KMatrix<T> transpose()const;
	void print();
	void insertAndSort(int row, int col, T val); //插入并按行列排序
	int binarySearchIndex(int row, int col)const; //排序后可以使用二分查找了
	T Find(int i,int j)const;
	vector<Node<T>> getV() { return v; }
	class Iterator { //迭代器
	public:
		Iterator(KMatrix* o, int r, int c) :obj(o), row(r), col(c) {}
		void operator++() {
			if (row == obj->row - 1 && col == obj->col - 1) {
				obj = nullptr;
				return;
			}
			if (col < obj->col - 1) col++;
			else { row++; col = 0; }
		}
		bool operator!=(const Iterator& it2) {
			return row != it2.row && col != it2.col;
		}
		T& operator*() { 
			//这里似乎有一个问题，就是如果想要迭代器能改掉矩阵的值，
			//但是如果这个值本身为0的话，根本就没有在数组里保存。
			//所以要想改掉他必须先保存一个该位置的节点，这样的话似乎就
			//违背了不保存0的初衷。因为使用*或许只是访问它，
			//并不是每次*it都是想改变他的值。
			if (obj->Find(row, col) == (T)0) obj->insertAndSort(row, col, (T)0);
			for (auto it = obj->v.begin(); it != obj->v.end(); it++) {
				if (it->row == row && it->col == col) return it->val;
			}
		}

		int getRow() { return row; }
		int getCol() { return col; }
		KMatrix<T>* getObj() { return obj; }

	private:
		KMatrix<T>* obj;
		int row;
		int col;
	};
	
	Iterator begin() {
		return Iterator(this, 0, 0);
	}
	Iterator end() {
		return Iterator(this, row, col);
	}

private:
	vector<Node<T>> v;
	int row;
	int col;
};

template<class T> //1
KMatrix<T>::KMatrix() {
	v.clear();
	row = 0;
	col = 0;
}

template<class T> //1
KMatrix<T>::KMatrix(const KMatrix<T>& km) {
	this->v = vector<Node<T>>(km.v);
	row = km.row;
	col = km.col;
}

template<class T> //1
KMatrix<T>& KMatrix<T>::operator=(const KMatrix<T>& km) {
	if (&km != this) {
		this->v = vector<Node<T>>(km.v);
		row = km.row;
		col = km.col;
	}
	return *this;
}

template<class T> //1
void KMatrix<T>::init(int row_count, int col_count) {
	row = row_count;
	col = col_count;
	v.clear();
}

template<class T>  //插入并按行列排序
void KMatrix<T>::insertAndSort(int row, int col, T val) {
	v.push_back(Node<T>(row, col, val));
	sort(v.begin(), v.end(), [](Node<T> n1, Node<T> n2)->bool {return n1.row == n2.row ? n1.col < n2.col : n1.row < n2.row; });
}

template<class T> //迭代器访问
void KMatrix<T>::print() { 
	//for (int i = 0; i < row; i++) {
	//	for (int j = 0; j < col; j++) {
	//		cout << Find(i, j) << "  ";
	//	}
	//	cout << endl;
	//}
	for (auto it = begin(); it != end(); ++it) { //看上去像一个迭代器
		if (!it.getObj()) { cout << endl << endl; return; } //走到了end()
		if (!it.getCol() && it.getRow()) cout << endl; //体现矩阵结构
		cout << *it << " ";
		//下面这个判断是为了保证访问过后0不会存储在v中
		//理论上需要跟在每一次*it之后，但是本项目里只有这里在访问
		//主函数中测试的是修改 所以没有加
		for (auto it1 = it.getObj()->v.begin(); it1 != it.getObj()->v.end(); it1++) {
			if (it1->val == (T)0) {
				it.getObj()->v.erase(it1);
				break;
			}
		}
	}
}

template<class T> //1
int KMatrix<T>::getRows()const {
	return row;
}

template<class T> //1
int KMatrix<T>::getCols()const {
	return col;
}

template<class T> //二分查找，找不到返回-1
int KMatrix<T>::binarySearchIndex(int row, int col)const {
	if (v.empty()) return -1;
	int l = 0, r = v.size() - 1;
	while (l < r) {
		int mid = l + (r - l) / 2;
		if (v[mid].row == row && v[mid].col == col) return mid;
		if (v[mid].row < row || (v[mid].row == row && v[mid].col < col)) {
			l = mid + 1;
		}
		else r = mid;
	}
	return v[r].row == row && v[r].col == col ? r : -1;
}

template<class T> //1
void KMatrix<T>::setData(int row, int col, T value) {
	try {
		if (row >= this->row) throw 0;
		if (col >= this->col) throw '0';
		int index = binarySearchIndex(row, col);
		if (index != -1) {
			v[index].val = value;
			return;
		}
		insertAndSort(row, col, value);
	}
	catch (int) { cout << "行超出范围，修改失败" << endl; }
	catch (char) { cout << "列超出范围，修改失败" << endl; }
}

template<class T> //1
T KMatrix<T>::getData(int row, int col)const {
	try {
		if (row >= this->row) throw 0;
		if (col >= this->col) throw '0';
		int index = binarySearchIndex(row, col);
		return index == -1 ? (T)0 : v[index].val;
	}
	catch (int) { cout << "行超出范围，获取失败" << endl; }
	catch (char) { cout << "列超出范围，获取失败" << endl; }
}

template<class T> //1
void KMatrix<T>::erase_row(int row) {
	try {
		if (row >= this->row) throw 0;
		for (auto it = v.begin(); it != v.end(); it++) {
			if (it->row == row) {
				it = v.erase(it);
				if (it == v.end()) break;
			}
			if (it->row > row) it->row--;
		}
		this->row--;
	}
	catch (int) {
		cout << "行超出范围，删除失败" << endl;
	}
}

template<class T> //1
void KMatrix<T>::erase_col(int col) {
	try {
		if (col >= this->col) throw 0;
		for (auto it = v.begin(); it != v.end(); it++) {
			if (it->col == col) {
				it = v.erase(it);
				if (it == v.end()) break;
			}
			if (it->col > col) it->col--;
		}
		this->col--;
	}
	catch (int) {
		cout << "列超出范围，删除失败" << endl;
	}
}

template<class T>
T KMatrix<T>::Find(int i, int j)const {
	int index = binarySearchIndex(i, j);
	return index == -1 ? (T)0 : v[index].val;
}

template<class T> //1
KMatrix<T> KMatrix<T>::operator+(T val) {
	KMatrix<T> res(*this);
	for (auto it = res.v.begin(); it != res.v.end(); it++) {
		it->val += val;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (res.Find(i, j)) continue;
			res.insertAndSort(i, j, val);
		}
	}
	for (auto it = res.v.begin(); it != res.v.end(); it++) {
		if (it->val == 0) it = res.v.erase(it);
	}
	return res;
}

template<class T> //1
KMatrix<T> KMatrix<T>::operator-(T val) {
	KMatrix<T> res(*this);
	for (auto it = res.v.begin(); it != res.v.end(); it++) {
		it->val -= val;
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (res.Find(i, j)) continue;
			res.insertAndSort(i, j, -val);
		}
	}
	for (auto it = res.v.begin(); it != res.v.end(); it++) {
		if (it->val == 0) it = res.v.erase(it);
	}
	return res;
}

template<class T> //1
KMatrix<T> KMatrix<T>::transpose()const {
	KMatrix<T> res(*this);
	for (auto it = res.v.begin(); it != res.v.end(); it++) {
		int temp = it->row;
		it->row = it->col;
		it->col = temp;
	}
	res.row = col;
	res.col = row;
	return res;
}

template<class T> //叉乘  M×N * N×K = M×K
KMatrix<T> KMatrix<T>::operator*(const KMatrix<T>& km) {
	try {
		if (this->col != km.row) throw 0;
		KMatrix<T> res;
		res.init(this->row, km.col);
		for (int i = 0; i < res.row; i++) {
			for (int j = 0; j < res.col; j++) {
				T temp = (T)0;
				for (int k = 0; k < col; k++) {
					temp += Find(i,k) * km.Find(k,j);
				}
				if (temp) res.insertAndSort(i, j, temp);
			}
		}
		return res;
	}
	catch (int) {
		cout << "维度不对" << endl;
	}
}

template<class T> //点乘 每个对应元素的逐个相乘
KMatrix<T> KMatrix<T>::dotMul(const KMatrix<T>& km) {
	try {
		if (row != km.row || col != km.col) throw 0;
		KMatrix<T> res;
		res.init(row, col);
		for (int i = 0; i < res.row; i++) {
			for (int j = 0; j < res.col; j++) {
				T temp = Find(i, j) * km.Find(i, j);
				if (temp) res.insertAndSort(i, j, temp);
			}
		}
		return res;
	}
	catch (int) {
		cout << "维度不对" << endl;
	}
}