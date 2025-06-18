// Boss.cpp
#include "Boss.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

Boss::Boss() : Enemy(L"보스") // 부모 생성자에 유니코드 이름 전달
{
    AttributeSet* attr = ASC->GetAttributeSet();
    if (attr)
    {
        // 보스 고유 스탯 설정
        attr->Strength = 55.0f;
        attr->Agility = 55.0f;
        attr->Intelligence = 30.0f;
        attr->Defence = 10.0f;
        attr->MagicResistance = 10.0f;
        attr->BaseHP = 75.0f;
        attr->BaseMP = 55.0f;

        attr->UpdateDerivedAttributes();
        attr->HP = attr->MaxHP;
        attr->MP = attr->MaxMP;

		attr->Level = 10; // 보스 레벨 설정
    }
}