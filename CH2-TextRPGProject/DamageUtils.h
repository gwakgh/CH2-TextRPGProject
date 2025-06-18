// DamageUtils.h
#pragma once

// ���� ����
class Actor;
class GameplayAbility;

struct DamageResult
{
    float Damage = 0.0f;
    bool bWasCritical = false;
};

class DamageUtils
{
public:
    // ����, ���� �������� ����Ͽ� ���� �������� ��ȯ
        static DamageResult CalculatePhysicalDamage(Actor* Caster, Actor* Target, float AD_Ratio);
        static DamageResult CalculateMagicalDamage(Actor* Caster, Actor* Target, float AP_Ratio);
        // ���� �������� ������ ���� ����� �����Ƿ� ���� �Լ��� ���ʿ�

private:
    // �⺻ �������� 15%�� ����(variance)�� ����
    static float ApplyDamageVariance(float BaseDamage);
};