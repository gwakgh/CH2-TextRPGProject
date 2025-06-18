// GameplayEffect.h
#pragma once
#include "AttributeSet.h"

// �Ӽ� ���� ������ ����
enum class EAttributeOperation
{
    Add,       // ����
    Multiply,  // ����
    Override   // �����
};

class GameplayEffect
{
public:
    // � �ɷ�ġ��(target), � ��������(op), �󸶸�ŭ(mag) �ٲ��� ����
    GameplayEffect(AttributeSet* target, EAttributeOperation op, float mag)
        : TargetAttributeSet(target), Operation(op), Magnitude(mag) {
    }

    AttributeSet* TargetAttributeSet;
    EAttributeOperation Operation;
    float Magnitude;
};