// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Characters/WWCharacter.h"

#include "Common/WWDebugHelper.h"
#include "Common/AbilitySystem/WWAbilitySystemComponent.h"
#include "Common/AbilitySystem/WWAttributeSet.h"

// Sets default values
AWWCharacter::AWWCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//VFX 지상 데칼 투영 영향을 줌
	GetMesh()->bReceivesDecals = false;

	//어빌리티 부착
	WWAbilitySystemComponent = CreateDefaultSubobject<UWWAbilitySystemComponent>(TEXT("WWAbilitySystemComponent"));
	WWAttributeSet = CreateDefaultSubobject<UWWAttributeSet>(TEXT("WWAttributeSet"));
}

// Called when the game starts or when spawned
void AWWCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWWCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (WWAbilitySystemComponent)
	{
		WWAbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	if (StartupData.IsNull())
	{
		Debug::Print(TEXT("WWCharacter : Can't find StartupData"));
		return;
	}
}

// Called every frame
void AWWCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPawnUIComponent* AWWCharacter::GetPawnUIComponent() const
{
	// 자식에서 구현
	return nullptr;
}

UPawnCombatComponent* AWWCharacter::GetPawnCombatComponent() const
{
	// 자식에서 구현
	return nullptr;
}

/*
// Called to bind functionality to input
void AWWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}
*/
