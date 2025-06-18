// Player.cpp
#include "Player.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

Player::Player(wstring name) : Actor(name)
{
    AttributeSet* attr = ASC->GetAttributeSet();
    if (attr)
    {
        attr->SetOwnerName(this->Name);

        attr->Strength = 10.0f;
        attr->Agility = 30.0f; // ũ��Ƽ�� �׽�Ʈ�� ���� ��ø�� ���� ���� (15% Ȯ��)
        attr->Intelligence = 7.0f;
        attr->Defence = 10.0f;
        attr->MagicResistance = 5.0f;
        attr->BaseHP = 100.0f;
        attr->BaseMP = 50.0f;

        attr->UpdateDerivedAttributes();
        attr->HP = attr->MaxHP;
        attr->MP = attr->MaxMP;
    }

    // �κ��丮 ������Ʈ ����
    m_inventory = new InventoryComponent();

    // �ʵ�� ��ġ ����
    m_x = 5;
    m_y = 5;
    m_direction = Direction::DOWN;
}

void Player::SetDirection(Direction dir)
{
    m_direction = dir;
}

Direction Player::GetDirection() const
{
    return m_direction;
}
Player::~Player()
{
    delete m_inventory; // �Ҹ��ڿ��� �κ��丮 �޸� ����
}

InventoryComponent* Player::GetInventoryComponent() const
{
    return m_inventory;
}