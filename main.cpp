
#include <iostream>

// ================================
// MinCalculatorクラステンプレート
// ================================
template <typename T1, typename T2>
class MinCalculator {
public:

    // ================================
    // 2つの値を比較して小さい値を返す
    // ================================
    T1 Min(T1 a, T2 b) {

        // 比較する型を統一する
        if (a < static_cast<T1>(b)) {
            return a;
        }

        return static_cast<T1>(b);
    }
};

// ================================
// 比較結果を表示する関数テンプレート
// ================================
template <typename T1, typename T2>
void ExecuteMin(
    const char* typeName,
    T1 a,
    T2 b) {

    // クラステンプレートのインスタンス生成
    MinCalculator<T1, T2> calculator;

    // ================================
    // 比較する値の表示
    // ================================
    std::cout << "\n[" << typeName << "]\n";

    std::cout
        << "First value: "
        << a
        << std::endl;

    std::cout
        << "Second value: "
        << b
        << std::endl;

    // ================================
    // 最小値の表示
    // ================================
    std::cout
        << "Minimum value: "
        << calculator.Min(a, b)
        << std::endl;
}

// ================================
// メイン関数
// ================================
int main() {

    std::cout
        << "Min Class Template Start!"
        << std::endl;

    // ================================
    // 同じ型の組み合わせ（3パターン）
    // ================================

    // int型 × int型
    ExecuteMin<int, int>("int - int", 10, 20);

    // float型 × float型
    ExecuteMin<float, float>("float - float", 3.5f, 2.5f);

    // double型 × double型
    ExecuteMin<double, double>("double - double", 7.8, 4.2);

    // ================================
    // 異なる型の組み合わせ（3パターン）
    // ================================

    // int型 × float型
    ExecuteMin<int, float>("int - float", 10, 5.0f);

    // int型 × double型
    ExecuteMin<int, double>("int - double", 20, 8.0);

    // float型 × double型
    ExecuteMin<float, double>("float - double", 6.5f, 3.0);

    std::cout
        << "\nMin Class Template End!"
        << std::endl;

    return 0;
}
