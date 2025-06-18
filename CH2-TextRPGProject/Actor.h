// Actor.h
#pragma once
#include "AbilitySystemComponent.h"

#include <string>

using namespace std;

class AbilitySystemComponent;

class Actor
{
public:
    Actor(wstring name);
    virtual ~Actor();

    wstring GetName() const;
    AbilitySystemComponent* GetAbilitySystemComponent() const;

    // --- ��ġ ���� �Լ� �߰� ---
    virtual void SetPosition(int x, int y);
    virtual int GetX() const;
    virtual int GetY() const;

protected:
    wstring Name;
    AbilitySystemComponent* ASC;

    // --- ��ǥ ���� �߰� ---
    int m_x;
    int m_y;
};