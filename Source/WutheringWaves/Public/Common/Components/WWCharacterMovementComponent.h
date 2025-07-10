// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WWCharacterMovementComponent.generated.h"

/**
//이 무브먼트를 적용시키면, Root Motion의 Z축 무효화가 취소됨
//그러나 지상(Walking 상태)에서의 Z축 변화는 적용되지 않음
	해결 방법1) SetMovementMode를 그 순간에만 Falling으로 바꿔서 제어하거나
	해결 방법2) 루트모션을 쓰지 말 것

//그리고, 점프 애니메이션 처럼 루트모션을 적용시키고, 앞으로 나아가야 하는 경우 등, 추가로 Velocity를 주어야 할 경우도 추천하지는 않음...
//by YHG
 */
UCLASS()
class WUTHERINGWAVES_API UWWCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual FVector ConstrainAnimRootMotionVelocity(const FVector& RootMotionVelocity, const FVector& CurrentVelocity) const override;
	//virtual void ApplyRootMotionToVelocity(float deltaTime) override;
};
