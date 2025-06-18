// DamageUtils.cpp
#include "DamageUtils.h"
#include "Actor.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include <random>
#include <algorithm>

using namespace std;

// 물리 데미지 계산
DamageResult DamageUtils::CalculatePhysicalDamage(Actor* Caster, Actor* Target, float AD_Ratio)
{
    AttributeSet* casterAttr = Caster->GetAbilitySystemComponent()->GetAttributeSet();
    AttributeSet* targetAttr = Target->GetAbilitySystemComponent()->GetAttributeSet();
    DamageResult result;

    // 1. 기본 데미지를 곱연산으로 계산
    float baseDamage = casterAttr->Strength * AD_Ratio;

    // 2. 크리티컬 발생 여부 판정
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.0, 100.0);

    float critChance = casterAttr->Agility * 0.5f; // 민첩 1당 0.5%
    if (distrib(gen) < critChance)
    {
        result.bWasCritical = true;
        baseDamage *= 1.5f; // 크리티컬 데미지 1.5배
    }

    // 3. 방어력 적용
    float finalDamage = baseDamage - targetAttr->Defence;
    finalDamage = max(1.0f, finalDamage);

	// 방어 중인 경우 30% 데미지 감소
    if (targetAttr->bIsDefending)
    {
        finalDamage *= 0.3f;
    }

    // 4. 데미지 편차 적용
    result.Damage = ApplyDamageVariance(finalDamage);

    return result;
}

// 마법 데미지 계산 (마법은 크리티컬 X)
DamageResult DamageUtils::CalculateMagicalDamage(Actor* Caster, Actor* Target, float AP_Ratio)
{
    AttributeSet* casterAttr = Caster->GetAbilitySystemComponent()->GetAttributeSet();
    AttributeSet* targetAttr = Target->GetAbilitySystemComponent()->GetAttributeSet();
    DamageResult result; // bWasCritical은 false로 유지

    // 기본 데미지를 곱연산으로 계산
    float baseDamage = casterAttr->Intelligence * AP_Ratio;
    float finalDamage = baseDamage - targetAttr->MagicResistance;
    finalDamage = max(1.0f, finalDamage);

    // 방어 상태일 경우 데미지 15% 감소
    if (targetAttr->bIsDefending)
    {
        finalDamage *= 0.15f;
    }

    result.Damage = ApplyDamageVariance(finalDamage);
    return result;
}

// 데미지 편차 적용
float DamageUtils::ApplyDamageVariance(float BaseDamage)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.85, 1.15);

    return BaseDamage * (float)distrib(gen);
}