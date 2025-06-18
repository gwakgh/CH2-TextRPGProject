// ItemBase.h
#pragma once
#include <string>

using namespace std;;

class Actor; // ���� ����

class ItemBase
{
public:
    ItemBase(wstring name, wstring description);
    virtual ~ItemBase() {}

    // �������� ����ϴ� ���� ���� �Լ�
    virtual void Use(Actor* user) = 0;

    wstring GetName() const;
    wstring GetDescription() const;

protected:
    wstring m_name;
    wstring m_description;
};