// ItemBase.h
#pragma once
#include <string>

using namespace std;;

class Actor; // 전방 선언

class ItemBase
{
public:
    ItemBase(wstring name, wstring description);
    virtual ~ItemBase() {}

    // 아이템을 사용하는 순수 가상 함수
    virtual void Use(Actor* user) = 0;

    wstring GetName() const;
    wstring GetDescription() const;

protected:
    wstring m_name;
    wstring m_description;
};