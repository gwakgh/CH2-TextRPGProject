// GameplayEffect.h
#pragma once
#include "AttributeSet.h"

// 속성 변경 연산의 종류
enum class EAttributeOperation
{
    Add,       // 덧셈
    Multiply,  // 곱셈
    Override   // 덮어쓰기
};

class GameplayEffect
{
public:
    // 어떤 능력치를(target), 어떤 연산으로(op), 얼마만큼(mag) 바꿀지 설정
    GameplayEffect(AttributeSet* target, EAttributeOperation op, float mag)
        : TargetAttributeSet(target), Operation(op), Magnitude(mag) {
    }

    AttributeSet* TargetAttributeSet;
    EAttributeOperation Operation;
    float Magnitude;
};