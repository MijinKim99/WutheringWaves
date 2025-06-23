// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WWPawnExtensionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WWCOPY_API UWWPawnExtensionComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Pawn에 붙어있지 않다면 Crash
	template<class T>
	T* GetOwningPawn() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value,
			"'T' Template Parameter get Pawn must be derived from APawn");

		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const
	{
		return GetOwningPawn<APawn>();
	}

	// Pawn에 붙어있지 않거나 Controller가 없으면 Crash
	template<class T>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value,
			"'T' Template Parameter get Controller must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}
	
	AController* GetOwningController() const
	{
		return GetOwningController<AController>();
	}

		
};
