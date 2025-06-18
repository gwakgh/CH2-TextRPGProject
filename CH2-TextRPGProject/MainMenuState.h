// MainMenuState.h
#pragma once
#include "GameStateBase.h"

class MainMenuState : public GameStateBase
{
public:
    MainMenuState();
    virtual void Init(Game* game) override;
    virtual void ProcessInput() override;
    virtual void Update() override;
    virtual void Draw() override;

private:
    Game* m_game;
    int m_menuCursor;
};