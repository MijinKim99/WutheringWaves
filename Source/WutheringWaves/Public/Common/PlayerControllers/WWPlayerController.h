// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "WWPlayerController.generated.h"

struct FGameplayTag;
struct FInputActionValue;
class UDataAsset_InputConfig;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AWWPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AWWPlayerController();
	virtual FGenericTeamId GetGenericTeamId() const override;
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* DataAsset_InputConfig;
	
	virtual void SetupInputComponent() override;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InputTag);
	void Input_AbilityInputReleased(FGameplayTag InputTag);
	
private:
	FGenericTeamId HeroTeamID;
};
