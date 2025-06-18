// AbilitySystemComponent.cpp
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "GameplayAbility.h" // �Ҹ��ڿ��� GrantedAbilities�� ��ȸ�ϱ� ���� ����
#include "GameplayEffect.h" // ApplyGameplayEffect �޼��忡�� ����ϱ� ���� ����

AbilitySystemComponent::AbilitySystemComponent()
{
    // ASC ���� ��, �ڽŸ��� AttributeSet�� �����Ͽ� ����
    this->OwnedAttributeSet = new AttributeSet();
}

AbilitySystemComponent::~AbilitySystemComponent()
{
    // �����ߴ� AttributeSet�� �޸� ����
    delete this->OwnedAttributeSet;

    // �ο��Ǿ��� ��� �����Ƽ�� �޸� ����
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

    // ������ HP�� ���� ���� ���길 ������ ����
    // TODO: ���� �پ��� �ɷ�ġ�� ����(����, ���� ��)�� ó���ϵ��� Ȯ��
    if (effect->Operation == EAttributeOperation::Add)
    {
        effect->TargetAttributeSet->HP += effect->Magnitude;

        // HP�� �ִ� HP�� ���� �ʵ��� ����
        if (effect->TargetAttributeSet->HP > effect->TargetAttributeSet->MaxHP)
        {
            effect->TargetAttributeSet->HP = effect->TargetAttributeSet->MaxHP;
        }
    }
}
void AbilitySystemComponent::RemoveAbility(GameplayAbility* ability) {}