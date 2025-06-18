// NPC.cpp
#include "NPC.h"
#include "Player.h" // Player의 전체 정의를 알기 위해 포함
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ConsoleUtils.h" // DrawDialogueBox를 직접 호출하기 위해

using namespace std;
using namespace ConsoleUtils; // 네임스페이스 사용

NPC::NPC(wstring name, NPCType type, int x, int y)
    : Actor(name), m_type(type)
{
    m_x = x;
    m_y = y;
}
NPCType NPC::GetType() const
{
    return m_type;
}

// NPC 타입에 따라 다른 상호작용 메시지를 반환
wstring NPC::GetInteractionMessage()
{
    switch (m_type)
    {
    case NPCType::HEALER:
        return L"지친 용사여, 상처를 치료해 드리겠습니다.";
    case NPCType::SHOP_ITEM:
        return L"필요한 물건이 있나? 한번 둘러보게.";
    case NPCType::SHOP_SKILL:
        return L"새로운 기술을 가르쳐주지.";
    case NPCType::BOSS:
        return L"BOSS";
    default:
        return L"…….";
    }
}
void NPC::Interact(Player* player)
{
    wstring message;
    switch (m_type)
    {
    case NPCType::HEALER:
        message = L"지친 용사여, 상처를 치료해 드리겠습니다.";
        DrawDialogueBox(message);

        // 플레이어의 HP와 MP를 최대로 회복
        {
            AttributeSet* attr = player->GetAbilitySystemComponent()->GetAttributeSet();
            attr->HP = attr->MaxHP;
            attr->MP = attr->MaxMP;
        }

        message = L"당신의 모든 상처와 피로가 회복되었습니다.";
        DrawDialogueBox(message);
        break;

    case NPCType::SHOP_ITEM:
        // TODO: 상점 기능 구현
        message = L"필요한 물건이 있나? (상점 기능 미구현)";
        DrawDialogueBox(message);
        break;

    case NPCType::SHOP_SKILL:
        // TODO: 스킬 상점 기능 구현
        message = L"새로운 기술을 가르쳐주지. (상점 기능 미구현)";
        DrawDialogueBox(message);
        break;
    }
}