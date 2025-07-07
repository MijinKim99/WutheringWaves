// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JMS/AttackCollision/EnemyAttackCollision.h"
#include "EnemyAttackCollision_Box.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AEnemyAttackCollision_Box : public AEnemyAttackCollision
{
	GENERATED_BODY()
	AEnemyAttackCollision_Box();

public:
	virtual void AttackAsProjectile(const FVector& TargetLocation, const FVector& BoxExtent) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AttackCollision")
	UBoxComponent* BoxComponent;
	virtual void BeginPlay() override;
	virtual void ResetCollision() override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                            UPrimitiveComponent* OtherComp,
	                            int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
