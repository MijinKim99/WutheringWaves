// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Attack/AttackCollision_SphereProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayCueInterface.h"
#include "GameplayTagContainer.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameplayCueFunctionLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWDebugHelper.h"
#include "Common/WWGameplayTags.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AAttackCollision_SphereProjectile::AAttackCollision_SphereProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AAttackCollision_SphereProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAttackCollision_SphereProjectile::OnBeginOverlap);
	SphereComponent->OnComponentHit.AddUniqueDynamic(this,&AAttackCollision_SphereProjectile::OnHit);

}

void AAttackCollision_SphereProjectile::OnHitTargetActor(AActor* HitActor)
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
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, WWGameplayTags::Shared_Event_HitReact, Data);
	UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag, FGameplayCueParameters());
	Deactivate();
}

void AAttackCollision_SphereProjectile::SetDamageEffect(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
}

void AAttackCollision_SphereProjectile::SetProjectileGameplayCueTag(FGameplayTag InGameplayCueTag)
{
	ProjectileGameplayCueTag = InGameplayCueTag;
}

void AAttackCollision_SphereProjectile::SetExplosionGameplayCueTag(FGameplayTag InGameplayCueTag)
{
	ExplosionGameplayCueTag = InGameplayCueTag;
}

void AAttackCollision_SphereProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                       UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                       bool bFromSweep, const FHitResult& SweepResult)
{
	Debug::Print(FString::Printf(TEXT("Collision Begin Overlap : %s"), *OtherActor->GetActorNameOrLabel()));
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn)
	{
		UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag, FGameplayCueParameters());
		Deactivate();
		return;
	}

	IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (!OtherTeamAgent)
	{
		UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag, FGameplayCueParameters());
		Deactivate();
		return;
	}

	if (OtherTeamAgent->GetGenericTeamId() != InstigatorTeamId)
	{
		OnHitTargetActor(OtherActor);
	}
}

void AAttackCollision_SphereProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                                              const FHitResult& Hit)
{
	UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag, FGameplayCueParameters());
	Deactivate();
}


void AAttackCollision_SphereProjectile::LaunchProjectile(const FVector& TargetLocation, float Power)
{
	// ProjectileMovementComponent 세팅
	ProjectileMovementComponent->Activate();
	ProjectileMovementComponent->SetUpdatedComponent(GetRootComponent());
	ProjectileMovementComponent->SetComponentTickEnabled(true);
	float Distance = (TargetLocation - GetActorLocation()).Size();
	ProjectileMovementComponent->InitialSpeed = Distance * Power;
	ProjectileMovementComponent->MaxSpeed = Distance * Power;
	ProjectileMovementComponent->AddForce(Power * (TargetLocation - GetActorLocation()));

	// GameplayCue 적용
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(this, ProjectileGameplayCueTag, FGameplayCueParameters());
}

void AAttackCollision_SphereProjectile::SetSphereRadius(float InRadius)
{
	SphereComponent->SetSphereRadius(InRadius);
}

void AAttackCollision_SphereProjectile::SetActive(bool IsActive, APawn* InInstigator)
{
	Super::SetActive(IsActive, InInstigator);

	if (IsActive)
	{
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ProjectileMovementComponent->SetUpdatedComponent(GetRootComponent());
		ProjectileMovementComponent->SetComponentTickEnabled(true);
		if (InInstigator)
		{
			InstigatorTeamId = Cast<IGenericTeamAgentInterface>(InInstigator->GetController())->GetGenericTeamId();
		}
	}
	else
	{
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ProjectileMovementComponent->SetUpdatedComponent(nullptr);
		ProjectileMovementComponent->SetComponentTickEnabled(false);
		ProjectileMovementComponent->StopMovementImmediately();
	}
}

void AAttackCollision_SphereProjectile::Deactivate()
{
	Super::Deactivate();
	HitTargetSet.Empty();
	UGameplayCueFunctionLibrary::RemoveGameplayCueOnActor(this, ProjectileGameplayCueTag, FGameplayCueParameters());
}
