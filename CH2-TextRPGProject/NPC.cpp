// NPC.cpp
#include "NPC.h"
#include "Player.h" // Player�� ��ü ���Ǹ� �˱� ���� ����
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "ConsoleUtils.h" // DrawDialogueBox�� ���� ȣ���ϱ� ����

using namespace std;
using namespace ConsoleUtils; // ���ӽ����̽� ���

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

// NPC Ÿ�Կ� ���� �ٸ� ��ȣ�ۿ� �޽����� ��ȯ
wstring NPC::GetInteractionMessage()
{
    switch (m_type)
    {
    case NPCType::HEALER:
        return L"��ģ ��翩, ��ó�� ġ���� �帮�ڽ��ϴ�.";
    case NPCType::SHOP_ITEM:
        return L"�ʿ��� ������ �ֳ�? �ѹ� �ѷ�����.";
    case NPCType::SHOP_SKILL:
        return L"���ο� ����� ����������.";
    case NPCType::BOSS:
        return L"BOSS";
    default:
        return L"����.";
    }
}
void NPC::Interact(Player* player)
{
    wstring message;
    switch (m_type)
    {
    case NPCType::HEALER:
        message = L"��ģ ��翩, ��ó�� ġ���� �帮�ڽ��ϴ�.";
        DrawDialogueBox(message);

        // �÷��̾��� HP�� MP�� �ִ�� ȸ��
        {
            AttributeSet* attr = player->GetAbilitySystemComponent()->GetAttributeSet();
            attr->HP = attr->MaxHP;
            attr->MP = attr->MaxMP;
        }

        message = L"����� ��� ��ó�� �Ƿΰ� ȸ���Ǿ����ϴ�.";
        DrawDialogueBox(message);
        break;

    case NPCType::SHOP_ITEM:
        // TODO: ���� ��� ����
        message = L"�ʿ��� ������ �ֳ�? (���� ��� �̱���)";
        DrawDialogueBox(message);
        break;

    case NPCType::SHOP_SKILL:
        // TODO: ��ų ���� ��� ����
        message = L"���ο� ����� ����������. (���� ��� �̱���)";
        DrawDialogueBox(message);
        break;
    }
}