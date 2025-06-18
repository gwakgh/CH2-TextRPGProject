// Game.cpp
#include "Game.h"
#include "Player.h"
#include "Field.h"
#include "Enemy.h"
#include "Goblin.h"
#include "Boss.h"
#include "BasicAttack.h"
#include "HealthPotion.h"
#include "BattleManager.h"
#include "ConsoleUtils.h"
#include "MainMenuState.h"
#include "FieldState.h"
// 인벤토리 상태도 추가될 것이므로 미리 포함
#include "InventoryState.h"

#include <iostream>
#include <vector>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

using namespace std;
using namespace ConsoleUtils;
Game::Game()
{
    // 1. 콘솔 환경 설정
    _setmode(_fileno(stdout), _O_U16TEXT);
    ShowConsoleCursor(false);

    m_isRunning = true;

    // 2. 핵심 데이터 객체 생성
    m_player = new Player(L"용사");
    m_field = new Field();

    // 플레이어 초기 아이템 및 스킬 설정
    m_player->GetAbilitySystemComponent()->GrantAbility(new BasicAttack());
    m_player->GetInventoryComponent()->AddItem(new HealthPotion());

    // 3. 게임 월드의 초기 상태를 미리 준비합니다.
    m_field->LoadMap(0);          // 0번 맵(마을)을 로드
    m_player->SetPosition(13, 2);  // 플레이어 초기 위치 설정

    // 4. 모든 게임 상태 객체들을 생성합니다.
    m_states[GameStateID::MAIN_MENU] = new MainMenuState();
    m_states[GameStateID::FIELD] = new FieldState();
    m_states[GameStateID::INVENTORY] = new InventoryState();

    // 5. 모든 상태를 초기화합니다.
    for (auto const& pair : m_states)
    {
        pair.second->Init(this);
    }

    // 6. 시작 상태를 메인 메뉴로 설정합니다.
    m_currentState = m_states[GameStateID::MAIN_MENU];
}

Game::~Game()
{
    delete m_player;
    delete m_field;
    for (auto& pair : m_states) {
        delete pair.second;
    }
    m_states.clear();
}

void Game::Run()
{
    while (m_isRunning)
    {
        m_currentState->Draw();
        m_currentState->ProcessInput();
        m_currentState->Update();
        Sleep(7);
    }
}

void Game::ChangeState(GameStateID newStateID)
{
    if (newStateID == GameStateID::EXIT_GAME) {
        m_isRunning = false;
        return;
    }
    if (m_states.find(newStateID) != m_states.end()) {
        m_currentState = m_states[newStateID];
    }
}

void Game::StartBattle(Enemy* enemy)
{
    enemy->GetAbilitySystemComponent()->GrantAbility(new BasicAttack());
    vector<Actor*> playerParty = { m_player };
    vector<Actor*> enemyParty = { enemy };

    BattleManager battleManager(playerParty, enemyParty);
    battleManager.Run();

    delete enemy;
}