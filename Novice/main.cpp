#include <Novice.h>
#include <cstdlib>
#include <cstring>
#include <math.h>



struct Vector2 {
	float x;
	float y;
};


bool IsHitByCircle(float aPosx, float aPosy, float aRadius, float bPosx, float bPosy, float bRadius)
{
	float dx = bPosx - aPosx;
	float dy = bPosy - aPosy;
	float distance = sqrtf(dx * dx + dy * dy);
	float totalRadius = aRadius + bRadius;

	return distance <= totalRadius;
}




// プレイヤー（ペンギン）構造体
struct Player {
	Vector2 pos;
	Vector2 velocity;
	float width, height;
	float speed;
	float stamina;
	bool isAlive;
	bool isFocus;
	int textureHandle;
	float radius;
};

struct Bullet {
	Vector2 pos;
	float speed;
	bool isShot;
	float width;
	float height;
	int textureHandle;
	float radius;
};

struct AzarasiBullet {
	Vector2 pos;
	float speed;
	float width;
	float height;
	bool isShot;
	int textureHandle;
	float radius;
};

struct SirokumaBullet {
	Vector2 pos;
	Vector2 velocity;
	float speed;
	float width;
	float height;
	bool isShot;
	int textureHandle;
	float radius;
};

// エネミー構造体
struct Azarasi {
	Vector2 pos;
	float speed;
	float width;
	float height;
	bool isAlive;
	int textureHandles[4]; //4フレーム分の画像
	int respawnTimer;
	bool moveLeft;
	bool dropFish;
	float radius;
};


// エネミー構造体
struct Syati {
	Vector2 pos;
	float speed;
	float width;
	float height;
	bool isAlive;
	int textureHandle;
	int respawnTimer;
	float radius;
};

// エネミー構造体
struct Sirokuma {
	Vector2 pos;
	float speed;
	float width;
	float height;
	bool isAlive;
	int textureHandle;
	int respawnTimer;
	float radius;
	bool dropFish;
	float hitCount;
};

struct Fish {
	Vector2 pos;
	Vector2 velocity;
	int textureHandle;
	float radius;
	bool isActive;
};

struct Explosion {
	Vector2 pos;
	int frame;
	bool isActive;
	int textureHandle[6];
};

enum Scene {
	SCENE_TITLE,
	SCENE_SOUSA,
	SCENE_SETUMEI,
	SCENE_GAME_PLAY,
	SCENE_CLEAR,
};


struct BG
{
	Vector2 pos;
};




const char kWindowTitle[] = "LC1B_07_オオタニ_タクヤ_AL1_評価課題1_どこまで滑れる？ぺんぎんくん！";



