// Enemy.cpp
#include "Enemy.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"

using namespace std;

Enemy::Enemy(wstring name) : Actor(name)
{
    // Enemy 클래스에서 OwnerName을 설정해줘야 자식 클래스에서 잊지 않음
    AttributeSet* attr = ASC->GetAttributeSet();
    if (attr)
    {
        attr->SetOwnerName(this->Name);
    }
}