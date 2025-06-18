// Boss.cpp
#include "Boss.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

Boss::Boss() : Enemy(L"����") // �θ� �����ڿ� �����ڵ� �̸� ����
{
    AttributeSet* attr = ASC->GetAttributeSet();
    if (attr)
    {
        // ���� ���� ���� ����
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

		attr->Level = 10; // ���� ���� ����
    }
}