// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Attack/AttackCollisionSphereProjectile.h"

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
AAttackCollisionSphereProjectile::AAttackCollisionSphereProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

UProjectileMovementComponent* AAttackCollisionSphereProjectile::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}

// Called when the game starts or when spawned
void AAttackCollisionSphereProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAttackCollisionSphereProjectile::OnBeginOverlap);
}

void AAttackCollisionSphereProjectile::OnHitTargetActor(AActor* HitActor)
{
	// 중복 검사
	if (HitTargetSet.Contains(HitActor))
	{
		return;
	}

	HitTargetSet.Add(HitActor);

	// GameplayEffectSpecHandle 적용
	if (!GameplayEffectSpecHandle.IsValid())
	{
		//Debug::Print(FString::Printf(TEXT("%s : GameplayEffectSpecHandle is not valid"), *GetNameSafe(this)));
		return;
	}

	UWWBlueprintFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(HitActor, GameplayEffectSpecHandle);
	// Gameplay Event 전달
	FGameplayEventData Data;
	Data.Instigator = GetInstigator();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, HitReactEventTag, Data);
	if (bExplodeOnHit)
	{
		UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag, FGameplayCueParameters());
		Deactivate();
	}
}

void AAttackCollisionSphereProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                      bool bFromSweep, const FHitResult& SweepResult)
{
	// Debug::Print(FString::Printf(TEXT("Collision Begin Overlap : %s"), *OtherActor->GetActorNameOrLabel()));
	APawn* OtherPawn = Cast<APawn>(OtherActor);
	if (!OtherPawn)
	{
		if (bExplodeOnHit)
		{
			UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag,
			                                                       FGameplayCueParameters());
			Deactivate();
			return;
		}
		return;
	}

	IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());
	if (!OtherTeamAgent)
	{
		if (bExplodeOnHit)
		{
			UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag,
			                                                       FGameplayCueParameters());
			Deactivate();
			return;
		}
		return;
	}

	if (OtherTeamAgent->GetGenericTeamId() != InstigatorTeamId)
	{
		OnHitTargetActor(OtherActor);
	}
}

void AAttackCollisionSphereProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                             UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                                             const FHitResult& Hit)
{
	UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag, FGameplayCueParameters());
	Deactivate();
}

void AAttackCollisionSphereProjectile::InitializeProjectileAndShoot(float InRadius,
                                                                    const FGameplayEffectSpecHandle&
                                                                    InGameplayEffectSpecHandle,
                                                                    FVector StartRelativeLocation,
                                                                    FVector TargetLocation, float ProjectileSpeed,
                                                                    FGameplayTag InProjectileGameplayCueTag,
                                                                    FGameplayTag InExplosionGameplayCueTag,
                                                                    FGameplayTag InHitReactEventTag,
                                                                    bool bShowCollisionInGame, float LineThickness,
                                                                    float InProjectileGravityScale,
                                                                    bool InbExplodeOnHit,
                                                                    float DurationForNotExplodingProjectile)
{
	// Sphere 세팅
	SphereComponent->SetSphereRadius(InRadius);
	SetActorLocation(StartRelativeLocation);
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
	ProjectileGameplayCueTag = InProjectileGameplayCueTag;
	ExplosionGameplayCueTag = InExplosionGameplayCueTag;
	HitReactEventTag = InHitReactEventTag;

	// Explosion 세팅
	bExplodeOnHit = InbExplodeOnHit;

	// ProjectileMovementComponent 활성화
	ProjectileMovementComponent->Activate();
	ProjectileMovementComponent->SetUpdatedComponent(GetRootComponent());
	ProjectileMovementComponent->SetComponentTickEnabled(true);
	ProjectileMovementComponent->ProjectileGravityScale = InProjectileGravityScale;
	ProjectileMovementComponent->InitialSpeed = ProjectileSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileSpeed;
	ProjectileMovementComponent->Friction = 0.0f;
	FVector Direction = GetInstigator() ? GetInstigator()->GetActorForwardVector() : GetActorForwardVector();
	ProjectileMovementComponent->AddForce(ProjectileSpeed * Direction);
	if (bShowCollisionInGame)
	{
		SphereComponent->SetLineThickness(LineThickness);
		SphereComponent->SetHiddenInGame(false);
	}
	// GameplayCue 적용
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(this, ProjectileGameplayCueTag, FGameplayCueParameters());
	if (bExplodeOnHit)
	{
		SphereComponent->OnComponentHit.AddUniqueDynamic(this, &AAttackCollisionSphereProjectile::OnHit);
		SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
		SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
	else
	{
		FTimerHandle DeactivateTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(DeactivateTimerHandle, this,
		                                       &AAttackCollisionSphereProjectile::Deactivate,
		                                       DurationForNotExplodingProjectile, false);
	}
}


void AAttackCollisionSphereProjectile::SetActive(bool IsActive, APawn* InInstigator)
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

void AAttackCollisionSphereProjectile::Deactivate()
{
	Super::Deactivate();
	HitTargetSet.Empty();
	SphereComponent->SetHiddenInGame(true);
	SphereComponent->SetLineThickness(0.f);
	UGameplayCueFunctionLibrary::RemoveGameplayCueOnActor(this, ProjectileGameplayCueTag, FGameplayCueParameters());
	SphereComponent->OnComponentHit.RemoveAll(this);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}
