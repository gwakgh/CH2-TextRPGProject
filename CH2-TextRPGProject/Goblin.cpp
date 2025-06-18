// Goblin.cpp
#include "Goblin.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

Goblin::Goblin() : Enemy(L"고블린") // 부모 생성자에 유니코드 이름 전달
{
    AttributeSet* attr = ASC->GetAttributeSet();
    if (attr)
    {
        // 고블린 고유 스탯 설정
        attr->Strength = 7.0f;
        attr->Agility = 10.0f;
        attr->Intelligence = 2.0f;
        attr->Defence = 5.0f;
        attr->MagicResistance = 2.0f;
        attr->BaseHP = 30.0f;
        attr->BaseMP = 10.0f;

        attr->UpdateDerivedAttributes();
        attr->HP = attr->MaxHP;
        attr->MP = attr->MaxMP;
    }
}