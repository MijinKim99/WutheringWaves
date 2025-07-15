// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/AnimNotifyState/EnemyAnimNotifyState.h"
#include "Common/WWDebugHelper.h"
#include "JMS/Character/EnemyCharacter.h"

void UEnemyAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	SkeletalMeshComponent = MeshComp;

	if (!SkeletalMeshComponent)
	{
		Debug::Print(TEXT("EnemyAnimNotifyState : Can't find SkeletalMeshComponent"));
		return;
	}

	
	OwningEnemyCharacter = Cast<AEnemyCharacter>(MeshComp->GetOwner());

	if (!OwningEnemyCharacter)
	{
		Debug::Print(TEXT("EnemyAnimNotifyState : Failed Cast OwningEnemyCharacter"));
		return;
	}
}
