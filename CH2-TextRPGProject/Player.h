// Player.h
#pragma once
#include "Actor.h"
#include "InventoryComponent.h" // 인벤토리 컴포넌트 포함

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Player : public Actor
{
public:
    Player(std::wstring name);
    ~Player();

    // 방향 관련 함수는 Player 고유의 것이므로 유지
    void SetDirection(Direction dir);
    Direction GetDirection() const;
    InventoryComponent* GetInventoryComponent() const;

private:
    // m_x, m_y 와 관련 함수들을 제거 (Actor로부터 상속받음)
    Direction m_direction;
    InventoryComponent* m_inventory;
};