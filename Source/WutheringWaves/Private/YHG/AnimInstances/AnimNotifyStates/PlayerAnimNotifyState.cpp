// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/AnimInstances/AnimNotifyStates/PlayerAnimNotifyState.h"

#include "Common/PlayerControllers/WWPlayerController.h"
#include "Common/WWDebugHelper.h"

void UPlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration, const FAnimNotifyEventReference& EventReference)
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
