#include "TitleScene.h"
TitleScene::TitleScene(std::function<void()> update, std::function<void()> draw)
    : update_(std::move(update)), draw_(std::move(draw)) {}
void TitleScene::Init() {}
void TitleScene::Update() { if (update_) update_(); }
void TitleScene::Draw() { if (draw_) draw_(); }
