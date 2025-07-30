// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Attack/AttackCollisionBoxProjectile.h"
#include "Common/WWDebugHelper.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayCueFunctionLibrary.h"
#include "IMessageTracer.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AAttackCollisionBoxProjectile::AAttackCollisionBoxProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
		TEXT("ProjectileMovementComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

UProjectileMovementComponent* AAttackCollisionBoxProjectile::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}

// Called when the game starts or when spawned
void AAttackCollisionBoxProjectile::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAttackCollisionBoxProjectile::OnBeginOverlap);
}

void AAttackCollisionBoxProjectile::OnHitTargetActor(AActor* HitActor)
{
	// 중복 검사
	if (HitTargetSet.Contains(HitActor))
	{
		return;
	}

	HitTargetSet.Add(HitActor);

	// GameplayEffectSpecHandle 적용
	for (FGameplayEffectSpecHandle GESpecHandle : MultipleGameplayEffectSpecHandles)
	{
		UWWBlueprintFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(HitActor, GESpecHandle);
	}
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

void AAttackCollisionBoxProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

void AAttackCollisionBoxProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                                          const FHitResult& Hit)
{
	UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag, FGameplayCueParameters());
	Deactivate();
}

void AAttackCollisionBoxProjectile::InitializeProjectileWithPresetAndShoot(
	TSubclassOf<AAttackCollisionBoxProjectile> ProjectilePresetClass, USkeletalMeshComponent* InstigatorMesh,
	FName AttachSocketName, AActor* HomingTargetActor,
	const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandles,
	FVector TargetLocation, float ProjectileSpeed, bool bShowCollisionInGame, float LineThickness, bool InbExplodeOnHit,
	float DurationForNotExplodingProjectile)
{
	// Box 세팅
	AActor* TemplateCDO = ProjectilePresetClass->GetDefaultObject<AActor>();

	UProjectileMovementComponent* ProjectileMovementComponentPreset = TemplateCDO->FindComponentByClass<
		UProjectileMovementComponent>();

	FVector Location;
	FRotator Rotation;
	if (InstigatorMesh)
	{
		InstigatorMesh->GetSocketWorldLocationAndRotation(AttachSocketName, Location, Rotation);
	}
	SetActorLocation(Location);
	SetActorRotation(Rotation);
	AttachToActor(GetInstigator(), FAttachmentTransformRules::KeepRelativeTransform, AttachSocketName);

	// Explosion 세팅
	bExplodeOnHit = InbExplodeOnHit;

	//만약 TargetActor가 있다면 유도탄, 그렇지 않다면 일반
	// ProjectileMovementComponent 활성화
	ProjectileMovementComponent->Activate();
	ProjectileMovementComponent->SetUpdatedComponent(GetRootComponent());
	ProjectileMovementComponent->SetComponentTickEnabled(true);
	ProjectileMovementComponent->ProjectileGravityScale = ProjectileMovementComponentPreset->ProjectileGravityScale;
	ProjectileMovementComponent->InitialSpeed = ProjectileMovementComponentPreset->InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileMovementComponentPreset->MaxSpeed;
	ProjectileMovementComponent->Friction = ProjectileMovementComponentPreset->Friction;
	ProjectileMovementComponent->bIsHomingProjectile = ProjectileMovementComponentPreset->bIsHomingProjectile;
	ProjectileMovementComponent->HomingTargetComponent =  HomingTargetActor->GetRootComponent();

	FVector Direction;
	if (!ProjectileMovementComponent->bIsHomingProjectile)
	{
		Direction = GetActorForwardVector();
	}
	else
	{
		Direction = (HomingTargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
	}


	ProjectileMovementComponent->AddForce(ProjectileSpeed * Direction);
	if (bShowCollisionInGame)
	{
		BoxComponent->SetLineThickness(LineThickness);
		BoxComponent->SetHiddenInGame(false);
	}
	// GameplayCue 적용
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(this, ProjectileGameplayCueTag, FGameplayCueParameters());
	if (bExplodeOnHit)
	{
		BoxComponent->OnComponentHit.AddUniqueDynamic(this, &AAttackCollisionBoxProjectile::OnHit);
		BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
		BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
	else
	{
		FTimerHandle DeactivateTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(DeactivateTimerHandle, this,
		                                       &AAttackCollisionBoxProjectile::Deactivate,
		                                       DurationForNotExplodingProjectile, false);
	}
}

void AAttackCollisionBoxProjectile::InitializeProjectileAndShoot_Internal(FVector BoxExtent,
                                                                          const TArray<FGameplayEffectSpecHandle>&
                                                                          InGameplayEffectSpecHandles,
                                                                          FVector StartRelativeLocation,
                                                                          FVector TargetLocation, float ProjectileSpeed,
                                                                          FGameplayTag InProjectileGameplayCueTag,
                                                                          FGameplayTag InExplosionGameplayCueTag,
                                                                          FGameplayTag InHitReactEventTag,
                                                                          bool bShowCollisionInGame,
                                                                          float LineThickness,
                                                                          float InProjectileGravityScale,
                                                                          bool InbExplodeOnHit,
                                                                          float DurationForNotExplodingProjectile)
{
	// Box 세팅
	BoxComponent->SetBoxExtent(BoxExtent);
	SetActorLocation(StartRelativeLocation);
	MultipleGameplayEffectSpecHandles = InGameplayEffectSpecHandles;
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
	//FVector Direction = GetInstigator() ? GetInstigator()->GetActorForwardVector() : GetActorForwardVector();

	FVector Direction;
	if (TargetLocation.IsZero())
	{
		if (GetInstigator())
		{
			Direction = GetInstigator() ? GetInstigator()->GetActorForwardVector() : GetActorForwardVector();
		}
	}
	else
	{
		Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	}

	ProjectileMovementComponent->AddForce(ProjectileSpeed * Direction);
	if (bShowCollisionInGame)
	{
		BoxComponent->SetLineThickness(LineThickness);
		BoxComponent->SetHiddenInGame(false);
	}
	// GameplayCue 적용
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(this, ProjectileGameplayCueTag, FGameplayCueParameters());
	if (bExplodeOnHit)
	{
		BoxComponent->OnComponentHit.AddUniqueDynamic(this, &AAttackCollisionBoxProjectile::OnHit);
		BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
		BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
	else
	{
		FTimerHandle DeactivateTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(DeactivateTimerHandle, this,
		                                       &AAttackCollisionBoxProjectile::Deactivate,
		                                       DurationForNotExplodingProjectile, false);
	}
}

void AAttackCollisionBoxProjectile::InitializeAttachedProjectileAndShoot_Internal(FVector BoxExtent,
	USkeletalMeshComponent* InstigatorMesh,
	FName AttachSocketName,
	const TArray<FGameplayEffectSpecHandle>&
	InGameplayEffectSpecHandles,
	FVector TargetLocation, float ProjectileSpeed,
	FGameplayTag InProjectileGameplayCueTag,
	FGameplayTag InExplosionGameplayCueTag,
	FGameplayTag InHitReactEventTag,
	bool bShowCollisionInGame,
	float LineThickness,
	float InProjectileGravityScale,
	bool InbExplodeOnHit,
	float DurationForNotExplodingProjectile)
{
	// Box 세팅
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
	MultipleGameplayEffectSpecHandles = InGameplayEffectSpecHandles;
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

	FVector Direction;
	if (TargetLocation.IsZero())
	{
		if (GetInstigator())
		{
			Direction = GetInstigator()->GetActorForwardVector();
		}
	}
	else
	{
		Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();
	}


	ProjectileMovementComponent->AddForce(ProjectileSpeed * Direction);
	if (bShowCollisionInGame)
	{
		BoxComponent->SetLineThickness(LineThickness);
		BoxComponent->SetHiddenInGame(false);
	}
	// GameplayCue 적용
	UGameplayCueFunctionLibrary::AddGameplayCueOnActor(this, ProjectileGameplayCueTag, FGameplayCueParameters());
	if (bExplodeOnHit)
	{
		BoxComponent->OnComponentHit.AddUniqueDynamic(this, &AAttackCollisionBoxProjectile::OnHit);
		BoxComponent->SetCollisionResponseToAllChannels(ECR_Block);
		BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
	else
	{
		FTimerHandle DeactivateTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(DeactivateTimerHandle, this,
		                                       &AAttackCollisionBoxProjectile::Deactivate,
		                                       DurationForNotExplodingProjectile, false);
	}
}

void AAttackCollisionBoxProjectile::InitializeProjectileAndShoot(FVector BoxExtent,
                                                                 const FGameplayEffectSpecHandle&
                                                                 InGameplayEffectSpecHandle,
                                                                 FVector StartRelativeLocation, FVector TargetLocation,
                                                                 float ProjectileSpeed,
                                                                 FGameplayTag InProjectileGameplayCueTag,
                                                                 FGameplayTag InExplosionGameplayCueTag,
                                                                 FGameplayTag InHitReactEventTag,
                                                                 bool bShowCollisionInGame, float LineThickness,
                                                                 float InProjectileGravityScale,
                                                                 bool InbExplodeOnHit,
                                                                 float DurationForNotExplodingProjectile)
{
	TArray<FGameplayEffectSpecHandle> GameplayEffectSpecHandles;
	GameplayEffectSpecHandles.Add(InGameplayEffectSpecHandle);
	InitializeProjectileAndShoot_Internal(BoxExtent, GameplayEffectSpecHandles, StartRelativeLocation, TargetLocation,
	                                      ProjectileSpeed, InProjectileGameplayCueTag, InExplosionGameplayCueTag,
	                                      InHitReactEventTag, bShowCollisionInGame, LineThickness,
	                                      InProjectileGravityScale, InbExplodeOnHit, DurationForNotExplodingProjectile);
}

void AAttackCollisionBoxProjectile::InitializeAttachedProjectileAndShoot(FVector BoxExtent,
                                                                         USkeletalMeshComponent* InstigatorMesh,
                                                                         FName AttachSocketName,
                                                                         const FGameplayEffectSpecHandle&
                                                                         InGameplayEffectSpecHandles,
                                                                         FVector TargetLocation, float ProjectileSpeed,
                                                                         FGameplayTag InProjectileGameplayCueTag,
                                                                         FGameplayTag InExplosionGameplayCueTag,
                                                                         FGameplayTag InHitReactEventTag,
                                                                         bool bShowCollisionInGame,
                                                                         float LineThickness,
                                                                         float InProjectileGravityScale,
                                                                         bool InbExplodeOnHit,
                                                                         float DurationForNotExplodingProjectile)
{
	TArray<FGameplayEffectSpecHandle> GameplayEffectSpecHandles;
	GameplayEffectSpecHandles.Add(InGameplayEffectSpecHandles);
	InitializeAttachedProjectileAndShoot_Internal(BoxExtent, InstigatorMesh, AttachSocketName,
	                                              GameplayEffectSpecHandles, TargetLocation,
	                                              ProjectileSpeed, InProjectileGameplayCueTag,
	                                              InExplosionGameplayCueTag,
	                                              InHitReactEventTag, bShowCollisionInGame, LineThickness,
	                                              InProjectileGravityScale, InbExplodeOnHit,
	                                              DurationForNotExplodingProjectile);
}


void AAttackCollisionBoxProjectile::InitializeProjectileAndShootMultipleEffects(FVector BoxExtent,
	const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandles, FVector StartRelativeLocation,
	FVector TargetLocation, float ProjectileSpeed, FGameplayTag InProjectileGameplayCueTag,
	FGameplayTag InExplosionGameplayCueTag, FGameplayTag InHitReactEventTag, bool bShowCollisionInGame,
	float LineThickness, float InProjectileGravityScale, bool InbExplodeOnHit, float DurationForNotExplodingProjectile)
{
	InitializeProjectileAndShoot_Internal(BoxExtent, InGameplayEffectSpecHandles, StartRelativeLocation, TargetLocation,
	                                      ProjectileSpeed, InProjectileGameplayCueTag, InExplosionGameplayCueTag,
	                                      InHitReactEventTag, bShowCollisionInGame, LineThickness,
	                                      InProjectileGravityScale, InbExplodeOnHit, DurationForNotExplodingProjectile);
}

void AAttackCollisionBoxProjectile::InitializeAttachedProjectileAndShootMultipleEffects(FVector BoxExtent,
	USkeletalMeshComponent* InstigatorMesh, FName AttachSocketName,
	const TArray<FGameplayEffectSpecHandle>& InGameplayEffectSpecHandles,
	FVector TargetLocation, float ProjectileSpeed, FGameplayTag InProjectileGameplayCueTag,
	FGameplayTag InExplosionGameplayCueTag, FGameplayTag InHitReactEventTag, bool bShowCollisionInGame,
	float LineThickness, float InProjectileGravityScale, bool InbExplodeOnHit, float DurationForNotExplodingProjectile)
{
	if (!InstigatorMesh)
		return;
	
	InitializeAttachedProjectileAndShoot_Internal(BoxExtent, InstigatorMesh, AttachSocketName,
	                                              InGameplayEffectSpecHandles, TargetLocation,
	                                              ProjectileSpeed, InProjectileGameplayCueTag,
	                                              InExplosionGameplayCueTag,
	                                              InHitReactEventTag, bShowCollisionInGame, LineThickness,
	                                              InProjectileGravityScale, InbExplodeOnHit,
	                                              DurationForNotExplodingProjectile);
}


void AAttackCollisionBoxProjectile::SetActive(bool IsActive, APawn* InInstigator)
{
	Super::SetActive(IsActive, InInstigator);

	if (IsActive)
	{
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ProjectileMovementComponent->SetUpdatedComponent(GetRootComponent());
		ProjectileMovementComponent->SetComponentTickEnabled(true);
		if (InInstigator)
		{
			InstigatorTeamId = Cast<IGenericTeamAgentInterface>(InInstigator->GetController())->GetGenericTeamId();
		}
	}
	else
	{
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ProjectileMovementComponent->SetUpdatedComponent(nullptr);
		ProjectileMovementComponent->SetComponentTickEnabled(false);
		ProjectileMovementComponent->StopMovementImmediately();
	}
}

void AAttackCollisionBoxProjectile::Deactivate()
{
	Super::Deactivate();
	HitTargetSet.Empty();
	BoxComponent->SetHiddenInGame(true);
	BoxComponent->SetLineThickness(0.f);
	UGameplayCueFunctionLibrary::RemoveGameplayCueOnActor(this, ProjectileGameplayCueTag, FGameplayCueParameters());
	BoxComponent->OnComponentHit.RemoveAll(this);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}
