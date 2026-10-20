
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <Windows.h>

// ================================
// 関数の宣言
// ================================

// 遅延実行する関数
void DelayReveal(
    void (*fn)(int, int),
    unsigned int delayMs,
    int roll,
    int userGuess
);

// ================================
// メイン関数
// ================================
int main() {

    // ================================
    // 乱数の初期化
    // ================================

    srand(static_cast<unsigned int>(time(nullptr)));

    // サイコロの出目を生成（1～6）
    int roll = rand() % 6 + 1;

    // ユーザーの予想
    int userGuess = 0;

    // ================================
    // ユーザー入力
    // ================================

    std::cout << "Guess the dice result!" << std::endl;
    std::cout << "Odd  (1)" << std::endl;
    std::cout << "Even (0)" << std::endl;

    // 正しい値が入力されるまで繰り返す
    while (true) {

        std::cout << "Enter your guess (1 or 0): ";

        // 入力値を取得
        int inputResult = scanf_s("%d", &userGuess);

        // 数値以外が入力された場合
        if (inputResult != 1) {

            std::cout << "Invalid input!" << std::endl;

            // 入力バッファをクリア
            int ch = 0;

            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            if (ch == EOF) {
                return 1;
            }

            continue;
        }

        // 1 または 0 なら入力完了
        if (userGuess == 1 || userGuess == 0) {
            break;
        }

        // 不正な値の場合
        std::cout << "Please enter 1 or 0." << std::endl;
    }

    // ================================
    // ラムダ式で結果表示処理を定義
    // ================================

    auto showResult = [](int roll, int userGuess) {

        // サイコロの出目を表示
        std::cout << "\nDice result: " << roll << std::endl;

        // 奇数なら1、偶数なら0
        int result = roll % 2;

        // 正解判定
        if (result == userGuess) {

            std::cout << "Correct!" << std::endl;

        }
        else {

            std::cout << "Incorrect!" << std::endl;
        }
        };

    // ================================
    // 3秒後に結果を表示
    // ================================

    std::cout << "\nRolling the dice..." << std::endl;

    // ラムダ式をコールバック関数として渡す
    DelayReveal(
        showResult,
        3000,
        roll,
        userGuess
    );

    return 0;
}

// ================================
// 遅延実行関数
// ================================
void DelayReveal(
    void (*fn)(int, int),
    unsigned int delayMs,
    int roll,
    int userGuess
) {

    // 指定された時間だけ待機
    Sleep(delayMs);

    // コールバック関数を呼び出す
    fn(roll, userGuess);
}
