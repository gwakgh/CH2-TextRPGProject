// InventoryComponent.cpp
#include "InventoryComponent.h"

InventoryComponent::~InventoryComponent()
{
    // 인벤토리가 소멸될 때, 가지고 있던 모든 아이템 메모리 해제
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
        delete m_items[index]; // 메모리 해제
        m_items.erase(m_items.begin() + index); // 벡터에서 제거
    }
}

const std::vector<ItemBase*>& InventoryComponent::GetItems() const
{
    return m_items;
}