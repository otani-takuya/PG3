#pragma once
#include "IScene.h"
#include <functional>
// GameScene: シーンごとの処理を担当
class GameScene final : public IScene {
public:
    explicit GameScene(std::function<void()> update, std::function<void()> draw = {});
    void Init() override;
    void Update() override;
    void Draw() override;
private:
    std::function<void()> update_;
    std::function<void()> draw_;
};
