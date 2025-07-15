// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AnimInstances/AnimNotifyStates/WWAnimNotifyState.h"
#include "EnemyAnimNotifyState.generated.h"

class AEnemyCharacter;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UEnemyAnimNotifyState : public UWWAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	AEnemyCharacter* OwningEnemyCharacter;


public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
	                         const FAnimNotifyEventReference& EventReference) override;
};
