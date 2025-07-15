// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Attack/AttackCollisionSphereInstance.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWGameplayTags.h"
#include "Common/Characters/WWCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values
AAttackCollisionSphereInstance::AAttackCollisionSphereInstance()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AAttackCollisionSphereInstance::BeginPlay()
{
	Super::BeginPlay();
}

void AAttackCollisionSphereInstance::SetActive(bool IsActive, APawn* InInstigator)
{
	Super::SetActive(IsActive, InInstigator);
}

void AAttackCollisionSphereInstance::Deactivate()
{
	Super::Deactivate();
}

void AAttackCollisionSphereInstance::AttackOverlappingEnemies(const FVector& TargetLocation)
{
	SetActorLocation(TargetLocation);
	TArray<AActor*> OverlappingActors;
	SphereComponent->GetOverlappingActors(OverlappingActors);
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
}

void AAttackCollisionSphereInstance::SetSphereRadius(float InRadius)
{
	SphereComponent->SetSphereRadius(InRadius);
}

void AAttackCollisionSphereInstance::SetDamageEffect(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
}

void AAttackCollisionSphereInstance::SetHitReactEventTag(FGameplayTag InGameplayEventTag)
{
	HitReactEventTag = InGameplayEventTag;
}
