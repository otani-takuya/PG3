#include <iostream>

using namespace std;

// 一般的な賃金（時給）
const int kNormalWage = 1226;

// ================================
// 一般的な賃金体系
// ================================
long long NormalSalary(int hours) {

    // 時給 × 労働時間
    return static_cast<long long>(kNormalWage) * hours;
}

// ================================
// 再帰的な賃金体系
// 指定した時間の賃金を求める
// ================================
long long RecursiveWage(int hours) {

    // 再帰処理の終了条件
    // 1時間目の賃金は100円
    if (hours == 1) {
        return 100;
    }

    // 前の時間の賃金 × 2 - 50円
    // 自分自身の関数を呼び出して計算する
    return RecursiveWage(hours - 1) * 2 - 50;
}

// ================================
// 再帰的な賃金体系の合計金額
// ================================
long long RecursiveSalary(int hours) {

    // 再帰処理の終了条件
    if (hours == 1) {
        return 100;
    }

    // 前の時間までの合計金額に
    // 現在の時間の賃金を加算する
    return RecursiveSalary(hours - 1)
        + RecursiveWage(hours);
}

// ================================
// メイン関数
// ================================
int main() {

    // 労働時間
    int hours;

    // 労働時間を入力
    cout << "Enter working hours: ";
    cin >> hours;

    // 入力された労働時間を確認
    if (hours < 1 || hours > 50) {
        cout << "Please enter a value between 1 and 50." << endl;
        return 1;
    }

    // ================================
    // 問1
    // 2つの賃金体系を計算して比較する
    // ================================
    cout << "\n===== Question 1 =====" << endl;

    // 一般的な賃金体系の合計金額
    long long normal = NormalSalary(hours);

    // 再帰的な賃金体系の合計金額
    long long recursive = RecursiveSalary(hours);

    // 計算結果を表示
    cout << "Normal Salary: " << normal << " yen" << endl;
    cout << "Recursive Salary: " << recursive << " yen" << endl;

    // 2つの賃金体系を比較
    if (normal > recursive) {

        // 一般的な賃金体系の方が高い場合
        cout << "Normal Salary is higher." << endl;
    }
    else if (normal < recursive) {

        // 再帰的な賃金体系の方が高い場合
        cout << "Recursive Salary is higher." << endl;
    }
    else {

        // 2つの賃金体系が同じ場合
        cout << "Both salaries are equal." << endl;
    }

    // ================================
    // 問2
    // 再帰的な賃金体系の方が高くなる
    // 労働時間を求める
    // ================================
    cout << "\n===== Question 2 =====" << endl;

    // 1時間から50時間まで順番に計算する
    for (int i = 1; i <= 50; i++) {

        // 一般的な賃金体系の合計金額
        long long normalTotal = NormalSalary(i);

        // 再帰的な賃金体系の合計金額
        long long recursiveTotal = RecursiveSalary(i);

        // 再帰的な賃金体系の方が高いか確認
        if (recursiveTotal > normalTotal) {

            // 再帰的な賃金体系が高くなる時間を表示
            cout << "Recursive Salary becomes higher after "
                << i << " hours." << endl;

            // それぞれの合計金額を表示
            cout << "Normal Salary: "
                << normalTotal << " yen" << endl;

            cout << "Recursive Salary: "
                << recursiveTotal << " yen" << endl;

            // 条件を満たしたのでループを終了
            break;
        }
    }

    return 0;
}