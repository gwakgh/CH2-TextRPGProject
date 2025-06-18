// BasicAttack.cpp
#include "BasicAttack.h"
#include "Actor.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DamageUtils.h" // DamageResult�� ���� ����

#include <iostream>
#include <string> // to_wstring ���

using namespace std;

// AD ����� �����꿡 �°� 1.2�� ����
BasicAttack::BasicAttack() : GameplayAbility(L"�⺻ ����", 1.2f, 0.0f)
{
}

wstring BasicAttack::ActivateAbility(Actor* Caster, Actor* Target)
{
    if (!Caster || !Target) return L"";

    DamageResult result = DamageUtils::CalculatePhysicalDamage(Caster, Target, this->AD_Ratio);
    int damageToInt = static_cast<int>(result.Damage);

    AttributeSet* targetAttr = Target->GetAbilitySystemComponent()->GetAttributeSet();
    targetAttr->HP -= result.Damage;

    // ��� �޽����� wstring���� ���� ��ȯ
    wstring message = L"�� " + Caster->GetName() + L"�� " + this->GetName() + L"!\n";
    if (result.bWasCritical)
    {
        message += L"   �ڡ� CRITICAL HIT! �ڡ�\n";
    }
    message += L"   " + Target->GetName() + L"���� " + to_wstring(damageToInt) + L"�� ���� ������!";

    if (targetAttr->HP <= 0)
    {
        targetAttr->HP = 0;
        message += L"\n   " + Target->GetName() + L"��(��) ����Ʈ�ȴ�!";
    }
    return message;
}