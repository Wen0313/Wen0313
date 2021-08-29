#pragma once
#include<iostream>
#include<vector>
using namespace std;

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
	vector<vector<T>> getV() { return v; }
	class Iterator { //迭代器
	public:
		Iterator(KMatrix* o, int r, int c) :obj(o), row(r), col(c) {}
		void operator++() {
			if (row == obj->v.size() - 1 && col == obj->v[0].size() - 1) {
				obj = nullptr;
				return;
			}
			if (col < obj->v[0].size() - 1) col++;
			else { row++; col = 0; }
		}
		bool operator!=(const Iterator& it2) {
			return row != it2.row && col != it2.col;
		}
		T& operator*() { return obj->v[row][col]; }

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
		return Iterator(this, v.size(), v[0].size());
	}

private:
	vector<vector<T>> v;
};

template<class T> //1
KMatrix<T>::KMatrix() {
	v.clear();
}

template<class T> //1
KMatrix<T>::KMatrix(const KMatrix<T>& km) {
	this->v = vector<vector<T>>(km.v);
}

template<class T> //1
KMatrix<T>& KMatrix<T>::operator=(const KMatrix<T>& km) {
	if (&km != this) {
		vector<vector<T>> newV(km.v);
		this->v = newV;
	}
	return *this;
}

template<class T> //1
void KMatrix<T>::init(int row_count, int col_count) {
	v = vector<vector<T>>(row_count, vector<T>(col_count, 0));
}

template<class T> //1  迭代器遍历输出
void KMatrix<T>::print() { 
	//for (int i = 0; i < v.size(); i++) {
	//	for (int j = 0; j < v[0].size(); j++) {
	//		cout << v[i][j] << "  ";
	//	}
	//	cout << endl;
	//}
	for (auto it = begin(); it != end(); ++it) { //假装是一个迭代器
		if (!it.getObj()) { cout << endl << endl; return; } //走到了end()
		if (!it.getCol() && it.getRow()) cout << endl; //体现矩阵结构
		cout << *it << " ";
	}
}

template<class T> //1
int KMatrix<T>::getRows()const {
	return v.size();
}

template<class T> //1
int KMatrix<T>::getCols()const {
	return v[0].size();
}

template<class T> //1
void KMatrix<T>::setData(int row, int col, T value) {
	try {
		if (row >= v.size()) throw 0;
		if (col >= v[0].size()) throw '0';
		v[row][col] = value;
	}
	catch (int) { cout << "行超出范围，修改失败" << endl; }
	catch (char) { cout << "列超出范围，修改失败" << endl; }
}

template<class T> //1
T KMatrix<T>::getData(int row, int col)const {
	try {
		if (row >= v.size()) throw 0;
		if (col >= v[0].size()) throw '0';
		return v[row][col];
	}
	catch (int) { cout << "行超出范围，获取失败" << endl; }
	catch (char) { cout << "列超出范围，获取失败" << endl; }
}

template<class T> //1
void KMatrix<T>::erase_row(int row) {
	try {
		if (row >= v.size()) throw 0;
		auto it = v.begin();
		for (int i = 0; i < row; i++) it++;
		v.erase(it);
	}
	catch (int) {
		cout << "行超出范围，删除失败" << endl;
	}
}

template<class T> //1
void KMatrix<T>::erase_col(int col) {
	try {
		if (col >= v[0].size()) throw 0;
		for (int i = 0; i < v.size(); i++) {
			auto it = v[i].begin();
			for (int j = 0; j < col; j++) it++;
			v[i].erase(it);
		}
	}
	catch (int) {
		cout << "列超出范围，删除失败" << endl;
	}
}

template<class T> //1
KMatrix<T> KMatrix<T>::operator+(T val) {
	KMatrix<T> res(*this);
	for (int i = 0; i < res.v.size(); i++) {
		for (int j = 0; j < res.v[0].size(); j++) {
			res.v[i][j] += val;
		}
	}
	return res;
}

template<class T> //1
KMatrix<T> KMatrix<T>::operator-(T val) {
	KMatrix<T> res(*this);
	for (int i = 0; i < res.v.size(); i++) {
		for (int j = 0; j < res.v[0].size(); j++) {
			res.v[i][j] -= val;
		}
	}
	return res;
}

template<class T> //1
KMatrix<T> KMatrix<T>::transpose()const {
	KMatrix<T> res;
	res.init(v[0].size(), v.size());
	for (int i = 0; i < res.v.size(); i++) {
		for (int j = 0; j < res.v[0].size(); j++) {
			res.v[i][j] = v[j][i];
		}
	}
	return res;
}

template<class T> //叉乘  M×N * N×K = M×K
KMatrix<T> KMatrix<T>::operator*(const KMatrix<T>& km) {
	try {
		if (v[0].size() != km.v.size()) throw 0;
		KMatrix<T> res;
		res.init(v.size(), km.v[0].size());
		for (int i = 0; i < res.v.size(); i++) {
			for (int j = 0; j < res.v[0].size(); j++) {
				for (int k = 0; k < v[0].size(); k++) {
					res.v[i][j] += v[i][k] * km.v[k][j];
				}
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
		if (v.size() != km.v.size() || v[0].size() != km.v[0].size()) throw 0;
		KMatrix<T> res;
		res.init(v.size(), v[0].size());
		for (int i = 0; i < res.v.size(); i++) {
			for (int j = 0; j < res.v[0].size(); j++) {
				res.v[i][j] = v[i][j] * km.v[i][j];
			}
		}
		return res;
	}
	catch (int) {
		cout << "维度不对" << endl;
	}
}