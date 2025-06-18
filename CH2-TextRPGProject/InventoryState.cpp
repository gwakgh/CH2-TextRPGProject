// InventoryState.cpp
#include "InventoryState.h"
#include "Game.h"
#include "Player.h"
#include "InventoryComponent.h"
#include "ItemBase.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <conio.h>
#include <windows.h> // Sleep

using namespace std;
using namespace ConsoleUtils;

InventoryState::InventoryState() : m_game(nullptr), m_cursor(0) {}

void InventoryState::Init(Game* game)
{
    m_game = game;
}

void InventoryState::ProcessInput()
{
    int input = _getch();
    const auto& items = m_game->m_player->GetInventoryComponent()->GetItems();

    if (input == 224) // 방향키
    {
        input = _getch();
        switch (input)
        {
        case 72: // 위
            m_cursor = (m_cursor > 0) ? m_cursor - 1 : 0;
            break;
        case 80: // 아래
            if (!items.empty())
            {
                m_cursor = (m_cursor < (int)items.size() - 1) ? m_cursor + 1 : (int)items.size() - 1;
            }
            break;
        }
    }
    else if (input == 13) // Enter 키: 아이템 사용
    {
        if (!items.empty() && m_cursor < items.size())
        {
            items[m_cursor]->Use(m_game->m_player);
            m_game->m_player->GetInventoryComponent()->RemoveItem(m_cursor);
            if (m_cursor >= (int)m_game->m_player->GetInventoryComponent()->GetItems().size() && m_cursor > 0)
            {
                m_cursor--;
            }
            Sleep(1500);
        }
    }
    else if (input == 27) // ESC 키: 필드 상태로 돌아가기
    {
        m_game->ChangeState(GameStateID::FIELD);
    }
}

void InventoryState::Update()
{
    // 인벤토리 상태에서는 특별히 업데이트할 내용 없음
}

void InventoryState::Draw()
{
    clearScreen();
    gotoxy(2, 1);
    wcout << L"--- 인벤토리 (ESC: 나가기) ---";

    const auto& items = m_game->m_player->GetInventoryComponent()->GetItems();
    if (items.empty())
    {
        gotoxy(2, 3);
        wcout << L"가방이 비어있습니다.";
    }
    else
    {
        for (size_t i = 0; i < items.size(); ++i)
        {
            gotoxy(2, 3 + (int)i);
            wcout << (m_cursor == (int)i ? L"▶ " : L"  ") << items[i]->GetName() << L" : " << items[i]->GetDescription();
        }
    }
}