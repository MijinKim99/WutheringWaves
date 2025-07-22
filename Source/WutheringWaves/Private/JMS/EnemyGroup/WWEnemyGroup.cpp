// Fill out your copyright notice in the Description page of Project Settings.


#include "JMS/EnemyGroup/WWEnemyGroup.h"

#include "Components/BillboardComponent.h"
#include "JMS/Character/EnemyCharacter.h"

// Sets default values
AWWEnemyGroup::AWWEnemyGroup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
#if WITH_EDITOR
void AWWEnemyGroup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	for (USkeletalMeshComponent* MeshComponent : SkeletalMeshVisualizers)
	{
		if (MeshComponent)
		{
			MeshComponent->DestroyComponent();
		}
		
	}
	SkeletalMeshVisualizers.Empty();
	int32 Index = 0;
	for (const FEnemySpawnInfo& Info : EnemySpawnInfoArray)
	{
		if (Info.EnemyClass)
		{
			AEnemyCharacter* EnemyDefaultObject = Info.EnemyClass->GetDefaultObject<AEnemyCharacter>();
			if (EnemyDefaultObject && EnemyDefaultObject->GetMesh())
			{
				FName MeshComponentName = FName(*FString::Printf(TEXT("EnemyMeshVisualizer_%d"), Index++));
				USkeletalMeshComponent* MeshVisualizer = NewObject<USkeletalMeshComponent>(this, MeshComponentName);
				if (MeshVisualizer)
				{
					MeshVisualizer->RegisterComponent();
					MeshVisualizer->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
					MeshVisualizer->SetSkeletalMesh(EnemyDefaultObject->GetMesh()->GetSkeletalMeshAsset());
					MeshVisualizer->SetCollisionEnabled(ECollisionEnabled::NoCollision);

					MeshVisualizer->SetVisibility(true);
					MeshVisualizer->SetHiddenInGame(true);
				}
			}
		}
	}
}
#endif

// Called when the game starts or when spawned
void AWWEnemyGroup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWWEnemyGroup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
