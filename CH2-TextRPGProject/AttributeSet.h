// AttributeSet.h
#pragma once

#include <string>

using namespace std;
class AttributeSet
{
public:
    AttributeSet();

    // 기본 스탯
    float Strength;
    float Agility;
    float Intelligence;

    // 방어 스탯
    float Defence;
    float MagicResistance;

    // 자원 (현재 값)
    float HP;
    float MP;

    // 최대 자원 (계산 값)
    float MaxHP;
    float MaxMP;

    // 최대치 계산용 기본값
    float BaseHP;
    float BaseMP;

    // 레벨 및 경험치
    int Level;
    int Experience;
    int ExpToNextLevel; // 다음 레벨 필요 경험치

	bool bIsDefending = false; // 방어 상태 여부

    void UpdateDerivedAttributes();
    void AddExperience(int amount);
    void SetOwnerName(wstring name);

private:
    void LevelUp();
    wstring OwnerName; // 소유자 이름을 저장할 변수
};