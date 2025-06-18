// AttributeSet.cpp
#include "AttributeSet.h"
#include <iostream> // wcout 사용

using namespace std;

AttributeSet::AttributeSet()
{
    // 캐릭터 생성 시 기본 능력치 설정
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

    // 파생 능력치 계산 및 현재 체력/마나 동기화
    UpdateDerivedAttributes();
    HP = MaxHP;
    MP = MaxMP;
}

void AttributeSet::SetOwnerName(wstring name)
{
    this->OwnerName = name;
}

// 파생(계산)되는 능력치를 업데이트
void AttributeSet::UpdateDerivedAttributes()
{
    // 힘 1당 MaxHP 2 증가, 지능 1당 MaxMP 5 증가
    MaxHP = BaseHP + (Strength * 2.0f);
    MaxMP = BaseMP + (Intelligence * 5.0f);
}

// 경험치 획득 및 레벨업 처리
void AttributeSet::AddExperience(int amount)
{
    Experience += amount;
    wcout << OwnerName << L"이(가) 경험치 " << amount << L"을(를) 획득했습니다!" << endl;

    while (Experience >= ExpToNextLevel)
    {
        Experience -= ExpToNextLevel;
        LevelUp();
    }
}

// 레벨업 처리
void AttributeSet::LevelUp()
{
    Level++;
    wcout << L"★★★★★ 레벨 업! ★★★★★" << endl;
    wcout << OwnerName << L"의 레벨이 " << Level << L"이(가) 되었습니다!" << endl;

    // 다음 레벨업에 필요한 경험치 증가 (예: 1.5배)
    ExpToNextLevel = static_cast<int>(ExpToNextLevel * 1.5f);

    // 레벨업 시 스탯 성장
    Strength += 2.0f;
    Agility += 2.0f;
    Intelligence += 1.0f;
    BaseHP += 10.0f;

    // 스탯 변경 후 파생 능력치 재계산
    UpdateDerivedAttributes();

    // 레벨업 시 체력과 마나를 최대로 회복
    HP = MaxHP;
    MP = MaxMP;
}