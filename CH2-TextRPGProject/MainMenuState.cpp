// MainMenuState.cpp
#include "MainMenuState.h"
#include "Game.h" // Game 클래스의 함수를 호출하기 위해
#include "ConsoleUtils.h"
#include <iostream>
#include <conio.h>
#include <vector>

using namespace std;
using namespace ConsoleUtils;

MainMenuState::MainMenuState() : m_game(nullptr), m_menuCursor(0) {}

void MainMenuState::Init(Game* game)
{
    m_game = game;
    m_menuCursor = 0;
}

void MainMenuState::ProcessInput()
{
    int input = _getch();
    if (input == 224)
    {
        input = _getch();
        if (input == 72) m_menuCursor = (m_menuCursor > 0) ? m_menuCursor - 1 : 0; // 위
        if (input == 80) m_menuCursor = (m_menuCursor < 4) ? m_menuCursor + 1 : 4; // 아래
    }
    else if (input == 13) // 엔터
    {
        switch (m_menuCursor)
        {
        case 0: // 새 게임
            m_game->ChangeState(GameStateID::FIELD);
            break;
        case 1: // 불러오기 (미구현)
            break;
        case 2: // 설정 (미구현)
            break;
        case 3: // 크레딧 (미구현)
            break;
        case 4: // 게임 종료
            m_game->ChangeState(GameStateID::EXIT_GAME);
            break;
        }
    }
}

void MainMenuState::Update()
{
    // 메인 메뉴에서는 특별히 매 프레임 업데이트할 내용이 없음
}
void MainMenuState::Draw()
{
    clearScreen();

    // 제목 (ASCII 아트 스타일)
    gotoxy(10, 2);
    wcout << L"████████╗███████╗██╗  ██╗████████╗     ██████╗ ██████╗  ██████╗";
    gotoxy(10, 3);
    wcout << L"╚══██╔══╝██╔════╝██║  ██║╚══██╔══╝    ██╔════╝ ██╔══██╗██╔═══██╗";
    gotoxy(10, 4);
    wcout << L"   ██║   █████╗  ███████║   ██║       ██║  ███╗██████╔╝██║   ██║";
    gotoxy(10, 5);
    wcout << L"   ██║   ██╔══╝  ██╔══██║   ██║       ██║   ██║██╔═══╝ ██║   ██║";
    gotoxy(10, 6);
    wcout << L"   ██║   ███████╗██║  ██║   ██║       ╚██████╔╝██║     ╚██████╔╝";
    gotoxy(10, 7);
    wcout << L"   ╚═╝   ╚══════╝╚═╝  ╚═╝   ╚═╝        ╚═════╝ ╚═╝      ╚═════╝ ";

    // 메뉴 항목
    vector<wstring> options = { L"새 게임", L"불러오기", L"설정", L"크레딧", L"게임 종료" };

    int boxStartX = 30;
    int startY = 10;

    for (int i = 0; i < options.size(); ++i)
    {
        gotoxy(boxStartX, startY + i * 3);

        if (m_menuCursor == i)
        {
            wcout << L"┏━━━━━━━━━━━━━━┓";
            gotoxy(boxStartX, startY + i * 3 + 1);
            wcout << L"┃   " << options[i];
            for (int s = 0; s < 10 - options[i].length(); ++s) wcout << L" ";
            wcout << L" ◀ ";
            gotoxy(boxStartX, startY + i * 3 + 2);
            wcout << L"┗━━━━━━━━━━━━━━┛";
        }
        else
        {
            wcout << L"┌──────────────┐";
            gotoxy(boxStartX, startY + i * 3 + 1);
            wcout << L"│   " << options[i];
            for (int s = 0; s < 10 - options[i].length(); ++s) wcout << L" ";
            wcout << L"   ";
            gotoxy(boxStartX, startY + i * 3 + 2);
            wcout << L"└──────────────┘";
        }
    }

    // 하단 안내
    gotoxy(22, startY + options.size() * 3 + 2);
    wcout << L"[ ↑ / ↓ 방향키로 이동 | Enter: 선택 ]";
}
