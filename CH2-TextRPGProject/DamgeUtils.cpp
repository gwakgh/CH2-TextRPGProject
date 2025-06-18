// DamageUtils.cpp
#include "DamageUtils.h"
#include "Actor.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include <random>
#include <algorithm>

using namespace std;

// ���� ������ ���
DamageResult DamageUtils::CalculatePhysicalDamage(Actor* Caster, Actor* Target, float AD_Ratio)
{
    AttributeSet* casterAttr = Caster->GetAbilitySystemComponent()->GetAttributeSet();
    AttributeSet* targetAttr = Target->GetAbilitySystemComponent()->GetAttributeSet();
    DamageResult result;

    // 1. �⺻ �������� ���������� ���
    float baseDamage = casterAttr->Strength * AD_Ratio;

    // 2. ũ��Ƽ�� �߻� ���� ����
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.0, 100.0);

    float critChance = casterAttr->Agility * 0.5f; // ��ø 1�� 0.5%
    if (distrib(gen) < critChance)
    {
        result.bWasCritical = true;
        baseDamage *= 1.5f; // ũ��Ƽ�� ������ 1.5��
    }

    // 3. ���� ����
    float finalDamage = baseDamage - targetAttr->Defence;
    finalDamage = max(1.0f, finalDamage);

	// ��� ���� ��� 30% ������ ����
    if (targetAttr->bIsDefending)
    {
        finalDamage *= 0.3f;
    }

    // 4. ������ ���� ����
    result.Damage = ApplyDamageVariance(finalDamage);

    return result;
}

// ���� ������ ��� (������ ũ��Ƽ�� X)
DamageResult DamageUtils::CalculateMagicalDamage(Actor* Caster, Actor* Target, float AP_Ratio)
{
    AttributeSet* casterAttr = Caster->GetAbilitySystemComponent()->GetAttributeSet();
    AttributeSet* targetAttr = Target->GetAbilitySystemComponent()->GetAttributeSet();
    DamageResult result; // bWasCritical�� false�� ����

    // �⺻ �������� ���������� ���
    float baseDamage = casterAttr->Intelligence * AP_Ratio;
    float finalDamage = baseDamage - targetAttr->MagicResistance;
    finalDamage = max(1.0f, finalDamage);

    // ��� ������ ��� ������ 15% ����
    if (targetAttr->bIsDefending)
    {
        finalDamage *= 0.15f;
    }

    result.Damage = ApplyDamageVariance(finalDamage);
    return result;
}

// ������ ���� ����
float DamageUtils::ApplyDamageVariance(float BaseDamage)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distrib(0.85, 1.15);

    return BaseDamage * (float)distrib(gen);
}