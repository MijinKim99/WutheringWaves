// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Characters/WWCharacter.h"
#include "MotionWarpingComponent.h"
#include "Common/WWDebugHelper.h"
#include "Common/Components/WWCharacterMovementComponent.h"

// Sets default values
AWWCharacter::AWWCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//VFX 지상 데칼 투영 영향을 줌
	GetMesh()->bReceivesDecals = false;

	//어빌리티 부착
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

AWWCharacter::AWWCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UWWCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//VFX 지상 데칼 투영 영향을 줌
	GetMesh()->bReceivesDecals = false;

	//어빌리티 부착
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

// Called when the game starts or when spawned
void AWWCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWWCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (StartupData.IsNull())
	{
		//Debug::Print(TEXT("WWCharacter : Can't find StartupData"));
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
void AWWCharacter::CancelActiveAbilities(UAbilitySystemComponent* ASC, FGameplayTag CancelTag)
{
	if (!ASC || !CancelTag.IsValid())
	{
		return;
	}
    
	for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (!Spec.IsActive())
			continue;

		const UGameplayAbility* AbilityCDO = Spec.Ability;
		if (!AbilityCDO)
			continue;

		// 어빌리티에 태그가 포함되어 있으면
		if (AbilityCDO->AbilityTags.HasTagExact(CancelTag))
		{
			ASC->CancelAbilityHandle(Spec.Handle);
		}
	}
}

void AWWCharacter::CancelAllActiveAbilities(UAbilitySystemComponent* ASC)
{
	if (!ASC)
	{
		Debug::Print(TEXT("WWCharacter : CancelAllActiveAbilities, Can't find ASC"));
		return;
	}

	for (FGameplayAbilitySpec& Spec : ASC->GetActivatableAbilities())
	{
		if (Spec.IsActive())
		{
			ASC->CancelAbilityHandle(Spec.Handle);
		}
	}
}*/

/*
// Called to bind functionality to input
void AWWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}
*/
