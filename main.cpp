
#include <iostream>
#include <limits>

// ================================
// MinCalculatorクラステンプレート
// ================================
template <typename Type>
class MinCalculator {
public:

    // ================================
    // 2つの値を比較して小さい値を返す
    // ================================
    Type Min(Type a, Type b) {

        if (a < b) {
            return a;
        }

        return b;
    }
};

// ================================
// 入力と比較を行う関数テンプレート
// ================================
template <typename Type>
void ExecuteMin(const char* typeName) {

    // 入力する2つの値
    Type a{};
    Type b{};

    // クラステンプレートのインスタンス生成
    MinCalculator<Type> calculator;

    // ================================
    // ユーザー入力
    // ================================
    std::cout << "\n[" << typeName << "]\n";

    std::cout << "Input first value: ";
    while (!(std::cin >> a)) {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
        std::cout << "Invalid input. Try again: ";
    }

    std::cout << "Input second value: ";
    while (!(std::cin >> b)) {
        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n'
        );
        std::cout << "Invalid input. Try again: ";
    }

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
    // int型：3回比較
    // ================================
    for (int i = 0; i < 3; i++) {
        ExecuteMin<int>("int");
    }

    // ================================
    // float型：3回比較
    // ================================
    for (int i = 0; i < 3; i++) {
        ExecuteMin<float>("float");
    }

    // ================================
    // double型：3回比較
    // ================================
    for (int i = 0; i < 3; i++) {
        ExecuteMin<double>("double");
    }

    std::cout
        << "\nMin Class Template End!"
        << std::endl;

    return 0;
}
