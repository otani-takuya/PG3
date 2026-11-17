#include "ClearScene.h"
ClearScene::ClearScene(std::function<void()> update, std::function<void()> draw)
    : update_(std::move(update)), draw_(std::move(draw)) {}
void ClearScene::Init() {}
void ClearScene::Update() { if (update_) update_(); }
void ClearScene::Draw() { if (draw_) draw_(); }
