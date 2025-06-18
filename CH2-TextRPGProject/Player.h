// Player.h
#pragma once
#include "Actor.h"
#include "InventoryComponent.h" // �κ��丮 ������Ʈ ����

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Player : public Actor
{
public:
    Player(std::wstring name);
    ~Player();

    // ���� ���� �Լ��� Player ������ ���̹Ƿ� ����
    void SetDirection(Direction dir);
    Direction GetDirection() const;
    InventoryComponent* GetInventoryComponent() const;

private:
    // m_x, m_y �� ���� �Լ����� ���� (Actor�κ��� ��ӹ���)
    Direction m_direction;
    InventoryComponent* m_inventory;
};