// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/TowerBattleSystem/EnemyGroup/WWEnemyGroup.h"

#include "Common/WWDebugHelper.h"
#include "Common/Components/WWHUDSharedUIComponent.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "JMS/Character/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "KMJ/UIComponents/EnemyUIComponent.h"

// Sets default values
AWWEnemyGroup::AWWEnemyGroup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


// Called when the game starts or when spawned
void AWWEnemyGroup::BeginPlay()
{
	Super::BeginPlay();
	EnemyCount = EnemySpawnInfoArray.Num();
	if (EnemyCount > 0)
	{
		bIsEnemyAllDead = false;
		SpawnEnemies();
	}
	else
	{
		bIsEnemyAllDead = true;
	}
	// InitializeHUDHPBar();
}

// void AWWEnemyGroup::DelegateTestFunction(float TestFloat)
// {
// 	Debug::Print(FString::Printf(TEXT("Delegate Test : %f"), TestFloat));
// }

// Called every frame
void AWWEnemyGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
//
// // PlayerController에 IWWHUDSharedUIInterface가 있다는 가정 하에 HPBar 정보 등록 및 초기화
// void AWWEnemyGroup::InitializeHUDHPBar()
// {
// 	if (OwnerIndexOfEnemyHPBarOnHUD < 0)
// 	{
// 		return;
// 	}
// 	if (!SpawnedEnemies.IsValidIndex(OwnerIndexOfEnemyHPBarOnHUD))
// 	{
// 		return;
// 	}
// 	IWWHUDSharedUIInterface* HUDSharedUIInterface = Cast<IWWHUDSharedUIInterface>(
// 		UGameplayStatics::GetPlayerController(GetWorld(), 0));
// 	if (HUDSharedUIInterface)
// 	{
// 		CachedHUDSharedUIComponent = HUDSharedUIInterface->GetHUDSharedUIComponent();
// 		if (!CachedHUDSharedUIComponent)
// 		{
// 			return;
// 		}
// 		AEnemyCharacter* EnemyOnHUD = Cast<AEnemyCharacter>(SpawnedEnemies[OwnerIndexOfEnemyHPBarOnHUD]);
// 		UEnemyUIComponent* EnemyUIComponent = EnemyOnHUD->GetEnemyUIComponent();
// 		// 이미 사용중인 Delegate에 추가로 Delegate를 연결
// 		if (IsValid(EnemyUIComponent)&&IsValid(CachedHUDSharedUIComponent))
// 		{
// 			// EnemyUIComponent->OnCurrentHpChanged.AddDynamic(CachedHUDSharedUIComponent,
// 			//                                                 &UWWHUDSharedUIComponent::
// 			//                                                 BroadcastUpdateEnemyHUDHPBarHPPercent);
// 			// EnemyUIComponent->OnCurrentStaggerChanged.AddDynamic(CachedHUDSharedUIComponent,
// 			//                                                      &UWWHUDSharedUIComponent::
// 			//                                                      BroadcastUpdateEnemyHUDHPBarStaggerPercent);
// 			EnemyUIComponent->OnCurrentHpChanged.AddDynamic(this,&AWWEnemyGroup::DelegateTestFunction);
// 		}
// 		EnemyOnHUD->HideWidgetComponent();
// 		CachedHUDSharedUIComponent->BroadcastSetEnabledEnemyHUDHPBar(
// 			true, Cast<AEnemyCharacter>(SpawnedEnemies[OwnerIndexOfEnemyHPBarOnHUD]));
// 	}
// }

void AWWEnemyGroup::EnemyDead(AActor* DeadEnemy)
{
	// if (SpawnedEnemies.Find(DeadEnemy) == OwnerIndexOfEnemyHPBarOnHUD)
	// {
	// 	if (CachedHUDSharedUIComponent)
	// 	{
	// 		CachedHUDSharedUIComponent->BroadcastSetEnabledEnemyHUDHPBar(false, DeadEnemy);
	// 	}
	// }
	SpawnedEnemies.Remove(DeadEnemy);
	if (SpawnedEnemies.Num() == 0)
	{
		OnAllEnemyDead.Broadcast();
		//Debug::Print(FString::Printf(TEXT("All Enemy Dead : %s"), *GetName()));
	}
}

void AWWEnemyGroup::SpawnEnemies()
{
	for (const FEnemySpawnInfo& EnemySpawnInfo : EnemySpawnInfoArray)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		// Owner를 등록 후 적 사망시 Owner에 접근해 사망 알림
		AActor* SpawnedEnemy = GetWorld()->SpawnActor<AActor>(EnemySpawnInfo.EnemyClass,
		                                                      GetActorLocation() + EnemySpawnInfo.SpawnTransform.
		                                                      GetLocation(),
		                                                      GetActorRotation() + EnemySpawnInfo.SpawnTransform.
		                                                      GetRotation().Rotator(),
		                                                      SpawnParameters);
		SpawnedEnemy->SetOwner(this);
		SpawnedEnemies.Add(SpawnedEnemy);
	}
}
