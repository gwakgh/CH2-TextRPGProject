// GameplayAbility.h
#pragma once
#include <string>

class Actor; // 전방 선언

using namespace std;

class GameplayAbility
{
public:
    GameplayAbility(wstring name, float ad_ratio = 0.f, float ap_ratio = 0.f);
    virtual ~GameplayAbility() {}

    // 순수 가상 함수: 자식 클래스에서 반드시 재정의
    virtual wstring ActivateAbility(Actor* caster, Actor* target) = 0;

    wstring GetName() const;

protected:
    wstring Name;
    // 데미지 연산 계수
    float AD_Ratio; // 물리 공격력 계수
    float AP_Ratio; // 마법 공격력 계수
};