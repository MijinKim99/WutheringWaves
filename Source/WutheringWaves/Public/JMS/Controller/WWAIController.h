// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WWAIController.generated.h"

/**
 * 
 */
struct FAIStimulus;
class UAISenseConfig_Sight;

UCLASS()
class WUTHERINGWAVES_API AWWAIController : public AAIController
{
	GENERATED_BODY()

	AWWAIController(const FObjectInitializer& ObjectInitializer);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBehaviorTree* BTAsset;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
	void ChangeTarget(APawn* NewTarget);

private:
	UPROPERTY(EditDefaultsOnly, Category="AI")
	bool bDetourCrowdAvoidence = true;

	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(EditCondition= "bDetourCrowdAvoidence", UIMin="1", UIMax="4"))
	int32 DetourCrowdAvoidenceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category="AI", meta=(EditCondition="bDetourCrowdAvoidence"))
	float CollisionQueryRange = 600.0f;
};
