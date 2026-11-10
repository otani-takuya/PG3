
#include <iostream>
#include <limits>

// ================================
// 基底クラス（抽象クラス）
// ================================
class IShape {
public:

    // 面積を求める純粋仮想関数
    virtual void Size() = 0;

    // 図形を描画する純粋仮想関数
    virtual void Draw() = 0;

    // 仮想デストラクタ
    virtual ~IShape() = default;
};

// ================================
// Circleクラス
// ================================
class Circle : public IShape {
public:

    // ================================
    // コンストラクタ
    // ================================
    Circle(int radius)
        : radius_(radius) {}

    // ================================
    // 円の面積を求める
    // ================================
    void Size() override {

        constexpr double kPi = 3.141592653589793;

        double area =
            kPi * radius_ * radius_;

        std::cout
            << "Circle Area: "
            << area
            << std::endl;
    }

    // ================================
    // 円をコンソールに描画する
    // ================================
    void Draw() override {

        std::cout << "\n[Circle]\n";

        // 縦横の座標を調べて円を描画
        for (int y = -radius_; y <= radius_; y++) {

            for (int x = -radius_; x <= radius_; x++) {

                // コンソールの文字の縦横比を補正
                double dx = x * 0.5;

                // 円の内側か判定
                if (dx * dx + y * y
                    <= radius_ * radius_) {

                    std::cout << "*";
                }
                else {

                    std::cout << " ";
                }
            }

            std::cout << std::endl;
        }
    }

private:

    // 円の半径
    int radius_ = 0;
};

// ================================
// Rectangleクラス
// ================================
class Rectangle : public IShape {
public:

    // ================================
    // コンストラクタ
    // ================================
    Rectangle(int width, int height)
        : width_(width),
        height_(height) {}

    // ================================
    // 長方形の面積を求める
    // ================================
    void Size() override {

        int area = width_ * height_;

        std::cout
            << "Rectangle Area: "
            << area
            << std::endl;
    }

    // ================================
    // 長方形をコンソールに描画する
    // ================================
    void Draw() override {

        std::cout << "\n[Rectangle]\n";

        // 高さの分だけ繰り返す
        for (int y = 0; y < height_; y++) {

            // 幅の分だけ繰り返す
            for (int x = 0; x < width_; x++) {

                std::cout << "* ";
            }

            std::cout << std::endl;
        }
    }

private:

    // 長方形の幅と高さ
    int width_ = 0;
    int height_ = 0;
};

// ================================
// 正の整数を入力する関数
// ================================
int InputPositiveInt(const char* message) {

    int value = 0;

    while (true) {

        std::cout << message;

        if (std::cin >> value && value > 0) {

            return value;
        }

        // 入力エラーを解除
        std::cin.clear();

        // 入力バッファをクリア
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );

        std::cout
            << "Invalid input. Try again.\n";
    }
}

// ================================
// 図形の処理を実行する関数
// ================================
void ExecuteShape(IShape* shape) {

    // ポインタが有効か確認
    if (shape == nullptr) {
        return;
    }

    // 面積を計算
    shape->Size();

    // 図形を描画
    shape->Draw();
}

// ================================
// メイン関数
// ================================
int main() {

    std::cout
        << "Shape Program Start!"
        << std::endl;

    // ================================
    // Circleの処理
    // ================================
    std::cout << "\n--- Circle ---\n";

    // 半径を入力
    int radius = InputPositiveInt(
        "Input radius: "
    );

    // Circleのインスタンス生成
    Circle circle(radius);

    // 基底クラスのポインタで管理
    IShape* circleShape = &circle;

    // 面積計算と描画
    ExecuteShape(circleShape);

    // ================================
    // Rectangleの処理
    // ================================
    std::cout << "\n--- Rectangle ---\n";

    // 幅と高さを入力
    int width = InputPositiveInt(
        "Input width: "
    );

    int height = InputPositiveInt(
        "Input height: "
    );

    // Rectangleのインスタンス生成
    Rectangle rectangle(width, height);

    // 基底クラスのポインタで管理
    IShape* rectangleShape = &rectangle;

    // 面積計算と描画
    ExecuteShape(rectangleShape);

    // ================================
    // 終了処理
    // ================================
    std::cout
        << "\nShape Program End!"
        << std::endl;

    return 0;
}
