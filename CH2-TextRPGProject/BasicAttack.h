// BasicAttack.h
#pragma once
#include "GameplayAbility.h"

class BasicAttack : public GameplayAbility
{
public:
    BasicAttack();

    // �θ� Ŭ������ ���� ���� �Լ��� ������(override)
    virtual wstring ActivateAbility(Actor* Caster, Actor* Target) override;
};