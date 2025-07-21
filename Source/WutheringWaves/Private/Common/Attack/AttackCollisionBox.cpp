// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Attack/AttackCollisionBox.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayCueFunctionLibrary.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWDebugHelper.h"
#include "Components/BoxComponent.h"

AAttackCollisionBox::AAttackCollisionBox()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

void AAttackCollisionBox::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAttackCollisionBox::OnBeginOverlap);
	BoxComponent->OnComponentHit.AddUniqueDynamic(this, &AAttackCollisionBox::OnHit);
}

void AAttackCollisionBox::SetActive(bool IsActive, APawn* InInstigator)
{
	Super::SetActive(IsActive, InInstigator);
	if (IsActive)
	{
		if (InInstigator)
		{
			IGenericTeamAgentInterface* GenericTeamAgentInterface = Cast<IGenericTeamAgentInterface>(
				InInstigator->GetController());
			if (GenericTeamAgentInterface)
			{
				InstigatorTeamId = GenericTeamAgentInterface->GetGenericTeamId();
			}
		}
	}
}

void AAttackCollisionBox::Deactivate()
{
	Super::Deactivate();
	HitTargetSet.Empty();
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UGameplayCueFunctionLibrary::RemoveGameplayCueOnActor(this, FXGameplayCueTag, FGameplayCueParameters());
	bIsAttached = false;
	BoxComponent->SetHiddenInGame(true);
	BoxComponent->SetLineThickness(0.0f);
}

void AAttackCollisionBox::OnHitTargetActor(AActor* HitActor)
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

void AAttackCollisionBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                         const FHitResult& SweepResult)
{
	Debug::Print(FString::Printf(TEXT("Collision Begin Overlap : %s"), *OtherActor->GetActorNameOrLabel()));
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

void AAttackCollisionBox::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                FVector NormalImpulse, const FHitResult& Hit)
{
}

void AAttackCollisionBox::InitializeAndAttackWithBox(float Duration, FVector BoxExtent, FVector Location,
                                                     FRotator Rotation,
                                                     const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle,
                                                     FGameplayTag InFXGameplayCueTag,
                                                     FGameplayTag InHitReactEventTag)
{
	BoxComponent->SetBoxExtent(BoxExtent);
	SetActorLocation(Location);
	SetActorRotation(Rotation);
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
	FXGameplayCueTag = InFXGameplayCueTag;
	HitReactEventTag = InHitReactEventTag;
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(this, FXGameplayCueTag, FGameplayCueParameters());
	FTimerHandle DeactivateTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DeactivateTimerHandle, this, &AAttackCollisionBox::Deactivate, Duration,
	                                       false);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AAttackCollisionBox::InitializeAttachedBoxAndAttack(FVector BoxExtent,
                                                         USkeletalMeshComponent* InstigatorMesh, FName AttachSocketName,
                                                         const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle,
                                                         FGameplayTag InFXGameplayCueTag,
                                                         FGameplayTag InHitReactEventTag, bool bShowCollisionInGame,
                                                         float LineThickness)
{
	BoxComponent->SetBoxExtent(BoxExtent);
	FVector Location;
	FRotator Rotation;
	if (InstigatorMesh)
	{
		InstigatorMesh->GetSocketWorldLocationAndRotation(AttachSocketName, Location, Rotation);
	}
	SetActorLocation(Location);
	SetActorRotation(Rotation);
	AttachToActor(GetInstigator(), FAttachmentTransformRules::KeepRelativeTransform, AttachSocketName);
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
	FXGameplayCueTag = InFXGameplayCueTag;
	HitReactEventTag = InHitReactEventTag;
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(this, FXGameplayCueTag, FGameplayCueParameters());
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	bIsAttached = true;
	if (bShowCollisionInGame)
	{
		BoxComponent->SetHiddenInGame(false);
		BoxComponent->SetLineThickness(LineThickness);
	}
}

void AAttackCollisionBox::DeactivateIfActivated()
{
	if (IsActive())
	{
		Deactivate();
	}
}
