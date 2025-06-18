// ItemBase.cpp
#include "ItemBase.h"

// ItemBase Ŭ������ ������ ����
ItemBase::ItemBase(std::wstring name, std::wstring description)
    : m_name(name), m_description(description)
{
    // ������ ������ ����־ �˴ϴ�.
}

// GetName �Լ��� ����
std::wstring ItemBase::GetName() const
{
    return m_name;
}

// GetDescription �Լ��� ����
std::wstring ItemBase::GetDescription() const
{
    return m_description;
}