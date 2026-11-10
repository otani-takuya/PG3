
#include <iostream>
#include <Windows.h>

// ================================
// Enemyクラス
// ================================
class Enemy {
public:

    // 敵の状態
    enum class State {
        Search, // 認識
        Shoot,  // 射撃
        Reload  // 再装填
    };

    // メンバ関数ポインタの型
    using StateFunction = void (Enemy::*)();

    // ================================
    // コンストラクタ
    // ================================
    Enemy() {
        state_ = State::Search;
        stateFunction_ = &Enemy::Search;
    }

    // ================================
    // 更新処理
    // ================================
    void Update() {

        // 現在の状態に対応する
        // メンバ関数を実行する
        (this->*stateFunction_)();
    }

private:

    // 現在の状態
    State state_;

    // 現在の状態処理を指す関数ポインタ
    StateFunction stateFunction_;

    // ================================
    // 状態変更
    // ================================
    void ChangeState(State nextState) {

        // 状態を変更
        state_ = nextState;

        // 状態に対応する関数を設定
        switch (state_) {

        case State::Search:
            stateFunction_ = &Enemy::Search;
            break;

        case State::Shoot:
            stateFunction_ = &Enemy::Shoot;
            break;

        case State::Reload:
            stateFunction_ = &Enemy::Reload;
            break;
        }
    }

    // ================================
    // 認識状態
    // ================================
    void Search() {

        std::cout
            << "[Search] Enemy is searching..."
            << std::endl;

        // 認識処理の待機
        Sleep(1000);

        std::cout
            << "Player detected!"
            << std::endl;

        // 射撃状態へ変更
        ChangeState(State::Shoot);
    }

    // ================================
    // 射撃状態
    // ================================
    void Shoot() {

        std::cout
            << "[Shoot] Enemy is shooting!"
            << std::endl;

        // 射撃処理の待機
        Sleep(1000);

        std::cout
            << "Ammo is empty!"
            << std::endl;

        // 再装填状態へ変更
        ChangeState(State::Reload);
    }

    // ================================
    // 再装填状態
    // ================================
    void Reload() {

        std::cout
            << "[Reload] Enemy is reloading..."
            << std::endl;

        // 再装填処理の待機
        Sleep(1000);

        std::cout
            << "Reload complete!"
            << std::endl;

        // 認識状態へ戻る
        ChangeState(State::Search);
    }
};

// ================================
// メイン関数
// ================================
int main() {

    // 敵を生成
    Enemy enemy;

    std::cout
        << "Enemy State Machine Start!"
        << std::endl;

    // 状態遷移を9回実行
    for (int i = 0; i < 9; i++) {

        std::cout
            << "\n--------------------"
            << std::endl;

        // 敵の更新
        enemy.Update();
    }

    std::cout
        << "\nEnemy State Machine End!"
        << std::endl;

    return 0;
}
