// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/AnimInstances/AnimNotifyStates/PlayerAnimNotifyState.h"

#include "Common/PlayerControllers/WWPlayerController.h"
#include "Common/WWDebugHelper.h"
#include "YHG/PlayerCharacters/PlayerCharacter.h"

void UPlayerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	PlayerCharacter = Cast<APlayerCharacter>(WWCharacter);

	if (!PlayerCharacter)
	{
		Debug::Print(TEXT("PlayerAnimNotifyState : Failed Cast PlayerCharacter"));
		return;
	}
	
	WWPlayerController = Cast<AWWPlayerController>(Controller);

	if (!WWPlayerController)
	{
		Debug::Print(TEXT("PlayerAnimNotifyState : Failed Cast WWPlayerController"));
		return;
	}
}
