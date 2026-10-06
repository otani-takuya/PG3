#include <iostream>
#include <list>
#include <string>

using namespace std;

// 駅一覧を表示する関数
void PrintStations(const list<string>& stations) {

	int number = 1;

	for (const string& station : stations) {
		cout << "JY" << number << " : " << station << endl;
		number++;
	}

	cout << endl;
}

int main() {

	// =========================================
	// 1970年の山手線
	// =========================================

	list<string> stations = {
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

	cout << "===== 1970 =====" << endl;

	PrintStations(stations);


	// =========================================
	// 西日暮里駅追加
	// =========================================

	auto nippori = stations.begin();

	while (nippori != stations.end()) {

		if (*nippori == "Nippori") {
			nippori++;

			stations.insert(nippori, "Nishi-Nippori");

			break;
		}

		nippori++;
	}


	// =========================================
	// 2019年の山手線
	// =========================================

	cout << "===== 2019 =====" << endl;

	PrintStations(stations);


	// =========================================
	// 高輪ゲートウェイ駅追加
	// =========================================

	auto shinagawa = stations.begin();

	while (shinagawa != stations.end()) {

		if (*shinagawa == "Shinagawa") {
			shinagawa++;

			stations.insert(shinagawa, "Takanawa Gateway");

			break;
		}

		shinagawa++;
	}


	// =========================================
	// 2022年の山手線
	// =========================================

	cout << "===== 2022 =====" << endl;

	PrintStations(stations);

	return 0;
}