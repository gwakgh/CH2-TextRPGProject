// Actor.cpp

#include "Actor.h"
#include "AbilitySystemComponent.h"

using namespace std;

// �������� �ʱ�ȭ ����Ʈ�� �����մϴ�.
Actor::Actor(wstring name) : Name(name), m_x(0), m_y(0) // Actor(name) -> Name(name) ���� ����
{
    this->ASC = new AbilitySystemComponent();
}

Actor::~Actor()
{
    delete this->ASC;
}

wstring Actor::GetName() const
{
    return this->Name;
}

AbilitySystemComponent* Actor::GetAbilitySystemComponent() const
{
    return this->ASC;
}

void Actor::SetPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

int Actor::GetX() const
{
    return m_x;
}

int Actor::GetY() const
{
    return m_y;
}