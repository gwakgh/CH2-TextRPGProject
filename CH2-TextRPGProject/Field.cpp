// Field.cpp
#include "Field.h"
#include "Player.h"
#include "NPC.h"
#include "ConsoleUtils.h"
#include <iostream>

using namespace std;
using namespace ConsoleUtils;

Field::Field() : m_width(0), m_height(0) {}

// Field가 소멸될 때, 가지고 있던 NPC들의 메모리를 안전하게 해제
Field::~Field()
{
    for (NPC* npc : m_npcs)
    {
        delete npc;
    }
    m_npcs.clear();
}

void Field::LoadMap(int mapId)
{
    for (NPC* npc : m_npcs) { delete npc; }
    m_npcs.clear();
    m_portals.clear();
    m_mapData.clear();

    vector<vector<int>> mapRawData;

    switch (mapId)
    {
    case 0: // 마을
        mapRawData = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1},
            {1,0,1,0,0,1,0,0,0,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,1},
            {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,5,0,1,0,0,1},
            {1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,0,0,1},
            {1,0,1,1,0,1,1,1,1,0,0,1,1,0,1,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
            {1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1},
            {1,0,0,1,0,4,0,0,0,0,0,1,0,3,0,1,0,0,0,0,1,1,1,0,0,1,1,0,0,1},
            {1,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        };
        m_portals[{29, 10}] = { 1, 1, 3 };
        m_portals[{29, 11}] = { 1, 1, 4 };
        break;

    case 1: // 사냥터 1
        mapRawData = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,2,2,2,0,1,1,0,1},
            {8,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,2,2,2,0,1,0,0,1},
            {8,0,0,0,0,0,0,0,0,1,0,1,2,2,2,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,1,2,2,2,0,1,1,1,1,1,0,1,1,1,1,0,0,0,1},
            {1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1},
            {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1},
            {1,0,0,1,0,0,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,1,0,0,1,0,0,0,1},
            {1,0,0,1,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
            {1,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,8,8,1,1,1,1},
        };
        m_portals[{0, 3}] = { 0, 28, 10 };
        m_portals[{0, 4}] = { 0, 28, 11 };
        m_portals[{24, 13}] = { 2 , 3,1 };
        m_portals[{25, 13}] = { 2 , 4,1 };
        break;
    case 2: // 사냥터 2
        mapRawData = {
            {1,1,1,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,2,2,2,2,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,1},
            {1,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,1,1},
            {1,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,2,2,2,2,2,1,1},
            {1,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,2,2,2,1,1,1,1},
            {1,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,2,2,2,1,1,1,1,1},
            {1,2,2,2,2,2,1,1,1,2,2,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1},
            {1,2,2,2,2,2,1,1,1,2,2,1,2,2,2,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
            {1,2,2,2,2,2,1,1,1,2,2,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
            {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,1,1,1},
            {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        };
        m_portals[{3, 0}] = { 1, 24, 12 };
        m_portals[{4, 0}] = { 1, 25, 12 };
        m_portals[{0, 11}] = { 3 , 28,6 };
        m_portals[{0, 12}] = { 3 , 28,7 };
        break; 
    case 3: // 사냥터 3
            mapRawData = {
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                {1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
                {1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,1},
                {8,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,8},
                {8,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,8},
                {1,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1},
                {1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1},
                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            };
            m_portals[{29, 6}] = { 2, 1, 11 };
            m_portals[{29, 7}] = { 2, 1, 12 };
            m_portals[{0, 6}] = { 4 , 14,11 };
            m_portals[{0, 7}] = { 4 , 14,11 };
            break;
    case 4: // 보스방
        mapRawData = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,1,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
            {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
            {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
            {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
            {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
            {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,8,8,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        };
        m_portals[{13, 13}] = { 3, 1, 6 };
        m_portals[{14, 13}] = { 3, 1, 7 };
        m_portals[{15, 13}] = { 3, 1, 7 };
        break;
    default:
        break;
    }

    if (mapRawData.empty()) return;

    m_height = static_cast<int>(mapRawData.size());
    m_width = static_cast<int>(mapRawData[0].size());

    m_mapData.assign(m_height, vector<TileType>(m_width));
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            int tileValue = mapRawData[y][x];
            m_mapData[y][x] = static_cast<TileType>(tileValue);

            switch (static_cast<TileType>(tileValue))
            {
            case TileType::NPC_HEALER:
                m_npcs.push_back(new NPC(L"† 간호사", NPCType::HEALER, x, y));
                break;
            case TileType::NPC_ITEM_SHOP:
                m_npcs.push_back(new NPC(L"● 상점주인", NPCType::SHOP_ITEM, x, y));
                break;
            case TileType::NPC_SKILL_SHOP:
                m_npcs.push_back(new NPC(L"◈ 스킬마스터", NPCType::SHOP_SKILL, x, y));
                break;
            case TileType::BOSS:
                m_npcs.push_back(new NPC(L"▼ 보스", NPCType::BOSS, x, y));
                break;
            default:
                break;
            }
        }
    }
}

void Field::Draw(Actor* player)
{
    clearScreen();
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            gotoxy(x * 2, y);
            switch (m_mapData[y][x])
            {
            case TileType::EMPTY:   wcout << L"· "; break;
            case TileType::WALL:    wcout << L"▒"; break;
            case TileType::BUSH:    wcout << L"∗∗"; break;
            case TileType::NPC_HEALER: case TileType::NPC_ITEM_SHOP: case TileType::NPC_SKILL_SHOP: case TileType::BOSS:
                wcout << L"· ";
                break;
            case TileType::PORTAL:
                wcout << L"回 ";
                break;
            default:                wcout << L"  "; break;
            }
        }
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    WORD saved_attributes = csbi.wAttributes;

    for (NPC* npc : m_npcs)
    {
        gotoxy(npc->GetX() * 2, npc->GetY());
        switch (npc->GetType())
        {
		case NPCType::HEALER:   wcout << L"† "; break;
		case NPCType::SHOP_ITEM: wcout << L"● "; break;
		case NPCType::SHOP_SKILL: wcout << L"◈ "; break;
		case NPCType::BOSS:
            // 글자를 출력하기 전에 색상 변경
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            wcout << L"▼ ";
            // 글자 출력 후 즉시 원래 색상으로 복원
            SetConsoleTextAttribute(hConsole, saved_attributes);
            break;
        }
    }
    Player* p = static_cast<Player*>(player);
    gotoxy(p->GetX() * 2, p->GetY());
    switch (p->GetDirection())
    {
    case Direction::UP:     wcout << L"▲ "; break;
    case Direction::DOWN:   wcout << L"▼ "; break;
    case Direction::LEFT:   wcout << L"◀ "; break;
    case Direction::RIGHT:  wcout << L"▶ "; break;
    }

    /*
	// 디버그용 플레이어 위치 출력
    gotoxy(0, m_height + 1);
    wcout << L"Player Position: (" << p->GetX() << L", " << p->GetY() << L")   ";
    */
}


bool Field::IsWalkable(int x, int y)
{
    if (x < 0 || x >= m_width || y < 0 || y >= m_height) return false;
    if (m_mapData[y][x] == TileType::WALL) return false;
    if (GetNPAt(x, y) != nullptr) return false;
    return true;
}

const Portal* Field::GetPortalAt(int x, int y)
{
    auto it = m_portals.find({ x, y });
    if (it != m_portals.end())
    {
        return &it->second;
    }
    return nullptr;
}

NPC* Field::GetNPAt(int x, int y)
{
    for (NPC* npc : m_npcs)
    {
        if (npc->GetX() == x && npc->GetY() == y)
        {
            return npc;
        }
    }
    return nullptr;
}

TileType Field::GetTileType(int x, int y)
{
    // 맵 경계를 벗어나면 충돌을 방지하기 위해 WALL로 간주
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
    {
        return TileType::WALL;
    }
    // 맵 경계 안이라면 해당 좌표의 타일 타입을 반환
    return m_mapData[y][x];
}