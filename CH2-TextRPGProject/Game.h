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

    // �ٸ� ���µ��� ������ �ٽ� �����Ϳ� ��ɿ� ������ �� �ֵ��� public���� �Ӵϴ�.
    Player* m_player;
    Field* m_field;
    void StartBattle(Enemy* enemy); // FieldState���� ȣ���� �� �ֵ��� public���� ����

private:
    bool m_isRunning;
    GameStateBase* m_currentState;
    std::map<GameStateID, GameStateBase*> m_states;
};