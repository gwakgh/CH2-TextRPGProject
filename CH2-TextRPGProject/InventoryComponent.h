// InventoryComponent.h
#pragma once
#include <vector>
#include "ItemBase.h"

class InventoryComponent
{
public:
    ~InventoryComponent();
    void AddItem(ItemBase* item);
    void RemoveItem(int index);
    const std::vector<ItemBase*>& GetItems() const;

private:
    std::vector<ItemBase*> m_items;
};