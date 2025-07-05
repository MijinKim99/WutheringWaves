// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ActionControlANS.generated.h"

class AWWPlayerController;

/*플레이어의 액션 제어를 위한 클래스
 * 1. 특정시점에 어빌리티에서 네이티브로 전환
 * 2. 특정시점에 어빌리티에서 어빌리티로 전환
 * 필요이유 : GA태그를 통한 제어는 시점 상관없이 즉시 캔슬로만 작동해서, 이걸 만들어보았다.
 * 필요이유 : BP에서 Notify는 변수를 Set할 수가 없어 절약을 위해 만든 이유도 있다.

/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UActionControlANS : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	AWWPlayerController* WWPlayerController;
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

	UFUNCTION(BlueprintCallable)
	void CancelAllActiveAbilities(UAbilitySystemComponent* ASC);
};
