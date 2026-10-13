#include <iostream>

using namespace std;

// 関数テンプレート
// 2つの値を比較して、小さい方を返す
template <typename Type>
Type Min(Type a, Type b) {

	if (a < b) {
		return a;
	}

	return b;
}

int main() {

	// =========================
	// int型
	// =========================
	int intA;
	int intB;

	cout << "int型の1つ目の値を入力してください：";
	cin >> intA;

	cout << "int型の2つ目の値を入力してください：";
	cin >> intB;

	cout << "小さい値：" << Min(intA, intB) << endl;


	// =========================
	// float型
	// =========================
	float floatA;
	float floatB;

	cout << "\nfloat型の1つ目の値を入力してください：";
	cin >> floatA;

	cout << "float型の2つ目の値を入力してください：";
	cin >> floatB;

	cout << "小さい値：" << Min(floatA, floatB) << endl;


	// =========================
	// double型
	// =========================
	double doubleA;
	double doubleB;

	cout << "\ndouble型の1つ目の値を入力してください：";
	cin >> doubleA;

	cout << "double型の2つ目の値を入力してください：";
	cin >> doubleB;

	cout << "小さい値：" << Min(doubleA, doubleB) << endl;


	return 0;
}