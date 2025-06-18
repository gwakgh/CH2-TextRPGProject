// GameStateBase.h
#pragma once

class Game; // Game 클래스를 전방 선언

// 앞으로 전환될 게임 상태를 나타내는 ID
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

    // Game 클래스의 주소를 받아, 각 상태가 게임 전체 데이터에 접근할 수 있도록 함
    virtual void Init(Game* game) = 0;

    virtual void ProcessInput() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
};