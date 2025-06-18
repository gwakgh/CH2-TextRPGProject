// Game.h
#pragma once
#include "GameStateBase.h"
#include <map>

class Player;
class Field;
class Enemy;

class Game
{
public:
    Game();
    ~Game();

    void Run();
    void ChangeState(GameStateID newStateID);

    // 다른 상태들이 게임의 핵심 데이터와 기능에 접근할 수 있도록 public으로 둡니다.
    Player* m_player;
    Field* m_field;
    void StartBattle(Enemy* enemy); // FieldState에서 호출할 수 있도록 public으로 변경

private:
    bool m_isRunning;
    GameStateBase* m_currentState;
    std::map<GameStateID, GameStateBase*> m_states;
};