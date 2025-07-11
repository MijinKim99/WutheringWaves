// Sets default values

#include "YHG/ObjectPool/AttackCollision_Test.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
#include "GameplayCueFunctionLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Common/WWBlueprintFunctionLibrary.h"
#include "Common/WWDebugHelper.h"
#include "Components/SphereComponent.h"

AAttackCollision_Test::AAttackCollision_Test()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Block);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void AAttackCollision_Test::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAttackCollision_Test::OnBeginOverlap);
	SphereComponent->OnComponentHit.AddUniqueDynamic(this,&AAttackCollision_Test::OnHit);

}

void AAttackCollision_Test::OnHitTargetActor(AActor* HitActor)
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
	UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag, FGameplayCueParameters());
	Deactivate();
}

void AAttackCollision_Test::SetDamageEffect(const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	GameplayEffectSpecHandle = InGameplayEffectSpecHandle;
}

void AAttackCollision_Test::SetExplosionGameplayCueTag(FGameplayTag InGameplayCueTag)
{
	ExplosionGameplayCueTag = InGameplayCueTag;
}

void AAttackCollision_Test::SetHitReactEventTag(FGameplayTag InGameplayEventTag)
{
	HitReactEventTag = InGameplayEventTag;
}

void AAttackCollision_Test::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
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

void AAttackCollision_Test::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, FVector NormalImpulse,
                                              const FHitResult& Hit)
{
	UGameplayCueFunctionLibrary::ExecuteGameplayCueOnActor(this, ExplosionGameplayCueTag, FGameplayCueParameters());
	Deactivate();
}

void AAttackCollision_Test::SetSphereRadius(float InRadius)
{
	SphereComponent->SetSphereRadius(InRadius);
}

void AAttackCollision_Test::SetActive(bool IsActive, APawn* InInstigator)
{
	Super::SetActive(IsActive, InInstigator);

	if (IsActive)
	{
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		if (InInstigator)
		{
			InstigatorTeamId = Cast<IGenericTeamAgentInterface>(InInstigator->GetController())->GetGenericTeamId();
		}
	}
	else
	{
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void AAttackCollision_Test::Deactivate()
{
	Super::Deactivate();
	HitTargetSet.Empty();
}