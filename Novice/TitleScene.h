#pragma once
#include "IScene.h"
#include <functional>
// TitleScene: シーンごとの処理を担当
class TitleScene final : public IScene {
public:
    explicit TitleScene(std::function<void()> update, std::function<void()> draw = {});
    void Init() override;
    void Update() override;
    void Draw() override;
private:
    std::function<void()> update_;
    std::function<void()> draw_;
};
