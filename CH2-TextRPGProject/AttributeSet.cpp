// AttributeSet.cpp
#include "AttributeSet.h"
#include <iostream> // wcout ���

using namespace std;

AttributeSet::AttributeSet()
{
    // ĳ���� ���� �� �⺻ �ɷ�ġ ����
    Level = 1;
    Experience = 0;
    ExpToNextLevel = 100;

    Strength = 5.0f;
    Agility = 5.0f;
    Intelligence = 5.0f;
    Defence = 5.0f;
    MagicResistance = 5.0f;

    BaseHP = 50.0f;
    BaseMP = 30.0f;

    // �Ļ� �ɷ�ġ ��� �� ���� ü��/���� ����ȭ
    UpdateDerivedAttributes();
    HP = MaxHP;
    MP = MaxMP;
}

void AttributeSet::SetOwnerName(wstring name)
{
    this->OwnerName = name;
}

// �Ļ�(���)�Ǵ� �ɷ�ġ�� ������Ʈ
void AttributeSet::UpdateDerivedAttributes()
{
    // �� 1�� MaxHP 2 ����, ���� 1�� MaxMP 5 ����
    MaxHP = BaseHP + (Strength * 2.0f);
    MaxMP = BaseMP + (Intelligence * 5.0f);
}

// ����ġ ȹ�� �� ������ ó��
void AttributeSet::AddExperience(int amount)
{
    Experience += amount;
    wcout << OwnerName << L"��(��) ����ġ " << amount << L"��(��) ȹ���߽��ϴ�!" << endl;

    while (Experience >= ExpToNextLevel)
    {
        Experience -= ExpToNextLevel;
        LevelUp();
    }
}

// ������ ó��
void AttributeSet::LevelUp()
{
    Level++;
    wcout << L"�ڡڡڡڡ� ���� ��! �ڡڡڡڡ�" << endl;
    wcout << OwnerName << L"�� ������ " << Level << L"��(��) �Ǿ����ϴ�!" << endl;

    // ���� �������� �ʿ��� ����ġ ���� (��: 1.5��)
    ExpToNextLevel = static_cast<int>(ExpToNextLevel * 1.5f);

    // ������ �� ���� ����
    Strength += 2.0f;
    Agility += 2.0f;
    Intelligence += 1.0f;
    BaseHP += 10.0f;

    // ���� ���� �� �Ļ� �ɷ�ġ ����
    UpdateDerivedAttributes();

    // ������ �� ü�°� ������ �ִ�� ȸ��
    HP = MaxHP;
    MP = MaxMP;
}