#include "GameManager.h"
#include "TitleScene.h"
#include "SousaScene.h"
#include "SetumeiScene.h"
#include "GameScene.h"
#include "ClearScene.h"
#include <memory>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Novice::Initialize(kWindowTitle, 1280, 720);
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };


	// 変数の宣言と初期化
	Player penguin;
	penguin.pos.x = 300.0f;
	penguin.pos.y = 500.0f;
	penguin.velocity.x = 0.0f;
	penguin.velocity.y = 0.0f;
	penguin.width = 64.0f;
	penguin.height = 64.0f;
	penguin.speed = 5.0f;
	penguin.stamina = 100.0f;
	penguin.isAlive = true;
	penguin.isFocus = false;
	penguin.textureHandle = Novice::LoadTexture("./Resources/images/penguin1.png");
	penguin.radius = 30.0;
	bool isGameOver = false;





	const int kBulletMax = 10;
	const int bulletTexture = Novice::LoadTexture("./Resources/images/bullet.png");
	Bullet bullet[kBulletMax];

	for (int i = 0; i < kBulletMax; i++)
	{
		bullet[i].pos.x = 0.0f;
		bullet[i].pos.y = 0.0f;
		bullet[i].speed = 10.0f;
		bullet[i].isShot = false;
		bullet[i].width = 16.0f;
		bullet[i].height = 16.0f;
		bullet[i].textureHandle = bulletTexture;
		bullet[i].radius = 64.0f;

	}


	const int kAzarasiBulletMax = 50;
	const int azarasibulletTexture = Novice::LoadTexture("./Resources/images/azarasi.bullet.png");
	AzarasiBullet azarasibullet[kAzarasiBulletMax];

	for (int i = 0; i < kAzarasiBulletMax; i++)
	{
		azarasibullet[i].pos.x = 0.0f;
		azarasibullet[i].pos.y = 0.0f;
		azarasibullet[i].speed = 10.0f;
		azarasibullet[i].isShot = false;
		azarasibullet[i].width = 16.0f;
		azarasibullet[i].height = 16.0f;
		azarasibullet[i].textureHandle = azarasibulletTexture;
		azarasibullet[i].radius = 20.0f;

	}



	const int kSirokumaBulletMax = 100;
	const int sirokumabulletTexture = Novice::LoadTexture("./Resources/images/sirokuma.bullet2.png");
	SirokumaBullet sirokumabullet[kSirokumaBulletMax];

	for (int i = 0; i < kSirokumaBulletMax; i++)
	{
		sirokumabullet[i].pos.x = 0.0f;
		sirokumabullet[i].pos.y = 0.0f;
		sirokumabullet[i].velocity.x = 0.0f;
		sirokumabullet[i].velocity.y = 0.0f;
		sirokumabullet[i].speed = 10.0f;
		sirokumabullet[i].isShot = false;
		sirokumabullet[i].width = 16.0f;
		sirokumabullet[i].height = 16.0f;
		sirokumabullet[i].textureHandle = sirokumabulletTexture;
		sirokumabullet[i].radius = 20.0f;
	}

	const int kAzarasiMax = 10;
	;
	Azarasi azarasi[kAzarasiMax];

	int activeAzarasiCount = 2; // はじめは1体から開始

	for (int i = 0; i < kAzarasiMax; i++)
	{
		float spacing = 200.0f;       // アザラシの間隔

		float startX = 800.0f;        // 右から開始位置（必要なら調整）

		azarasi[i].speed = 5.0f;
		azarasi[i].width = 64.0f;
		azarasi[i].height = 64.0f;
		azarasi[i].isAlive = false;
		azarasi[i].textureHandles[0] = Novice::LoadTexture("./Resources/images/azarasi1.png");
		azarasi[i].textureHandles[1] = Novice::LoadTexture("./Resources/images/azarasi2.png");
		azarasi[i].textureHandles[2] = Novice::LoadTexture("./Resources/images/azarasi3.png");
		azarasi[i].textureHandles[3] = Novice::LoadTexture("./Resources/images/azarasi4.png");
		azarasi[i].respawnTimer = 0;
		azarasi[i].dropFish = false;
		azarasi[i].radius = 32.0f;

		azarasi[i].moveLeft = (rand() % 2 == 0);  // 50%の確率で左右を振り分け

		if (azarasi[i].moveLeft) {
			azarasi[i].pos.x = startX + i * spacing;  // 右から
		}
		else {
			azarasi[i].pos.x = 0.0f;  // 左から
		}

		azarasi[i].pos.y = 100.0f;

	}

	const int kSyatiMax = 10; // 最終的に最大5体出るようにする例
	Syati syati[kSyatiMax];

	int activeSyatiCount = 1; // はじめは1体から開始

	for (int i = 0; i < kSyatiMax; i++)
	{
		syati[i].pos.x = 200.0f;
		syati[i].pos.y = -200.0f;
		syati[i].speed = 5.0f;
		syati[i].width = 64.0f;
		syati[i].height = 64.0f;
		syati[i].isAlive = false;
		syati[i].textureHandle = Novice::LoadTexture("./Resources/images/syati.png");
		syati[i].respawnTimer = 50;
		syati[i].radius = 32.0f;
	}



	Sirokuma sirokuma;
	sirokuma.pos.x = 400.0f;
	sirokuma.pos.y = -200.0f;
	sirokuma.speed = 5.0f;
	sirokuma.width = 64.0f;
	sirokuma.height = 64.0f;
	sirokuma.isAlive = false;
	sirokuma.textureHandle = Novice::LoadTexture("./Resources/images/sirokuma.png");
	sirokuma.respawnTimer = 600;
	sirokuma.radius = 64.0f;
	sirokuma.dropFish = false;
	sirokuma.hitCount = 0;

	int sirokumaKillCount = 0;




	const int kFishMax = 10000;
	const int fishTexture = Novice::LoadTexture("./Resources/images/fish2.png");
	Fish fish[kFishMax];

	for (int i = 0; i < kFishMax; i++)
	{
		fish[i].pos.x = 0.0f;
		fish[i].pos.y = 0.0f;
		fish[i].textureHandle = fishTexture;
		fish[i].radius = 25.0f;
		fish[i].isActive = false;
	}

	const int kExplosionMax = 10000;
	int explosionTextures[6] = {};
	for (int i = 0; i < 6; ++i) {
		char path[128];
		sprintf_s(path, "./Resources/images/bakuhatu%d.png", i + 1);
		explosionTextures[i] = Novice::LoadTexture(path);
	}
	Explosion explosions[kExplosionMax];

	for (int i = 0; i < kExplosionMax; i++)
	{
		explosions[i].pos.x = 0.0f;
		explosions[i].pos.y = 0.0f;
		explosions[i].frame = 0;
		explosions[i].textureHandle[0] = explosionTextures[0];
		explosions[i].textureHandle[1] = explosionTextures[1];
		explosions[i].textureHandle[2] = explosionTextures[2];
		explosions[i].textureHandle[3] = explosionTextures[3];
		explosions[i].textureHandle[4] = explosionTextures[4];
		explosions[i].textureHandle[5] = explosionTextures[5];
		explosions[i].isActive = false;
	}


	BG bg;
	bg.pos.x = 100.0f;
	bg.pos.y = 30.0f;

	int GHBG = Novice::LoadTexture("./Resources/images/haikei2.png");
	int GHBGS = Novice::LoadTexture("./Resources/images/sotogawa.png");


	int GHBGD = Novice::LoadTexture("./Resources/images/batteri-.png");

	int GHBGTL = Novice::LoadTexture("./Resources/images/TITLEHAIKEI1.png");
	int GHBGSO = Novice::LoadTexture("./Resources/images/SOUSAHAIKEI1.png");
	int GHBGSE = Novice::LoadTexture("./Resources/images/SETUMEIHAIKEI1.png");
	int GHBGRE = Novice::LoadTexture("./Resources/images/resarutoHAIKEI2.png");
	int GHBGEN = Novice::LoadTexture("./Resources/images/ENDHAIKEI.png");

	float batterix = 757.0f;
	float batteriy = 168.0f;

	//フレームタイマー
	int frameCount = 0;

	int gameTimer10 = 0;
	int gameTimer100 = 0;
	int gameTimer1000 = 0;
	//int gameTimer10000 = 0;
	int gameTimer = 0;

	bool kuriage1 = false;
	bool kuriage2 = false;
	bool kuriage3 = false;




	int targetNumber = 0;
	int targetNumber10 = 0;
	int targetNumber100 = 0;

	//================================================================
	// 変数と初期値
	//================================================================

	int graphHandleNumber[10];

	graphHandleNumber[0] = Novice::LoadTexture("./Resources/images/0.png");
	graphHandleNumber[1] = Novice::LoadTexture("./Resources/images/1.png");
	graphHandleNumber[2] = Novice::LoadTexture("./Resources/images/2.png");
	graphHandleNumber[3] = Novice::LoadTexture("./Resources/images/3.png");
	graphHandleNumber[4] = Novice::LoadTexture("./Resources/images/4.png");
	graphHandleNumber[5] = Novice::LoadTexture("./Resources/images/5.png");
	graphHandleNumber[6] = Novice::LoadTexture("./Resources/images/6.png");
	graphHandleNumber[7] = Novice::LoadTexture("./Resources/images/7.png");
	graphHandleNumber[8] = Novice::LoadTexture("./Resources/images/8.png");
	graphHandleNumber[9] = Novice::LoadTexture("./Resources/images/9.png");



	int seShoot = Novice::LoadAudio("./Resources/sound/shoot.mp3");   // 弾を撃つ音
	int seHit = Novice::LoadAudio("./Resources/sound/hit.mp3");     // 弾が当たる音
	int seDamage = Novice::LoadAudio("./Resources/sound/damage.mp3");  // 攻撃を受けた音
	int seHeal = Novice::LoadAudio("./Resources/sound/heal.mp3");    // 回復したとき
	int seGameOver = Novice::LoadAudio("./Resources/sound/batan.mp3"); // やられSE


	int playHandle = 0;

	int bgmHandle = Novice::LoadAudio("./Resources/sound/gameBGM.mp3");





	GameManager manager;
	manager.Register(SceneType::Title, std::make_unique<TitleScene>([&]() {

		if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
		{
			//Novice::StopAudio(playHandle);

			manager.ChangeScene(SceneType::Game);
			return;
		}

		if (!preKeys[DIK_S] && keys[DIK_S])
		{
			//Novice::StopAudio(playHandle);

			manager.ChangeScene(SceneType::Sousa);
			return;
		}

		if (!Novice::IsPlayingAudio(playHandle))
		{
			playHandle = Novice::PlayAudio(bgmHandle, true, 0.2f);
		}

		//描画処理

		Novice::DrawSprite(
			0,
			0,
			GHBGTL,
			1.0f, 1.0f, 0.0f, WHITE


		);

		}));
	manager.Register(SceneType::Sousa, std::make_unique<SousaScene>([&]() {

		if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
		{
			//Novice::StopAudio(playHandle);

			manager.ChangeScene(SceneType::Setumei);
			return;
		}

		if (!Novice::IsPlayingAudio(playHandle))
		{
			playHandle = Novice::PlayAudio(bgmHandle, true, 0.2f);
		}

		//描画処理


		Novice::DrawSprite(
			0,
			0,
			GHBGSO,
			1.0f, 1.0f, 0.0f, WHITE

		);

		}));
	manager.Register(SceneType::Setumei, std::make_unique<SetumeiScene>([&]() {

		if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
		{


			manager.ChangeScene(SceneType::Title);
			return;
		}

		if (!Novice::IsPlayingAudio(playHandle))
		{
			playHandle = Novice::PlayAudio(bgmHandle, true, 0.2f);
		}


		//描画処理


		Novice::DrawSprite(
			0,
			0,
			GHBGSE,
			1.0f, 1.0f, 0.0f, WHITE

		);

		}));
	manager.Register(SceneType::Game, std::make_unique<GameScene>([&]() {

		if (!penguin.isAlive)
		{
			Novice::StopAudio(playHandle);

			if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
			{

				Novice::StopAudio(playHandle);

				manager.ChangeScene(SceneType::Clear);
				return;
			}

		}

		if (!Novice::IsPlayingAudio(playHandle))
		{
			playHandle = Novice::PlayAudio(bgmHandle, true, 0.2f);
		}


		bg.pos.y += penguin.speed;

		if (bg.pos.y >= 810.0f)
		{
			bg.pos.y = 30.0f;
		}

		Novice::DrawSprite(
			static_cast<int>(bg.pos.x),
			static_cast<int>(bg.pos.y),
			GHBG,
			1.0f, 1.5f, 0.0f, WHITE

		);

		Novice::DrawSprite(
			static_cast<int>(bg.pos.x),
			static_cast<int>(bg.pos.y - 780.0f),
			GHBG,
			1.0f, 1.5f, 0.0f, WHITE

		);


		if (penguin.isAlive)
		{
			penguin.velocity.x = 0.0f;
			penguin.velocity.y = 0.0f;

			if (keys[DIK_W])
			{
				penguin.velocity.y = -1.0f;
			}
			if (keys[DIK_S])
			{
				penguin.velocity.y = 1.0f;
			}
			if (keys[DIK_A])
			{
				penguin.velocity.x = -1.0f;
			}
			if (keys[DIK_D])
			{
				penguin.velocity.x = 1.0f;
			}

			float length = sqrtf(penguin.velocity.x * penguin.velocity.x + penguin.velocity.y * penguin.velocity.y);

			if (length != 0.0f)
			{
				penguin.velocity.x = penguin.velocity.x / length * penguin.speed;
				penguin.velocity.y = penguin.velocity.y / length * penguin.speed;
			}

			// 位置更新
			penguin.pos.x += penguin.velocity.x;
			penguin.pos.y += penguin.velocity.y;

			// 範囲制限（壁にぶつからないように）
			if (penguin.pos.x < 100.0f)
			{
				penguin.pos.x = 100.0f;
			}

			if (penguin.pos.x > 600.0f)
			{
				penguin.pos.x = 600.0f;
			}

			if (penguin.pos.y < 30.0f)
			{
				penguin.pos.y = 30.0f;
			}

			if (penguin.pos.y > 550.0f)
			{
				penguin.pos.y = 550.0f;
			}




			//弾の発射の処理
			if (!preKeys[DIK_SPACE] && keys[DIK_SPACE])
			{
				for (int i = 0; i < kBulletMax; i++)
				{
					if (!bullet[i].isShot)
					{
						bullet[i].pos.x = penguin.pos.x + penguin.width / 2 - bullet[i].width / 2;
						bullet[i].pos.y = penguin.pos.y;
						bullet[i].isShot = true;
						Novice::PlayAudio(seShoot, false, 0.2f);

						break;
					}
				}
			}


			for (int i = 0; i < kBulletMax; i++)
			{
				//弾の移動
				if (bullet[i].isShot)
				{
					bullet[i].pos.y -= bullet[i].speed;

					//弾が画面外に行ったとき
					if (bullet[i].pos.y <= 0.0f)
					{
						bullet[i].isShot = false;
					}

					Novice::DrawSprite(
						(int)bullet[i].pos.x - 20,

						(int)bullet[i].pos.y,
						bullet[i].textureHandle,
						1.0f, 1.0f, 0.0f, WHITE
					);



				}
			}


			Novice::DrawSprite(
				(int)penguin.pos.x,
				(int)penguin.pos.y,
				penguin.textureHandle,
				1.0f, 1.0f, 0.0f, WHITE
			);


		}


		//アザラシ
		for (int i = 0; i < activeAzarasiCount; i++) {
			if (azarasi[i].isAlive)
			{
				if (azarasi[i].moveLeft)
				{
					azarasi[i].pos.x -= azarasi[i].speed;

					// 左端を越えたら退場
					if (azarasi[i].pos.x + azarasi[i].width < 0)
					{
						azarasi[i].isAlive = false;
						azarasi[i].respawnTimer = rand() % 600;
					}
				}
				else
				{
					azarasi[i].pos.x += azarasi[i].speed;

					// 右端を越えたら退場
					if (azarasi[i].pos.x > 800.0f)
					{
						azarasi[i].isAlive = false;
						azarasi[i].respawnTimer = rand() % 600;
					}
				}



				// 弾を撃つ
				if (frameCount == rand() % 61) {
					for (int j = 0; j < kAzarasiBulletMax; j++) {

						if (!azarasibullet[j].isShot) {
							azarasibullet[j].isShot = true;
							azarasibullet[j].pos.x = azarasi[i].pos.x + azarasi[i].width / 2;
							azarasibullet[j].pos.y = azarasi[i].pos.y + azarasi[i].height;
							azarasibullet[j].speed = 5.0f;
							break;
						}
					}
				}
			}
			else
			{
				// リスポーン処理
				azarasi[i].respawnTimer--;
				if (azarasi[i].respawnTimer <= 0) {
					azarasi[i].isAlive = true;
					azarasi[i].moveLeft = (rand() % 2 == 0);
					if (azarasi[i].moveLeft)
					{
						azarasi[i].pos.x = 800.0f;
					}
					else {
						azarasi[i].pos.x = 0.0f;
					}

					azarasi[i].pos.y = 100.0f + rand() % 171 + 30;
				}
			}

			if (azarasibullet[i].isShot)
			{
				azarasibullet[i].pos.y += azarasibullet[i].speed;

				if (azarasibullet[i].pos.y > 720.0f)
				{
					azarasibullet[i].isShot = false;
				}

				Novice::DrawSprite(
					(int)azarasibullet[i].pos.x - 20,
					(int)azarasibullet[i].pos.y,
					azarasibullet[i].textureHandle,
					1.0f, 1.0f, 0.0f, WHITE
				);


			}

			//描画

			if (azarasi[i].isAlive) {

				Novice::DrawSprite(
					static_cast<int>(azarasi[i].pos.x),
					static_cast<int>(azarasi[i].pos.y),
					azarasi[i].textureHandles[(frameCount / 15) % 4],
					1.0f, 1.0f, 0.0f, WHITE
				);



			}

		}

		if (penguin.stamina <= 0 && penguin.isAlive) {
			penguin.isAlive = false;

			Novice::PlayAudio(seGameOver, false, 1.0f);  // SE再生！
		}




		//シャチ

		for (int i = 0; i < activeSyatiCount; i++)
		{
			if (!syati[i].isAlive) {
				syati[i].respawnTimer--;
				if (syati[i].respawnTimer <= 0) {
					syati[i].isAlive = true;
					syati[i].pos.x = 200.0f + rand() % 500;  // 出現X位置ランダム
					syati[i].pos.y = -64.0f;                // 画面上から登場
					syati[i].speed = 1.0f + rand() % 10;
				}
			}

			if (syati[i].isAlive) {
				syati[i].pos.y += syati[i].speed;

				// S字軌道：X座標をsin波で変動
				float amplitude = 400.0f;  // 揺れの幅（左右への振れ幅）
				float frequency = 30.0f;  // 波の周期（小さいと速く曲がる）

				syati[i].pos.x += sinf((float)syati[i].pos.y / frequency) * amplitude * 0.05f;



				// 画面外に出たら非表示＆次の登場準備
				if (syati[i].pos.y > 720.0f) {
					syati[i].isAlive = false;
					syati[i].respawnTimer = rand() % 600;
				}

				// 描画
				Novice::DrawSprite(
					(int)syati[i].pos.x,
					(int)syati[i].pos.y,
					syati[i].textureHandle,
					1.0f, 1.0f, 0.0f, WHITE
				);

			}
		}



		//シロクマ
		if (!sirokuma.isAlive) {
			sirokuma.respawnTimer--;
			if (sirokuma.respawnTimer <= 0) {
				sirokuma.isAlive = true;
				sirokuma.pos.x = 100.0f + rand() % 401;  // ランダム登場位置
				sirokuma.pos.y = 50.0f;
				sirokuma.speed = 3.0f;
			}
		}
		else
		{
			// 左右移動（反射）
			sirokuma.pos.x += sirokuma.speed;

			if (sirokuma.pos.x < 100.0f || sirokuma.pos.x + sirokuma.width > 650.0f) {
				sirokuma.speed *= -1.0f;
			}

			// 全体に散らばる弾（ランダム方向）
			if (frameCount % 90 == 0) {
				for (int i = 0; i < kSirokumaBulletMax; i++) {
					if (!sirokumabullet[i].isShot) {
						float angle = (float)(rand() % 360) * (3.14159f / 180.0f);
						sirokumabullet[i].isShot = true;
						sirokumabullet[i].pos = { sirokuma.pos.x + sirokuma.width / 2, sirokuma.pos.y + sirokuma.height };
						sirokumabullet[i].velocity = {
							cosf(angle) * sirokumabullet[i].speed,
							sinf(angle) * sirokumabullet[i].speed
						};
						break;
					}
				}
			}


			// 軽くプレイヤーを追尾する弾
			if (frameCount % 120 == 0) {
				for (int i = 0; i < kSirokumaBulletMax; i++) {
					if (!sirokumabullet[i].isShot) {
						Vector2 toPlayer = {
							penguin.pos.x - sirokuma.pos.x,
							penguin.pos.y - sirokuma.pos.y
						};
						float len = sqrtf(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
						toPlayer.x /= len;
						toPlayer.y /= len;

						sirokumabullet[i].isShot = true;
						sirokumabullet[i].pos = { sirokuma.pos.x + sirokuma.width / 2, sirokuma.pos.y + sirokuma.height };
						sirokumabullet[i].velocity = {
							toPlayer.x * sirokumabullet[i].speed,
							toPlayer.y * sirokumabullet[i].speed
						};
						break;
					}
				}
			}
		}

		for (int i = 0; i < kSirokumaBulletMax; i++) {
			if (sirokumabullet[i].isShot) {
				sirokumabullet[i].pos.x += sirokumabullet[i].velocity.x;
				sirokumabullet[i].pos.y += sirokumabullet[i].velocity.y;

				// 画面外で消去
				if (sirokumabullet[i].pos.x < 0 || sirokumabullet[i].pos.x >= 800 ||
					sirokumabullet[i].pos.y < 0 || sirokumabullet[i].pos.y >= 720)
				{
					sirokumabullet[i].isShot = false;
				}

				Novice::DrawSprite(
					(int)sirokumabullet[i].pos.x,
					(int)sirokumabullet[i].pos.y,
					sirokumabullet[i].textureHandle,
					1.0f, 1.0f, 0.0f, WHITE
				);


			}
		}

		if (sirokuma.isAlive) {
			Novice::DrawSprite(
				static_cast<int>(sirokuma.pos.x),
				static_cast<int>(sirokuma.pos.y),
				sirokuma.textureHandle,
				1.0f, 1.0f, 0.0f, WHITE
			);


		}





		if (penguin.isAlive)
		{
			frameCount++;

			if (frameCount >= 60)
			{
				frameCount = 0;
			}

			gameTimer++;

			if (gameTimer == 600)
			{
				activeAzarasiCount = 3;
			}

			if (gameTimer == 1200)
			{
				activeSyatiCount = 2;
				activeAzarasiCount = 4;
			}

			if (gameTimer == 2400)
			{
				activeSyatiCount = 3;
				activeAzarasiCount = 5;
			}

			if (gameTimer == 3600)
			{
				activeSyatiCount = 4;
				activeAzarasiCount = 6;
			}

			if (gameTimer == 4800)
			{
				activeSyatiCount = 5;
				activeAzarasiCount = 7;
			}

			if (gameTimer == 6000)
			{
				activeSyatiCount = 6;
				activeAzarasiCount = 8;
			}

			if (gameTimer == 6000)
			{
				activeSyatiCount = 7;
				activeAzarasiCount = 9;
			}

			if (gameTimer == 7200)
			{
				activeSyatiCount = 8;
				activeAzarasiCount = 10;
			}

			if (gameTimer == 8400)
			{
				activeSyatiCount = 9;
				activeAzarasiCount = 10;
			}

			if (gameTimer == 9600)
			{
				activeSyatiCount = 10;
				activeAzarasiCount = 10;
			}

			gameTimer10++;

			if (gameTimer10 >= 600)
			{
				kuriage1 = true;
				gameTimer10 = 0;
			}

			gameTimer100++;
			if (gameTimer100 >= 6000)
			{
				kuriage2 = true;
				gameTimer10 = 0;
				gameTimer100 = 0;
			}

			gameTimer1000++;
			if (gameTimer1000 >= 60000)
			{
				kuriage3 = true;
				gameTimer10 = 0;
				gameTimer100 = 0;
				gameTimer1000 = 0;
			}
			/*
			gameTimer10000++;
			if (gameTimer1000 >= 600000)
			{
				gameTimer10 = 540;
				gameTimer100 = 5400;
				gameTimer1000 = 54000;
				gameTimer10000 = 540000;
			}
			*/
		}


		//当たり判定

		if (penguin.isAlive)
		{
			//玉とアザラシ
			for (int i = 0; i < kAzarasiMax; i++) {
				if (azarasi[i].isAlive) {
					for (int j = 0; j < kBulletMax; j++) {
						if (bullet[j].isShot)
						{
							if (IsHitByCircle(bullet[j].pos.x + 42, bullet[j].pos.y + 60, bullet[j].radius, azarasi[i].pos.x + 45, azarasi[i].pos.y + 70, azarasi[i].radius))
							{
								for (int e = 0; e < kExplosionMax; e++) {
									if (!explosions[e].isActive) {
										explosions[e].isActive = true;
										explosions[e].pos = bullet[j].pos;
										break;
									}
								}

								// 当たり！アザラシ撃破！
								azarasi[i].isAlive = false;
								azarasi[i].dropFish = true;
								bullet[j].isShot = false;
								azarasi[i].respawnTimer = rand() % 600;
								Novice::PlayAudio(seHit, false, 0.3f);


								// 魚を生成する処理をここにしっかり入れる
								for (int f = 0; f < kFishMax; f++) {
									if (!fish[f].isActive) {
										fish[f].isActive = true;
										fish[f].pos = {
											azarasi[i].pos.x + 45,
											azarasi[i].pos.y + 70
										};
										fish[f].velocity = { 0.0f, 2.5f };
										fish[f].radius = 25.0f;
										fish[f].textureHandle = fishTexture;
										break;
									}
								}
							}


						}
					}
				}

			}

			for (int i = 0; i < kExplosionMax; i++) {
				if (explosions[i].isActive) {
					Novice::DrawSprite(
						static_cast<int>(explosions[i].pos.x),
						static_cast<int>(explosions[i].pos.y - 50),
						explosions[i].textureHandle[explosions[i].frame / 10],
						1.0f, 1.0f, 0.0f, WHITE
					);
					explosions[i].frame++;

					if (explosions[i].frame > 50) {
						explosions[i].isActive = false;
						explosions[i].frame = 0;
					}

				}
			}


			for (int f = 0; f < kFishMax; f++) {
				if (fish[f].isActive) {
					// 位置更新
					fish[f].pos.x += fish[f].velocity.x;
					fish[f].pos.y += fish[f].velocity.y;

					// 当たり判定（回復）
					if (IsHitByCircle(penguin.pos.x + 65, penguin.pos.y + 60, penguin.radius, fish[f].pos.x + 30, fish[f].pos.y + 30, fish[f].radius))
					{
						penguin.stamina += 20;
						if (penguin.stamina > 100) penguin.stamina = 100;
						fish[f].isActive = false;
						Novice::PlayAudio(seHeal, false, 0.2f);
					}

					// 表示
					Novice::DrawSprite(
						(int)fish[f].pos.x, (int)fish[f].pos.y,
						fish[f].textureHandle, 1.0f, 1.0f, 0.0f, WHITE
					);
				}
			}

			//アザラシと自機

			for (int i = 0; i < kAzarasiMax; i++)
			{
				if (azarasi[i].isAlive)
				{
					if (IsHitByCircle(penguin.pos.x + 64, penguin.pos.y + 60, penguin.radius, azarasi[i].pos.x + 45, azarasi[i].pos.y + 70, azarasi[i].radius))
					{
						penguin.stamina -= 20;
						azarasi[i].isAlive = false;
						Novice::PlayAudio(seDamage, false, 1.0f);

						if (penguin.stamina <= 0)
						{
							penguin.isAlive = false;
							isGameOver = true;
						}
					}
				}
			}


			//アザラシ玉と自機
			for (int i = 0; i < kAzarasiBulletMax; i++) {
				if (azarasibullet[i].isShot) {

					if (IsHitByCircle(penguin.pos.x + 65, penguin.pos.y + 60, penguin.radius, azarasibullet[i].pos.x + 10, azarasibullet[i].pos.y + 35, azarasibullet[i].radius))
					{
						penguin.stamina -= 10;
						azarasibullet[i].isShot = false;
						Novice::PlayAudio(seDamage, false, 1.0f);


						if (penguin.stamina <= 0)
						{
							penguin.isAlive = false;
							isGameOver = true;
						}
					}
				}
			}


			//シャチと自機
			for (int i = 0; i < kSyatiMax; i++)
			{
				if (syati[i].isAlive && penguin.isAlive) {
					if (IsHitByCircle(penguin.pos.x + 65, penguin.pos.y + 60, penguin.radius, syati[i].pos.x + 63, syati[i].pos.y + 50, syati[i].radius)) {
						penguin.stamina -= 30;
						syati[i].isAlive = false;
						Novice::PlayAudio(seDamage, false, 1.0f);

						if (penguin.stamina <= 0) {

							penguin.isAlive = false;
							isGameOver = true;
						}
					}
				}
			}


			//シロクマと玉

			for (int i = 0; i < kBulletMax; i++) {
				if (bullet[i].isShot && sirokuma.isAlive)
				{
					if (IsHitByCircle(bullet[i].pos.x + 42, bullet[i].pos.y + 60, bullet[i].radius, sirokuma.pos.x + 60, sirokuma.pos.y + 55, sirokuma.radius)) {
						bullet[i].isShot = false;
						sirokuma.hitCount++;

						for (int e = 0; e < kExplosionMax; e++) {
							if (!explosions[e].isActive) {
								explosions[e].isActive = true;
								explosions[e].pos = bullet[i].pos;
								break;
							}
						}

						Novice::PlayAudio(seHit, false, 0.3f);


						if (sirokuma.hitCount >= 30) {
							sirokuma.respawnTimer = 600;
							sirokuma.hitCount = 0;
							sirokuma.isAlive = false;
							sirokuma.dropFish = true;
							sirokumaKillCount++;  // ←リザルト用スコアにも貢献！

							for (int e = 0; e < kExplosionMax; e++) {
								if (!explosions[e].isActive) {
									explosions[e].isActive = true;
									explosions[e].pos = sirokuma.pos;
									break;
								}
							}
						}
					}
				}
			}


			//シロクマと自機
			if (sirokuma.isAlive && penguin.isAlive)
			{
				if (IsHitByCircle(penguin.pos.x + 65, penguin.pos.y + 60, penguin.radius, sirokuma.pos.x + 60, sirokuma.pos.y + 55, sirokuma.radius)) {
					penguin.stamina -= 50;
					Novice::PlayAudio(seDamage, false, 1.0f);


					// ゲームオーバー条件
					if (penguin.stamina <= 0) {
						penguin.isAlive = false;
						isGameOver = true;
					}
				}
			}

			//白熊の球と自機
			for (int i = 0; i < kSirokumaBulletMax; i++) {
				if (sirokumabullet[i].isShot)
				{
					if (IsHitByCircle(penguin.pos.x + 65, penguin.pos.y + 60, penguin.radius, sirokumabullet[i].pos.x + 30, sirokumabullet[i].pos.y + 30, sirokumabullet[i].radius))
					{
						penguin.stamina -= 40;  // ライフやスタミナを減らす
						sirokumabullet[i].isShot = false;
						Novice::PlayAudio(seDamage, false, 1.0);


						if (penguin.stamina <= 0) {
							penguin.isAlive = false;
							isGameOver = true;
						}
					}
				}
			}
		}








		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		if (penguin.isAlive)
		{
			if (penguin.stamina == 100)
			{
				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);
			}
			else if (penguin.stamina == 90)
			{

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 50, 0.0f, BLACK, kFillModeSolid

				);
			}
			else if (penguin.stamina == 80)
			{

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 100, 0.0f, BLACK, kFillModeSolid

				);
			}
			else if (penguin.stamina == 70)
			{

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 150, 0.0f, BLACK, kFillModeSolid

				);
			}
			else if (penguin.stamina == 60)
			{

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 200, 0.0f, BLACK, kFillModeSolid

				);
			}
			else if (penguin.stamina == 50)
			{

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 250, 0.0f, BLACK, kFillModeSolid

				);
			}
			else if (penguin.stamina == 40)
			{

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 300, 0.0f, BLACK, kFillModeSolid

				);
			}
			else if (penguin.stamina == 30)
			{

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 350, 0.0f, BLACK, kFillModeSolid

				);
			}
			else if (penguin.stamina == 20)
			{

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 400, 0.0f, BLACK, kFillModeSolid

				);
			}
			else if (penguin.stamina == 10)
			{
				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, 0xffff00FF, kFillModeSolid

				);

				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 400, 0.0f, BLACK, kFillModeSolid

				);
			}
			else if (penguin.stamina == 0)
			{
				Novice::DrawBox(
					(int)batterix, (int)batteriy,
					70, 500, 0.0f, BLACK, kFillModeSolid

				);
			}
		}

		if (penguin.stamina == 100)
		{
			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);
		}
		else if (penguin.stamina == 90)
		{

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 50, 0.0f, BLACK, kFillModeSolid

			);
		}
		else if (penguin.stamina == 80)
		{

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 100, 0.0f, BLACK, kFillModeSolid

			);
		}
		else if (penguin.stamina == 70)
		{

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 150, 0.0f, BLACK, kFillModeSolid

			);
		}
		else if (penguin.stamina == 60)
		{

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 200, 0.0f, BLACK, kFillModeSolid

			);
		}
		else if (penguin.stamina == 50)
		{

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 250, 0.0f, BLACK, kFillModeSolid

			);
		}
		else if (penguin.stamina == 40)
		{

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 300, 0.0f, BLACK, kFillModeSolid

			);
		}
		else if (penguin.stamina == 30)
		{

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 350, 0.0f, BLACK, kFillModeSolid

			);
		}
		else if (penguin.stamina == 20)
		{

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 400, 0.0f, BLACK, kFillModeSolid

			);
		}
		else if (penguin.stamina == 10)
		{

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, 0xffff00FF, kFillModeSolid

			);

			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 450, 0.0f, BLACK, kFillModeSolid

			);
		}
		else
		{
			Novice::DrawBox(
				(int)batterix, (int)batteriy,
				70, 500, 0.0f, BLACK, kFillModeSolid

			);
		}

		Novice::DrawSprite(
			(int)batterix,
			(int)batteriy,
			GHBGD,
			1.0f, 1.0f, 0.0f, WHITE
		);


		Novice::DrawSprite(
			0,
			0,
			GHBGS,
			1.0f, 1.0f, 0.0f, WHITE
		);

		targetNumber = gameTimer10 / 60;

		if (targetNumber == 0)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 1)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 2)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[2], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 3)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[3], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 4)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[4], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 5)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[5], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 6)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[6], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 7)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[7], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 8)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[8], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 9)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[9], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber == 10)
		{
			Novice::DrawSprite(1100, 200, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
		}



		targetNumber10 = gameTimer100 / 600;

		if (targetNumber10 == 0)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 1)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 2)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[2], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 3)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[3], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 4)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[4], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 5)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[5], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 6)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[6], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 7)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[7], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 8)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[8], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 9)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[9], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber10 == 10)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
		}

		targetNumber100 = gameTimer1000 / 6000;

		if (targetNumber100 == 0)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 1)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 2)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[2], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 3)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[3], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 4)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[4], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 5)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[5], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 6)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[6], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 7)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[7], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 8)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[8], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 9)
		{
			Novice::DrawSprite(1000, 200, graphHandleNumber[9], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (targetNumber100 == 10)
		{
			Novice::DrawSprite(1050, 200, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
		}

		if (sirokumaKillCount == 0)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 1)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 2)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[2], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 3)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[3], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 4)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[4], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 5)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[5], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 6)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[6], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 7)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[7], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 8)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[8], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 9)
		{
			Novice::DrawSprite(1100, 530, graphHandleNumber[9], 0.5f, 0.5f, 0.0f, WHITE);
		}
		else if (sirokumaKillCount == 10)
		{
			Novice::DrawSprite(1050, 530, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
			Novice::DrawSprite(1100, 530, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
		}


		//描画処理
		if (!penguin.isAlive)
		{
			Novice::DrawSprite(
				0,
				0,
				GHBGRE,
				1.0f, 1.0f, 0.0f, WHITE

			);

			targetNumber = gameTimer10 / 60;

			if (targetNumber == 0)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 1)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 2)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[2], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 3)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[3], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 4)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[4], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 5)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[5], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 6)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[6], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 7)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[7], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 8)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[8], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 9)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[9], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber == 10)
			{
				Novice::DrawSprite(400, 150, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
			}

			targetNumber10 = gameTimer100 / 600;

			if (targetNumber10 == 0)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 1)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 2)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[2], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 3)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[3], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 4)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[4], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 5)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[5], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 6)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[6], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 7)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[7], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 8)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[8], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 9)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[9], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber10 == 10)
			{
				Novice::DrawSprite(350, 150, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
			}

			targetNumber100 = gameTimer1000 / 6000;

			if (targetNumber100 == 0)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 1)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 2)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[2], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 3)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[3], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 4)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[4], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 5)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[5], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 6)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[6], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 7)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[7], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 8)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[8], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 9)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[9], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (targetNumber100 == 10)
			{
				Novice::DrawSprite(300, 150, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
			}

			if (sirokumaKillCount == 0)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 1)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 2)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[2], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 3)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[3], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 4)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[4], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 5)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[5], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 6)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[6], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 7)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[7], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 8)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[8], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 9)
			{
				Novice::DrawSprite(500, 260, graphHandleNumber[9], 0.5f, 0.5f, 0.0f, WHITE);
			}
			else if (sirokumaKillCount == 10)
			{
				Novice::DrawSprite(450, 260, graphHandleNumber[1], 0.5f, 0.5f, 0.0f, WHITE);
				Novice::DrawSprite(500, 260, graphHandleNumber[0], 0.5f, 0.5f, 0.0f, WHITE);
			}
		}

		}));
	manager.Register(SceneType::Clear, std::make_unique<ClearScene>([&]() {

		//更新処理
		if (!preKeys[DIK_R] && keys[DIK_R])
		{
			//Novice::StopAudio(playHandle);

			for (int i = 0; i < kAzarasiMax; i++)
			{
				for (int j = 0; j < kSyatiMax; j++)
				{
					for (int k = 0; k < kSirokumaBulletMax; k++)
					{
						for (int l = 0; l < kAzarasiBulletMax; l++)
						{
							manager.ChangeScene(SceneType::Game);
							penguin.isAlive = true;
							penguin.stamina = 100;
							penguin.pos.x = 300.0;;
							penguin.pos.y = 500.0f;
							gameTimer = 0;
							gameTimer10 = 0;
							gameTimer100 = 0;
							gameTimer1000 = 0;
							sirokumaKillCount = 0;
							azarasibullet[l].isShot = false;
							sirokumabullet[k].isShot = false;
							azarasi[i].isAlive = false;
							syati[j].isAlive = false;
							sirokuma.isAlive = false;
							sirokuma.respawnTimer = 600;
							activeSyatiCount = 1;
							activeAzarasiCount = 2;
							sirokuma.hitCount = 0;
						}
					}
				}

			}
			return;
		}

		if (!preKeys[DIK_T] && keys[DIK_T])
		{
			//Novice::StopAudio(playHandle);

			for (int i = 0; i < kAzarasiMax; i++)
			{
				for (int j = 0; j < kSyatiMax; j++)
				{
					for (int k = 0; k < kSirokumaBulletMax; k++)
					{
						for (int l = 0; l < kAzarasiBulletMax; l++)
						{
							manager.ChangeScene(SceneType::Title);
							penguin.isAlive = true;
							penguin.stamina = 100;
							penguin.pos.x = 300.0;;
							penguin.pos.y = 500.0f;
							gameTimer = 0;
							gameTimer10 = 0;
							gameTimer100 = 0;
							gameTimer1000 = 0;
							sirokumaKillCount = 0;
							azarasibullet[l].isShot = false;
							sirokumabullet[k].isShot = false;
							azarasi[i].isAlive = false;
							syati[j].isAlive = false;
							sirokuma.isAlive = false;
							sirokuma.respawnTimer = 600;
							activeSyatiCount = 1;
							activeAzarasiCount = 2;
							sirokuma.hitCount = 0;
						}
					}
				}

			}



			if (!Novice::IsPlayingAudio(playHandle))
			{
				playHandle = Novice::PlayAudio(bgmHandle, true, 0.2f);
			}

			return;



		}

		/*if (!Novice::IsPlayingAudio(playHandle))
		{
			playHandle = Novice::PlayAudio(startHandle, true, 0.5f);
		}*/


		//描画処理

		Novice::DrawSprite(
			0,
			0,
			GHBGEN,
			1.0f, 1.0f, 0.0f, WHITE

		);

		}));
	while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		manager.Update();
		manager.Draw();
		Novice::EndFrame();
		if (!preKeys[DIK_ESCAPE] && keys[DIK_ESCAPE]) break;
	}
	Novice::Finalize();
	return 0;
}
