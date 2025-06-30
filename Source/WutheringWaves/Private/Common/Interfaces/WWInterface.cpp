// Fill out your copyright notice in the Description page of Project Settings.


#include "Common/Interfaces/WWInterface.h"

// Add default functionality here for any IWWInterface functions that are not pure virtual.
UPlayerUIComponent* IWWInterface::GetPlayerUIComponent() const
{
	return nullptr;
}

UEnemyUIComponent* IWWInterface::GetEnemyUIComponent() const
{
	return nullptr;
}
