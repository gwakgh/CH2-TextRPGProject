// FieldState.cpp
#include "FieldState.h"
#include "Game.h"
#include "Player.h"
#include "Field.h"
#include "NPC.h"
#include "Goblin.h"
#include "Boss.h"

#include <conio.h>
#include <random>

using namespace std;

void FieldState::Init(Game* game) { m_game = game; }

void FieldState::ProcessInput()
{
    int input = _getch();

    if (input == 'i' || input == 'I')
    {
        m_game->ChangeState(GameStateID::INVENTORY);
    }
    else if (input == 'z' || input == 'Z')
    {
        int targetX = m_game->m_player->GetX();
        int targetY = m_game->m_player->GetY();
        switch (m_game->m_player->GetDirection())
        {
        case Direction::UP:    targetY--; break;
        case Direction::DOWN:  targetY++; break;
        case Direction::LEFT:  targetX--; break;
        case Direction::RIGHT: targetX++; break;
        }

        NPC* targetNpc = m_game->m_field->GetNPAt(targetX, targetY);
        if (targetNpc != nullptr)
        {
            if (targetNpc->GetType() == NPCType::BOSS)
            {
                m_game->StartBattle(new Boss());
            }
            else {
                targetNpc->Interact(m_game->m_player);
            }
        }
    }
    else if (input == 224) {
        int arrow_code = _getch();

        int newX = m_game->m_player->GetX();
        int newY = m_game->m_player->GetY();

        if (arrow_code == 72) { m_game->m_player->SetDirection(Direction::UP); newY--; }
        else if (arrow_code == 80) { m_game->m_player->SetDirection(Direction::DOWN); newY++; }
        else if (arrow_code == 75) { m_game->m_player->SetDirection(Direction::LEFT); newX--; }
        else if (arrow_code == 77) { m_game->m_player->SetDirection(Direction::RIGHT); newX++; }

        if (m_game->m_field->IsWalkable(newX, newY))
        {
            m_game->m_player->SetPosition(newX, newY);

            const Portal* portal = m_game->m_field->GetPortalAt(newX, newY);
            if (portal != nullptr)
            {
                int destMapId = portal->destMapId;
                int destX = portal->destX;
                int destY = portal->destY;
                m_game->m_field->LoadMap(destMapId);
                m_game->m_player->SetPosition(destX, destY);
            }
            else
            {
                TileType currentTile = m_game->m_field->GetTileType(newX, newY);
                if (currentTile == TileType::BUSH)
                {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> distrib(1, 100);
					if (distrib(gen) <= 10) // 10% 확률로 전투 발생 ★
                    {
                        m_game->StartBattle(new Goblin());
                    }
                }
            }
        }
    }
}

void FieldState::Update() { /* 현재는 비워둠 */ }

void FieldState::Draw() {
    m_game->m_field->Draw(m_game->m_player);
}