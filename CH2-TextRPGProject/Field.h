// Field.h
#pragma once
#include <vector>
#include <string>
#include <map>
#include <utility> // std::pair

class Actor;
class NPC;

struct Portal
{
    int destMapId;
    int destX;
    int destY;
};

enum class TileType
{
    EMPTY = 0, WALL = 1, BUSH = 2,
    NPC_HEALER = 3, NPC_ITEM_SHOP = 4, NPC_SKILL_SHOP = 5,
    PORTAL = 8, BOSS = 9
};

class Field
{
public:
    Field();
    ~Field(); // ¼Ò¸êÀÚ Ãß°¡

    void LoadMap(int mapId);
    void Draw(Actor* player);
    bool IsWalkable(int x, int y);
    TileType GetTileType(int x, int y);
    NPC* GetNPAt(int x, int y);
    const Portal* GetPortalAt(int x, int y);
    int m_width;
    int m_height;

private:
    std::vector<std::vector<TileType>> m_mapData;
    std::vector<NPC*> m_npcs;
    std::map<std::pair<int, int>, Portal> m_portals;
};