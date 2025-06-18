// HealthPotion.cpp
#include "HealthPotion.h"
#include "Actor.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"

#include <iostream>

using namespace std;

HealthPotion::HealthPotion()
    : ItemBase(L"체력 포션", L"HP를 50만큼 회복합니다.")
{
}

inline void HealthPotion::Use(Actor* user)
{
    if (!user) return;

    AbilitySystemComponent* asc = user->GetAbilitySystemComponent();
    AttributeSet* attr = asc->GetAttributeSet();

    // +50 HP 효과를 생성
    GameplayEffect effect(attr, EAttributeOperation::Add, 50.0f);

    // ASC에 효과 적용을 요청
    asc->ApplyGameplayEffect(&effect);

    // 콘솔에는 간단한 메시지 출력 (실제 게임에서는 이 로직을 BattleManager나 UIManager가 담당)
    wcout << L"\n" << m_name << L"을(를) 사용했습니다. " << m_description << endl;
}

