#include "SousaScene.h"
SousaScene::SousaScene(std::function<void()> update, std::function<void()> draw)
    : update_(std::move(update)), draw_(std::move(draw)) {}
void SousaScene::Init() {}
void SousaScene::Update() { if (update_) update_(); }
void SousaScene::Draw() { if (draw_) draw_(); }
