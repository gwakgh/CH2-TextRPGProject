// ItemBase.cpp
#include "ItemBase.h"

// ItemBase 클래스의 생성자 구현
ItemBase::ItemBase(std::wstring name, std::wstring description)
    : m_name(name), m_description(description)
{
    // 생성자 본문은 비어있어도 됩니다.
}

// GetName 함수의 구현
std::wstring ItemBase::GetName() const
{
    return m_name;
}

// GetDescription 함수의 구현
std::wstring ItemBase::GetDescription() const
{
    return m_description;
}