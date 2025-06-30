// Fill out your copyright notice in the Description page of Project Settings.


#include "YHG/PlayerCharacters/VerinaCharacter.h"

#include "Components/CapsuleComponent.h"

AVerinaCharacter::AVerinaCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 66.0f);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Assets/YHG/VerinaModel/VerinaModel.VerinaModel"));

	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -66.0f));
}
