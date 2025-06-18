// GameStateBase.h
#pragma once

class Game; // Game Ŭ������ ���� ����

// ������ ��ȯ�� ���� ���¸� ��Ÿ���� ID
enum class GameStateID
{
    NONE,
    MAIN_MENU,
    FIELD,
    INVENTORY,
    BATTLE,
    EXIT_GAME
};

class GameStateBase
{
public:
    virtual ~GameStateBase() {}

    // Game Ŭ������ �ּҸ� �޾�, �� ���°� ���� ��ü �����Ϳ� ������ �� �ֵ��� ��
    virtual void Init(Game* game) = 0;

    virtual void ProcessInput() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};