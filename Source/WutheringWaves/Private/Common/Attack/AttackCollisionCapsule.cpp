// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Attack/AttackCollisionCapsule.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayCueFunctionLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWDebugHelper.h"
#include "Components/CapsuleComponent.h"

AAttackCollisionCapsule::AAttackCollisionCapsule()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AAttackCollisionCapsule::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAttackCollisionCapsule::OnBeginOverlap);
	CapsuleComponent->OnComponentHit.AddUniqueDynamic(this, &AAttackCollisionCapsule::OnHit);
}

void AAttackCollisionCapsule::SetActive(bool IsActive, APawn* InInstigator)
{
	Super::SetActive(IsActive, InInstigator);
	if (IsActive)
	{
		if (InInstigator)
		{
			InstigatorTeamId = Cast<IGenericTeamAgentInterface>(InInstigator->GetController())->GetGenericTeamId();
		}
	}
}

void AAttackCollisionCapsule::Deactivate()
{
	Super::Deactivate();
	HitTargetSet.Empty();
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UGameplayCueFunctionLibrary::RemoveGameplayCueOnActor(this, FXGameplayCueTag, FGameplayCueParameters());
}

void AAttackCollisionCapsule::OnHitTargetActor(AActor* HitActor)
{
	// 중복 검사
	if (HitTargetSet.Contains(HitActor))
	{
		return;
	}

	HitTargetSet.Add(HitActor);

	// GameplayEffectSpecHandle 적용
	UWWBlueprintFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(HitActor, GameplayEffectSpecHandle);

	// Gameplay Event 전달
	FGameplayEventData Data;
	Data.Instigator = GetInstigator();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, HitReactEventTag, Data);
}

void AAttackCollisionCapsule::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                              const FHitResult& SweepResult)
{
	//Debug::Print(FString::Printf(TEXT("Collision Begin Overlap : %s"), *OtherActor->GetActorNameOrLabel()));
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn)
	{
		return;
	}

	IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (!OtherTeamAgent)
	{
		return;
	}

	if (OtherTeamAgent->GetGenericTeamId() != InstigatorTeamId)
	{
		OnHitTargetActor(OtherActor);
	}
}

void AAttackCollisionCapsule::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

void AAttackCollisionCapsule::InitializeAndAttackWithCapsule(float Duration, float Radius, float HalfHeight, FVector Location,
                                                 FRotator Rotation,
                                                 const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle,
                                                 FGameplayTag InFXGameplayCueTag,
                                                 FGameplayTag InHitReactEventTag)
{
	CapsuleComponent->SetCapsuleSize(Radius, HalfHeight);
	SetActorLocation(Location);
	SetActorRotation(Rotation);
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
	FXGameplayCueTag = InFXGameplayCueTag;
	HitReactEventTag = InHitReactEventTag;
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(this, FXGameplayCueTag, FGameplayCueParameters());
	FTimerHandle DeactivateTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeactivateTimerHandle,this,&AAttackCollisionCapsule::Deactivate,Duration, false);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}
