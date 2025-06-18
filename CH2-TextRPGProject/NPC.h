// NPC.h
#pragma once
#include "Actor.h"

#include <vector>

using namespace std;

class Player; // ���� ����

// NPC�� ������ �����ϱ� ���� ������
enum class NPCType
{
    HEALER,       // ȸ�� NPC
    SHOP_ITEM,    // ������ ����
    SHOP_SKILL,    // ��ų ����
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