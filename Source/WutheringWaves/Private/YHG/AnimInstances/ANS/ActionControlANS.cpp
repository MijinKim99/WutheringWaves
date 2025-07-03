// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/AnimInstances/ANS/ActionControlANS.h"

#include "Common/PlayerControllers/WWPlayerController.h"
#include "Common/WWDebugHelper.h"

void UActionControlANS::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AController* Controller = MeshComp->GetOwner()->GetInstigatorController();
	WWPlayerController = Cast<AWWPlayerController>(MeshComp->GetOwner()->GetInstigatorController());

	if (!WWPlayerController)
	{
		Debug::Print(TEXT("CancelAbilityByNative : Failed Cast WWPlayerController"));
		return;
	}
}

void UActionControlANS::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}
