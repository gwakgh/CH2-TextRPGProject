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
        attr->Agility = 30.0f; // 크리티컬 테스트를 위해 민첩을 높게 설정 (15% 확률)
        attr->Intelligence = 7.0f;
        attr->Defence = 10.0f;
        attr->MagicResistance = 5.0f;
        attr->BaseHP = 100.0f;
        attr->BaseMP = 50.0f;

        attr->UpdateDerivedAttributes();
        attr->HP = attr->MaxHP;
        attr->MP = attr->MaxMP;
    }

    // 인벤토리 컴포넌트 생성
    m_inventory = new InventoryComponent();

    // 필드용 위치 설정
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
    delete m_inventory; // 소멸자에서 인벤토리 메모리 해제
}

InventoryComponent* Player::GetInventoryComponent() const
{
    return m_inventory;
}