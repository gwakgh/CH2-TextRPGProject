// FieldState.h
#pragma once
#include "GameStateBase.h"

class FieldState : public GameStateBase
{
public:
    virtual void Init(Game* game) override;
    virtual void ProcessInput() override;
    virtual void Update() override;
    virtual void Draw() override;
private:
    Game* m_game;
};