// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/AnimInstances/AnimNotifies/WWAnimNotify.h"

void UWWAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
		if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
		{
			
		}
}
