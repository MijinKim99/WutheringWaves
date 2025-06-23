// Fill out your copyright notice in the Description page of Project Settings.


#include "WWCopy/Public/Characters/Boss/ScarCharacter.h"
#include "DrawDebugHelpers.h"
#include "AbilitySystem/WWAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/Enemy/ScarAttributeSet.h"

AScarCharacter::AScarCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Assets/Scar/Scar1Phase.Scar1Phase"));
	if (MeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(MeshAsset.Object);
	}
}

void AScarCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AScarCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
