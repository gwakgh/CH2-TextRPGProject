// BasicAttack.h
#pragma once
#include "GameplayAbility.h"

class BasicAttack : public GameplayAbility
{
public:
    BasicAttack();

    // 부모 클래스의 순수 가상 함수를 재정의(override)
    virtual wstring ActivateAbility(Actor* Caster, Actor* Target) override;
};