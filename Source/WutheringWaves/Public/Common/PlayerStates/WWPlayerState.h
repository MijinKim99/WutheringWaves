// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "WWPlayerState.generated.h"

class UResonatorAttributeSet;
class UPlayerCharacterStartup;
class UWWAbilitySystemComponent;
class UPlayerAttributeSet;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API AWWPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AWWPlayerState();
private:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UWWAbilitySystemComponent* WWAbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem", meta = (AllowPrivateAccess = "true"))
	UPlayerAttributeSet* PlayerAttributeSet;

	
	//동기식으로 데이터를 불러온다
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "StartupData", meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<UPlayerCharacterStartup> CommonStartupData;

	//캐릭터 데이터
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "StartupData", meta = (AllowPrivateAccess = "true"))
	TArray<TSoftObjectPtr<UPlayerCharacterStartup>> CharacterStartupData;

private:
	UFUNCTION()
	void ChangedPlayerCharacter(APlayerState* Player, APawn* NewPawn, APawn* OldPawn);


public:
	//Get ASC
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	UFUNCTION(BlueprintCallable)
	void CancelPlayerActiveAbilities(UAbilitySystemComponent* ASC, FGameplayTag CancelTag);
	
	UFUNCTION(BlueprintCallable)
	void CancelAllPlayerActiveAbilities(UAbilitySystemComponent* ASC);
};
