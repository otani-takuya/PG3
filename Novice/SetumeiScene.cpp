#include "SetumeiScene.h"
SetumeiScene::SetumeiScene(std::function<void()> update, std::function<void()> draw)
    : update_(std::move(update)), draw_(std::move(draw)) {}
void SetumeiScene::Init() {}
void SetumeiScene::Update() { if (update_) update_(); }
void SetumeiScene::Draw() { if (draw_) draw_(); }
