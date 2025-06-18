// BasicAttack.cpp
#include "BasicAttack.h"
#include "Actor.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DamageUtils.h" // DamageResult를 위해 포함

#include <iostream>
#include <string> // to_wstring 사용

using namespace std;

// AD 계수를 곱연산에 맞게 1.2로 조정
BasicAttack::BasicAttack() : GameplayAbility(L"기본 공격", 1.2f, 0.0f)
{
}

wstring BasicAttack::ActivateAbility(Actor* Caster, Actor* Target)
{
    if (!Caster || !Target) return L"";

    DamageResult result = DamageUtils::CalculatePhysicalDamage(Caster, Target, this->AD_Ratio);
    int damageToInt = static_cast<int>(result.Damage);

    AttributeSet* targetAttr = Target->GetAbilitySystemComponent()->GetAttributeSet();
    targetAttr->HP -= result.Damage;

    // 결과 메시지를 wstring으로 만들어서 반환
    wstring message = L"▶ " + Caster->GetName() + L"의 " + this->GetName() + L"!\n";
    if (result.bWasCritical)
    {
        message += L"   ★★ CRITICAL HIT! ★★\n";
    }
    message += L"   " + Target->GetName() + L"에게 " + to_wstring(damageToInt) + L"의 물리 데미지!";

    if (targetAttr->HP <= 0)
    {
        targetAttr->HP = 0;
        message += L"\n   " + Target->GetName() + L"을(를) 쓰러트렸다!";
    }
    return message;
}