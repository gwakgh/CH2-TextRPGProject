// AbilitySystemComponent.cpp
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayAbility.h" // 소멸자에서 GrantedAbilities를 순회하기 위해 포함
#include "GameplayEffect.h" // ApplyGameplayEffect 메서드에서 사용하기 위해 포함

AbilitySystemComponent::AbilitySystemComponent()
{
    // ASC 생성 시, 자신만의 AttributeSet을 생성하여 소유
    this->OwnedAttributeSet = new AttributeSet();
}

AbilitySystemComponent::~AbilitySystemComponent()
{
    // 소유했던 AttributeSet의 메모리 해제
    delete this->OwnedAttributeSet;

    // 부여되었던 모든 어빌리티의 메모리 해제
    for (GameplayAbility* ability : GrantedAbilities)
    {
        delete ability;
    }
    GrantedAbilities.clear();
}

AttributeSet* AbilitySystemComponent::GetAttributeSet() const
{
    return this->OwnedAttributeSet;
}

void AbilitySystemComponent::GrantAbility(GameplayAbility* ability)
{
    if (ability)
    {
        GrantedAbilities.push_back(ability);
    }
}
void AbilitySystemComponent::ApplyGameplayEffect(GameplayEffect* effect)
{
    if (!effect || !effect->TargetAttributeSet) return;

    // 지금은 HP에 대한 덧셈 연산만 간단히 구현
    // TODO: 향후 다양한 능력치와 연산(곱셈, 버프 등)을 처리하도록 확장
    if (effect->Operation == EAttributeOperation::Add)
    {
        effect->TargetAttributeSet->HP += effect->Magnitude;

        // HP가 최대 HP를 넘지 않도록 보정
        if (effect->TargetAttributeSet->HP > effect->TargetAttributeSet->MaxHP)
        {
            effect->TargetAttributeSet->HP = effect->TargetAttributeSet->MaxHP;
        }
    }
}
void AbilitySystemComponent::RemoveAbility(GameplayAbility* ability) {}