// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Attack/AttackCollisionCapsuleInstance.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayCueFunctionLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/Characters/WWCharacter.h"
#include "Components/CapsuleComponent.h"


class AWWCharacter;
// Sets default values
AAttackCollisionCapsuleInstance::AAttackCollisionCapsuleInstance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Block);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AAttackCollisionCapsuleInstance::BeginPlay()
{
	Super::BeginPlay();
}

void AAttackCollisionCapsuleInstance::SetActive(bool IsActive, APawn* InInstigator)
{
	Super::SetActive(IsActive, InInstigator);
	if (IsActive)
	{
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		if (InInstigator)
		{
			InstigatorTeamId = Cast<IGenericTeamAgentInterface>(InInstigator->GetController())->GetGenericTeamId();
		}
	}
	else
	{
		CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AAttackCollisionCapsuleInstance::Deactivate()
{
	Super::Deactivate();
	
}

void AAttackCollisionCapsuleInstance::AttackOverlappingEnemies(const FVector& TargetLocation)
{
	
	TArray<AActor*> OverlappingActors;
	CapsuleComponent->GetOverlappingActors(OverlappingActors);
	for (AActor* FoundActor : OverlappingActors)
	{
		// 캐릭터인지 검사
		AWWCharacter* FoundCharacter = Cast<AWWCharacter>(FoundActor);
		if (!FoundCharacter)
		{
			continue;
		}
		// 팀 지정 되어있는지 검사
		IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(FoundCharacter->GetController());
		if (!OtherTeamAgent)
		{
			continue;
		}
		// 같은 팀인지 검사
		if (OtherTeamAgent->GetGenericTeamId() != InstigatorTeamId)
		{
			//GameplayEffectSpecHandle 적용
			UWWBlueprintFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(
				FoundCharacter, GameplayEffectSpecHandle);
			//Gameplay Event 전달
			FGameplayEventData Data;
			Data.Instigator = GetInstigator();
			Data.Target = FoundActor;
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(FoundCharacter,
			                                                         HitReactEventTag, Data);
			//Gameplay Effect 적용
		}
	}
	Deactivate();
}

void AAttackCollisionCapsuleInstance::SetCapsuleSize(float InRadius, float InHalfHeight)
{
	CapsuleComponent->SetCapsuleSize(InRadius,InHalfHeight);
}


void AAttackCollisionCapsuleInstance::SetDamageEffect(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
}

void AAttackCollisionCapsuleInstance::SetHitReactEventTag(FGameplayTag InGameplayEventTag)
{
	HitReactEventTag = InGameplayEventTag;
}
void AAttackCollisionCapsuleInstance::SetAttackVFXGameplayCueTag(FGameplayTag InGameplayCueTag)
{
	AttackFXGameplayCueTag = InGameplayCueTag;
}

