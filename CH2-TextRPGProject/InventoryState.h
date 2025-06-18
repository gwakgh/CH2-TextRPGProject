// InventoryState.h
#pragma once
#include "GameStateBase.h"

class InventoryState : public GameStateBase
{
public:
    InventoryState();
    virtual void Init(Game* game) override;
    virtual void ProcessInput() override;
    virtual void Update() override;
    virtual void Draw() override;

private:
    Game* m_game;
    int m_cursor;
};