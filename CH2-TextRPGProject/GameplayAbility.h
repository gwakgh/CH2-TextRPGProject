// GameplayAbility.h
#pragma once
#include <string>

class Actor; // ���� ����

using namespace std;

class GameplayAbility
{
public:
    GameplayAbility(wstring name, float ad_ratio = 0.f, float ap_ratio = 0.f);
    virtual ~GameplayAbility() {}

    // ���� ���� �Լ�: �ڽ� Ŭ�������� �ݵ�� ������
    virtual wstring ActivateAbility(Actor* caster, Actor* target) = 0;

    wstring GetName() const;

protected:
    wstring Name;
    // ������ ���� ���
    float AD_Ratio; // ���� ���ݷ� ���
    float AP_Ratio; // ���� ���ݷ� ���
};