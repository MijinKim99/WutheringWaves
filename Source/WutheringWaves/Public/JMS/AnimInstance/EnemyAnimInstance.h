// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AnimInstances/CharacterAnimInstance.h"
#include "Common/AnimInstances/WWAnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UEnemyAnimInstance : public UCharacterAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Locomotion")
	FVector Velocity;
	
};
