// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "WWPlayerController.generated.h"

class UDataAsset_InputConfig;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class WWCOPY_API AWWPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
protected:

	virtual void BeginPlay() override;
#pragma region Input
protected:
	virtual void SetupInputComponent() override;
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityInputPressed(FGameplayTag InputTag);
	void Input_AbilityInputReleased(FGameplayTag InputTag);

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;

#pragma endregion
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	UPROPERTY(VisibleInstanceOnly)
	class APlayerCharacter* PossessedPlayerCharacter;


private:
public:
};
