// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WWUserWidget.generated.h"

class UWWHUDSharedUIComponent;
class UPawnUIComponent;
class APlayerCharacter;
class UEnemyUIComponent;
class UPlayerUIComponent;
/**
 * 
 */
UCLASS()
class WUTHERINGWAVES_API UWWUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningPlayerUIComponentInitialized(UPawnUIComponent* PawnUIComponent);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent);

	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOwningHUDSharedUIComponentInitialized(UWWHUDSharedUIComponent* HUDSharedUIComponent);
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreateWidget(AActor* EnemyActor);

	UFUNCTION(BlueprintCallable)
	void InitPlayerCreateWidget(AActor* PlayerCharacter);

	UFUNCTION(BlueprintCallable)
	void InitHUDSharedWidget(AActor* UIOwner);
	
	
};
