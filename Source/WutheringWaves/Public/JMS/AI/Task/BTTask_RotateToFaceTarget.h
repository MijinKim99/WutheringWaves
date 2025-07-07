// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RotateToFaceTarget.generated.h"

/**
 * 
 */
struct FRotateToFaceTagetTaskMemory
{
	TWeakObjectPtr<APawn> OwningPawn;
	TWeakObjectPtr<AActor> TargetActor;

	bool IsValid() const
	{
		return OwningPawn.IsValid() && TargetActor.IsValid();
	}

	void Reset()
	{
		OwningPawn.Reset();
		TargetActor.Reset();
	}
};

UCLASS()
class WUTHERINGWAVES_API UBTTask_RotateToFaceTarget : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTask_RotateToFaceTarget();

public:
	UPROPERTY(EditAnywhere, Category="FaceTaget")
	float AnglePrecision;

	UPROPERTY(EditAnywhere, Category="FaceTaget")
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere, Category="FaceTaget")
	FBlackboardKeySelector TagetFaceKey;

protected:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	bool HasAnglePrecision(APawn* QueryPawn, AActor* TargetActor);
};
