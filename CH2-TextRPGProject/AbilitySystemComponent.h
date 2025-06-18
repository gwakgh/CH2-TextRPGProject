// AbilitySystemComponent.h
#pragma once
#include <vector>

// ���� ����
class AttributeSet;
class GameplayAbility;
class GameplayEffect;
class Actor;

class AbilitySystemComponent
{
public:
    AbilitySystemComponent();
    ~AbilitySystemComponent();

    // �ο��� �����Ƽ(��ų) ���
    std::vector<GameplayAbility*> GrantedAbilities;

    void InitAttributeSet();
    AttributeSet* GetAttributeSet() const;

    void GrantAbility(GameplayAbility* ability);
    void RemoveAbility(GameplayAbility* ability);
    void ApplyGameplayEffect(GameplayEffect* effect);

protected:
    // �� ������Ʈ�� �����ϴ� AttributeSet
    AttributeSet* OwnedAttributeSet;

};