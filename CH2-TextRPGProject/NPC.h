// NPC.h
#pragma once
#include "Actor.h"

#include <vector>

using namespace std;

class Player; // 전방 선언

// NPC의 역할을 구분하기 위한 열거형
enum class NPCType
{
    HEALER,       // 회복 NPC
    SHOP_ITEM,    // 아이템 상점
    SHOP_SKILL,    // 스킬 상점
    BOSS
};

class NPC : public Actor
{
public:
    NPC(wstring name, NPCType type, int x, int y);

    wstring GetInteractionMessage();

    void Interact(Player* player);

    NPCType GetType() const;

private:
    NPCType m_type;
};