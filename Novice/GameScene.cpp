#include "GameScene.h"
GameScene::GameScene(std::function<void()> update, std::function<void()> draw)
    : update_(std::move(update)), draw_(std::move(draw)) {}
void GameScene::Init() {}
void GameScene::Update() { if (update_) update_(); }
void GameScene::Draw() { if (draw_) draw_(); }
