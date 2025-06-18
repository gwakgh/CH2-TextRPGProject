// AbilitySystemComponent.h
#pragma once
#include <vector>

// 전방 선언
class AttributeSet;
class GameplayAbility;
class GameplayEffect;
class Actor;

class AbilitySystemComponent
{
public:
    AbilitySystemComponent();
    ~AbilitySystemComponent();

    // 부여된 어빌리티(스킬) 목록
    std::vector<GameplayAbility*> GrantedAbilities;

    void InitAttributeSet();
    AttributeSet* GetAttributeSet() const;

    void GrantAbility(GameplayAbility* ability);
    void RemoveAbility(GameplayAbility* ability);
    void ApplyGameplayEffect(GameplayEffect* effect);

protected:
    // 이 컴포넌트가 소유하는 AttributeSet
    AttributeSet* OwnedAttributeSet;

};