// AttributeSet.h
#pragma once

#include <string>

using namespace std;
class AttributeSet
{
public:
    AttributeSet();

    // �⺻ ����
    float Strength;
    float Agility;
    float Intelligence;

    // ��� ����
    float Defence;
    float MagicResistance;

    // �ڿ� (���� ��)
    float HP;
    float MP;

    // �ִ� �ڿ� (��� ��)
    float MaxHP;
    float MaxMP;

    // �ִ�ġ ���� �⺻��
    float BaseHP;
    float BaseMP;

    // ���� �� ����ġ
    int Level;
    int Experience;
    int ExpToNextLevel; // ���� ���� �ʿ� ����ġ

	bool bIsDefending = false; // ��� ���� ����

    void UpdateDerivedAttributes();
    void AddExperience(int amount);
    void SetOwnerName(wstring name);

private:
    void LevelUp();
    wstring OwnerName; // ������ �̸��� ������ ����
};