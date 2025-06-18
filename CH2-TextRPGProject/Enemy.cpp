// Enemy.cpp
#include "Enemy.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

using namespace std;

Enemy::Enemy(wstring name) : Actor(name)
{
    // Enemy Ŭ�������� OwnerName�� ��������� �ڽ� Ŭ�������� ���� ����
    AttributeSet* attr = ASC->GetAttributeSet();
    if (attr)
    {
        attr->SetOwnerName(this->Name);
    }
}