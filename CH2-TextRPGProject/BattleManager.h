// BattleManager.h
#pragma once
#include <vector>
#include <string>

class Actor;

enum class BattleState { MainMenu, AttackMenu, ItemMenu, Busy, BattleEnd };

class BattleManager
{
public:
    BattleManager(std::vector<Actor*> playerParty, std::vector<Actor*> enemyParty);
    void Run(); // 전투 실행

private:
    void Draw();
    void ProcessInput();
    void Update();
    void PlayIntroAnimation();

    std::vector<Actor*> m_playerParty;
    std::vector<Actor*> m_enemyParty;

    BattleState m_currentState;
    int m_mainMenuSelection;
    int m_attackMenuSelection;
    std::wstring m_statusMessage;
};