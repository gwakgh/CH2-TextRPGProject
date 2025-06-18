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
// �κ��丮 ���µ� �߰��� ���̹Ƿ� �̸� ����
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
    // 1. �ܼ� ȯ�� ����
    _setmode(_fileno(stdout), _O_U16TEXT);
    ShowConsoleCursor(false);

    m_isRunning = true;

    // 2. �ٽ� ������ ��ü ����
    m_player = new Player(L"���");
    m_field = new Field();

    // �÷��̾� �ʱ� ������ �� ��ų ����
    m_player->GetAbilitySystemComponent()->GrantAbility(new BasicAttack());
    m_player->GetInventoryComponent()->AddItem(new HealthPotion());

    // 3. ���� ������ �ʱ� ���¸� �̸� �غ��մϴ�.
    m_field->LoadMap(0);          // 0�� ��(����)�� �ε�
    m_player->SetPosition(13, 2);  // �÷��̾� �ʱ� ��ġ ����

    // 4. ��� ���� ���� ��ü���� �����մϴ�.
    m_states[GameStateID::MAIN_MENU] = new MainMenuState();
    m_states[GameStateID::FIELD] = new FieldState();
    m_states[GameStateID::INVENTORY] = new InventoryState();

    // 5. ��� ���¸� �ʱ�ȭ�մϴ�.
    for (auto const& pair : m_states)
    {
        pair.second->Init(this);
    }

    // 6. ���� ���¸� ���� �޴��� �����մϴ�.
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