// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/PlayerCharacters/LightRoverCharacter.h"

#include "Components/CapsuleComponent.h"

ALightRoverCharacter::ALightRoverCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 77.0f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Assets/YHG/RoverModel/RoverModel.RoverModel"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -77.0f));
}
