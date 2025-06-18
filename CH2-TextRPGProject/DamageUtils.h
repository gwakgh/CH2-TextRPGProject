// DamageUtils.h
#pragma once

// 전방 선언
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
    // 물리, 마법 데미지를 계산하여 최종 데미지를 반환
        static DamageResult CalculatePhysicalDamage(Actor* Caster, Actor* Target, float AD_Ratio);
        static DamageResult CalculateMagicalDamage(Actor* Caster, Actor* Target, float AP_Ratio);
        // 고정 데미지는 편차나 방어력 계산이 없으므로 별도 함수는 불필요

private:
    // 기본 데미지에 15%의 편차(variance)를 적용
    static float ApplyDamageVariance(float BaseDamage);
};