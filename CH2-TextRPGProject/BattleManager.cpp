// BattleManager.cpp
#include "BattleManager.h"
#include "Actor.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbility.h"
#include "ConsoleUtils.h" // 우리의 새 유틸리티

#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;
using namespace ConsoleUtils;

BattleManager::BattleManager(vector<Actor*> playerParty, vector<Actor*> enemyParty)
    : m_playerParty(playerParty), m_enemyParty(enemyParty),
    m_currentState(BattleState::MainMenu),
    m_mainMenuSelection(0), m_attackMenuSelection(0)
{
    m_statusMessage = L"야생의 " + m_enemyParty[0]->GetName() + L"이(가) 나타났다!";
}

void BattleManager::Run() {
    ConsoleUtils::ShowConsoleCursor(false);
    // 전투 진입 인트로 애니메이션 재생
    PlayIntroAnimation();

    // 초기 메시지 표시를 위해 첫 프레임을 먼저 그림
    Draw();
    Sleep(1500);

    while (m_currentState != BattleState::BattleEnd) {
        Draw();
        ProcessInput();
        Update();
    }
    // 전투 종료 메시지를 포함한 마지막 프레임을 그림
    Draw();
    Sleep(2000);
    ConsoleUtils::ShowConsoleCursor(true);
}

void BattleManager::ProcessInput() {
    if (m_currentState != BattleState::MainMenu && m_currentState != BattleState::AttackMenu) {
        return; // 입력을 받지 않는 상태면 리턴
    }
    char input = _getch();
    if (input == (char)224) { // 방향키
        input = _getch();
        if (m_currentState == BattleState::MainMenu) {
            if (input == 72) m_mainMenuSelection = (m_mainMenuSelection - 1 + 4) % 4; // 위
            if (input == 80) m_mainMenuSelection = (m_mainMenuSelection + 1) % 4;    // 아래
        }
        else if (m_currentState == BattleState::AttackMenu) {
            int skillCount = static_cast<int>(m_playerParty[0]->GetAbilitySystemComponent()->GrantedAbilities.size());
            int totalMenuItems = 5; // 스킬 4개 + 뒤로가기
            if (input == 72) m_attackMenuSelection = (m_attackMenuSelection - 1 + totalMenuItems) % totalMenuItems;
            if (input == 80) m_attackMenuSelection = (m_attackMenuSelection + 1) % totalMenuItems;
        }
    }
    else if (input == 13) { // 엔터
        if (m_currentState == BattleState::MainMenu) {
            switch (m_mainMenuSelection) {
            case 0: // 공격
                m_currentState = BattleState::AttackMenu;
                m_attackMenuSelection = 0;
                m_statusMessage = L"사용할 스킬을 선택하세요.";
                break;
            case 1: // 방어
                m_playerParty[0]->GetAbilitySystemComponent()->GetAttributeSet()->bIsDefending = true;
                m_statusMessage = m_playerParty[0]->GetName() + L"이(가) 방어 태세를 갖춥니다!";
                m_currentState = BattleState::Busy;
                break;
            case 2: // 아이템
                m_statusMessage = L"아이템 가방이 비어있습니다!";
                // TODO: 아이템 로직
                break;
            case 3: // 도망가기
                m_statusMessage = L"성공적으로 도망쳤다!";
                m_currentState = BattleState::BattleEnd;
                break;
            }
        }
        else if (m_currentState == BattleState::AttackMenu) {
            vector<GameplayAbility*>& abilities = m_playerParty[0]->GetAbilitySystemComponent()->GrantedAbilities;
            int skillCount = static_cast<int>(abilities.size());
            if (m_attackMenuSelection < skillCount) { // 스킬 선택
                // TODO: 타겟 선택 로직 추가 필요
                m_statusMessage = abilities[m_attackMenuSelection]->ActivateAbility(m_playerParty[0], m_enemyParty[0]);
                m_currentState = BattleState::Busy;
            }
            else { // 뒤로가기
                m_currentState = BattleState::MainMenu;
                m_mainMenuSelection = 0;
                m_statusMessage = L"무엇을 할까?";
            }
        }
    }
}

void BattleManager::Update() {
    if (m_currentState == BattleState::Busy) {
        Draw(); // 행동 결과를 먼저 화면에 그림
        Sleep(2000);

        // 적 HP 확인
        if (m_enemyParty[0]->GetAbilitySystemComponent()->GetAttributeSet()->HP <= 0) {
            m_statusMessage = m_enemyParty[0]->GetName() + L"을(를) 물리쳤다!";
            m_currentState = BattleState::BattleEnd;
            return;
        }

        // 적 턴 진행
        m_playerParty[0]->GetAbilitySystemComponent()->GetAttributeSet()->bIsDefending = false;
        m_statusMessage = m_enemyParty[0]->GetName() + L"의 공격!";
        Draw(); Sleep(1000);

        vector<GameplayAbility*>& enemyAbilities = m_enemyParty[0]->GetAbilitySystemComponent()->GrantedAbilities;
        if (!enemyAbilities.empty()) {
            m_statusMessage = enemyAbilities[0]->ActivateAbility(m_enemyParty[0], m_playerParty[0]);
        }
        m_currentState = BattleState::Busy; // 적 행동 결과도 보여주기 위해 다시 Busy
        Draw(); Sleep(2000);

        // 플레이어 HP 확인
        if (m_playerParty[0]->GetAbilitySystemComponent()->GetAttributeSet()->HP <= 0) {
            m_statusMessage = m_playerParty[0]->GetName() + L"은(는) 쓰러졌다...";
            m_currentState = BattleState::BattleEnd;
            return;
        }

        // 플레이어 턴으로 복귀
        m_currentState = BattleState::MainMenu;
        m_statusMessage = L"무엇을 할까?";
    }
}

