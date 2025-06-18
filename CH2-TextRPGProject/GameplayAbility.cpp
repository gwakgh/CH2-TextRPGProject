// GameplayAbility.cpp
#include "GameplayAbility.h"

using namespace std;

GameplayAbility::GameplayAbility(wstring name, float ad_ratio, float ap_ratio)
    : Name(name), AD_Ratio(ad_ratio), AP_Ratio(ap_ratio)
{
}

wstring GameplayAbility::GetName() const
{
    return Name;
}