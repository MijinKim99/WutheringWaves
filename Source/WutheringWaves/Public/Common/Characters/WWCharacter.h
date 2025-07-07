// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Common/Interfaces/PawnUIInterface.h"
#include "Common/Interfaces/PawnCombatInterface.h"
#include "WWCharacter.generated.h"

class UMotionWarpingComponent;
class UWWAbilitySystemComponent;
class UWWAttributeSet;
class UDataAsset_Startup;

UCLASS()
class WUTHERINGWAVES_API AWWCharacter : public ACharacter , public IPawnUIInterface, public IPawnCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWWCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	*/

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWWAbilitySystemComponent* WWAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UWWAttributeSet* WWAttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	//동기식으로 데이터를 불러온다
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "StartupData")
	TSoftObjectPtr<UDataAsset_Startup> StartupData;

	//IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	//IPawnCombatInterface
	
public:
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	FORCEINLINE UWWAbilitySystemComponent* GetBaseAbilitySystemComponent() const { return WWAbilitySystemComponent; }
	FORCEINLINE UWWAttributeSet* GetBaseAttributeSet() const { return WWAttributeSet; }

//어빌리티 제어
public:
	UFUNCTION(BlueprintCallable)
	void CancelAllActiveAbilities(UAbilitySystemComponent* ASC);
};