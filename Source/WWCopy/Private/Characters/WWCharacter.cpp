// Fill out your copyright notice in the Description page of Project Settings.


#include "WWCopy/Public/Characters/WWCharacter.h"

#include "AbilitySystem/WWAbilitySystemComponent.h"
#include "AbilitySystem/AttributeSet/WWAttributeSet.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AWWCharacter::AWWCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// Ability System
	WWAbilitySystemComponent = CreateDefaultSubobject<UWWAbilitySystemComponent>(TEXT("WWAbilitySystemComponent"));
	WWAttributeSet = CreateDefaultSubobject<UWWAttributeSet>(TEXT("WWAttributeSet"));

}

UPawnUIComponent* AWWCharacter::GetPawnUIComponent() const
{
	// 자식 클래스에서 구현
	return nullptr;
}

UAbilitySystemComponent* AWWCharacter::GetAbilitySystemComponent() const
{
	return WWAbilitySystemComponent;
}

void AWWCharacter::BeginPlay()
{
	Super::BeginPlay();
}
