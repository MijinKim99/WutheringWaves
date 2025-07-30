// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/AnimInstances/AnimNotifyStates/WWAnimNotifyState.h"

#include "Common/WWDebugHelper.h"
#include "Common/Characters/WWCharacter.h"

void UWWAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	
	SkeletalMeshComponent = MeshComp;

	if (!SkeletalMeshComponent)
	{
		//Debug::Print(TEXT("WWAnimNotifyState : Can't find SkeletalMeshComponent"));
		return;
	}
	
	WWCharacter = Cast<AWWCharacter>(SkeletalMeshComponent->GetOwner());

	if (!WWCharacter)
	{
		//Debug::Print(TEXT("WWAnimNotifyState : Failed Cast WWCharacter"));
		return;
	}
	
	Controller = WWCharacter->GetController();

	if (!Controller)
	{
		//Debug::Print(TEXT("WWAnimNotifyState : Can't find Controller"));
		return;
	}
	
}