void BattleManager::Draw() {
    clearScreen();

    AttributeSet* playerAttr = m_playerParty[0]->GetAbilitySystemComponent()->GetAttributeSet();
    AttributeSet* monsterAttr = m_enemyParty[0]->GetAbilitySystemComponent()->GetAttributeSet();

    // --- 적 정보 UI (우측 상단) ---
    drawBox(45, 2, 30, 6);
    gotoxy(47, 3); wcout << m_enemyParty[0]->GetName() << L"      Lv. " << monsterAttr->Level;
    gotoxy(47, 4); wcout << drawStatBar(L"HP", monsterAttr->HP, monsterAttr->MaxHP, 15);
    gotoxy(49, 5); wcout << (int)monsterAttr->HP << L" / " << (int)monsterAttr->MaxHP;

    // --- 플레이어 정보 UI (좌측 하단) ---
    drawBox(2, 12, 30, 7);
    gotoxy(4, 13); wcout << m_playerParty[0]->GetName() << L"      Lv. " << playerAttr->Level;
    gotoxy(4, 14); wcout << drawStatBar(L"HP", playerAttr->HP, playerAttr->MaxHP, 15);
    gotoxy(6, 15); wcout << (int)playerAttr->HP << L" / " << (int)playerAttr->MaxHP;
    gotoxy(4, 16); wcout << L"MP: " << (int)playerAttr->MP << L" / " << (int)playerAttr->MaxMP;

    // --- 하단 UI (메시지, 메뉴) ---
    drawBox(2, 20, 52, 8);
    drawBox(55, 20, 25, 8);

    // 메시지 출력 (박스 크기에 맞게 좌표 조정)
    gotoxy(4, 22); wcout << m_statusMessage;

    // 메뉴 출력
    if (m_currentState == BattleState::MainMenu) {
        vector<wstring> options = { L"공격", L"방어", L"아이템", L"도망가기" };
        for (int i = 0; i < options.size(); ++i) {
            gotoxy(57, 22 + i);
            wcout << (i == m_mainMenuSelection ? L"> " : L"  ") << options[i];
        }
    }
    else if (m_currentState == BattleState::AttackMenu) {
        vector<wstring> attackOptions;
        const auto& abilities = m_playerParty[0]->GetAbilitySystemComponent()->GrantedAbilities;
        for (const auto& ability : abilities) {
            attackOptions.push_back(ability->GetName());
        }
        while (attackOptions.size() < 4) attackOptions.push_back(L"-");
        attackOptions.push_back(L"뒤로가기");

        for (int i = 0; i < attackOptions.size(); ++i) {
            gotoxy(57, 21 + i);
            wcout << (i == m_attackMenuSelection ? L"> " : L"  ") << attackOptions[i];
        }
    }
}
void BattleManager::PlayIntroAnimation()
{
    ShowConsoleCursor(false);
    clearScreen();

    // 1. 화면 깜빡임 효과 (3번)
    for (int i = 0; i < 3; ++i)
    {
        system("color F0");
        Sleep(60);
        system("color 0F");
        Sleep(60);
    }

    // 2. 위아래로 갈라지는 효과 (수정된 로직)
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int screenWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    int screenHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    // 먼저 화면 전체를 블록으로 채움
    for (int y = 0; y < screenHeight; ++y)
    {
        gotoxy(0, y);
        for (int x = 0; x < screenWidth / 2; ++x) // gotoxy가 x*2를 하므로 screenWidth/2 만큼 반복
        {
            wcout << L"██";
        }
    }

    // 중앙에서부터 위아래로 한 줄씩 공백으로 만들며 갈라지는 효과
    int centerY = screenHeight / 2;
    wstring blankLine(screenWidth, L' '); // 공백으로 채워진 한 줄

    for (int i = 0; i <= centerY; ++i)
    {
        // 중앙에서 위로 한 줄 지우기
        if (centerY - i >= 0) {
            gotoxy(0, centerY - i);
            wcout << blankLine;
        }
        // 중앙에서 아래로 한 줄 지우기
        if (centerY + i < screenHeight) {
            gotoxy(0, centerY + i);
            wcout << blankLine;
        }
        Sleep(25); // 애니메이션 속도 조절
    }
    clearScreen();
}