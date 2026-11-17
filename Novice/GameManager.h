#pragma once
#include "IScene.h"
#include "SceneType.h"
#include <array>
#include <memory>

class GameManager {
public:
    GameManager();
    ~GameManager();
    void Register(SceneType id, std::unique_ptr<IScene> scene);
    void ChangeScene(SceneType id);
    void Update();
    void Draw();
private:
    std::array<std::unique_ptr<IScene>, static_cast<size_t>(SceneType::Count)> scenes_{};
    SceneType current_ = SceneType::Title;
    bool needsInit_ = true;
};
