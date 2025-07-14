// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/AnimInstances/AnimNotifyStates/PlayerAnimNotifyState.h"

#include "Common/PlayerControllers/WWPlayerController.h"
#include "Common/WWDebugHelper.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"

void UPlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	SkeletalMeshComponent = MeshComp;

	if (!SkeletalMeshComponent)
	{
		Debug::Print(TEXT("PlayerAnimNotifyState : Can't find SkeletalMeshComponent"));
		return;
	}

	
	PlayerCharacter = Cast<APlayerCharacter>(MeshComp->GetOwner());

	if (!PlayerCharacter)
	{
		Debug::Print(TEXT("PlayerAnimNotifyState : Failed Cast PlayerCharacter"));
		return;
	}
	
	WWPlayerController = Cast<AWWPlayerController>(MeshComp->GetOwner()->GetInstigatorController());

	if (!WWPlayerController)
	{
		Debug::Print(TEXT("PlayerAnimNotifyState : Failed Cast WWPlayerController"));
		return;
	}
}
