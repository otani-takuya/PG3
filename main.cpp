
#include <iostream>
#include <list>
#include <cstring>

// =========================================
// 駅一覧を表示する関数
// =========================================
void PrintStations(const std::list<const char*>& stations) {

    int number = 1;

    // listに登録されている駅を順番に表示
    for (const char* station : stations) {

        std::cout << "JY" << number
            << " : " << station << std::endl;

        number++;
    }

    std::cout << std::endl;
}

// =========================================
// 指定した駅の直後に新しい駅を追加する関数
// =========================================
bool InsertStationAfter(
    std::list<const char*>& stations,
    const char* targetStation,
    const char* newStation) {

    // listの先頭から駅を探索
    for (auto it = stations.begin(); it != stations.end(); ++it) {

        // 文字列の内容を比較
        if (std::strcmp(*it, targetStation) == 0) {

            // 指定した駅の次の位置へ移動
            ++it;

            // 新しい駅を挿入
            stations.insert(it, newStation);

            // 追加成功
            return true;
        }
    }

    // 対象の駅が見つからなかった場合
    return false;
}

int main() {

    // =========================================
    // 1970年の山手線（28駅）
    // =========================================

    std::list<const char*> stations = {
        "Tokyo",
        "Kanda",
        "Akihabara",
        "Okachimachi",
        "Ueno",
        "Uguisudani",
        "Nippori",
        "Tabata",
        "Komagome",
        "Sugamo",
        "Otsuka",
        "Ikebukuro",
        "Mejiro",
        "Takadanobaba",
        "Shin-Okubo",
        "Shinjuku",
        "Yoyogi",
        "Harajuku",
        "Shibuya",
        "Ebisu",
        "Meguro",
        "Gotanda",
        "Osaki",
        "Shinagawa",
        "Tamachi",
        "Hamamatsucho",
        "Shimbashi",
        "Yurakucho"
    };

    // =========================================
    // 1970年の山手線を表示
    // =========================================

    std::cout << "===== 1970 =====" << std::endl;

    PrintStations(stations);

    // =========================================
    // 1971年 西日暮里駅 開業
    // =========================================

    // 日暮里駅の直後に西日暮里駅を追加
    if (!InsertStationAfter(
        stations,
        "Nippori",
        "Nishi-Nippori")) {

        std::cerr << "西日暮里駅の追加に失敗しました。"
            << std::endl;

        return 1;
    }

    // =========================================
    // 2019年の山手線を表示
    // =========================================

    std::cout << "===== 2019 =====" << std::endl;

    PrintStations(stations);

    // =========================================
    // 2020年 高輪ゲートウェイ駅 開業
    // =========================================

    // 品川駅の直後に高輪ゲートウェイ駅を追加
    if (!InsertStationAfter(
        stations,
        "Shinagawa",
        "Takanawa Gateway")) {

        std::cerr << "高輪ゲートウェイ駅の追加に失敗しました。"
            << std::endl;

        return 1;
    }

    // =========================================
    // 2022年の山手線を表示
    // =========================================

    std::cout << "===== 2022 =====" << std::endl;

    PrintStations(stations);

    return 0;
}
