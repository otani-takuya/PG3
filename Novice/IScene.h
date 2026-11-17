#pragma once
// 全シーンの共通インターフェース
class IScene {
public:
    virtual ~IScene() = default;
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};
