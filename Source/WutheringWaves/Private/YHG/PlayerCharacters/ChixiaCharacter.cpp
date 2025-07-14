// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/PlayerCharacters/ChixiaCharacter.h"

#include "Components/CapsuleComponent.h"

AChixiaCharacter::AChixiaCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 77.0f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Assets/YHG/ChixiaModel/ChixiaModel.ChixiaModel"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -77.0f));
}
