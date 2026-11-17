#include "GameManager.h"
#include <cstddef>
GameManager::GameManager() = default;
GameManager::~GameManager() = default;
void GameManager::Register(SceneType id, std::unique_ptr<IScene> scene) {
    scenes_[static_cast<size_t>(id)] = std::move(scene);
}
void GameManager::ChangeScene(SceneType id) {
    if (current_ != id) { current_ = id; needsInit_ = true; }
}
void GameManager::Update() {
    auto& scene = scenes_[static_cast<size_t>(current_)];
    if (!scene) return;
    if (needsInit_) { needsInit_ = false; scene->Init(); }
    scene->Update();
}
void GameManager::Draw() {
    auto& scene = scenes_[static_cast<size_t>(current_)];
    if (scene) scene->Draw();
}
