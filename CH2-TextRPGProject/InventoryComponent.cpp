// InventoryComponent.cpp
#include "InventoryComponent.h"

InventoryComponent::~InventoryComponent()
{
    // �κ��丮�� �Ҹ�� ��, ������ �ִ� ��� ������ �޸� ����
    for (ItemBase* item : m_items)
    {
        delete item;
    }
    m_items.clear();
}

void InventoryComponent::AddItem(ItemBase* item)
{
    if (item) m_items.push_back(item);
}

void InventoryComponent::RemoveItem(int index)
{
    if (index >= 0 && index < m_items.size())
    {
        delete m_items[index]; // �޸� ����
        m_items.erase(m_items.begin() + index); // ���Ϳ��� ����
    }
}

const std::vector<ItemBase*>& InventoryComponent::GetItems() const
{
    return m_items;
}