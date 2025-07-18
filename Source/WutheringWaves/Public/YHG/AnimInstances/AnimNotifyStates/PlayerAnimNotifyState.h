// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/AnimInstances/AnimNotifyStates/WWAnimNotifyState.h"
#include "PlayerAnimNotifyState.generated.h"

class AWWPlayerState;
class APlayerCharacter;
class AWWPlayerController;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UPlayerAnimNotifyState : public UWWAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	APlayerCharacter* PlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	AWWPlayerState* PlayerState;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	AWWPlayerController* WWPlayerController;
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
};
