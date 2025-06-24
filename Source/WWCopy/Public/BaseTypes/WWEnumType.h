// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
UENUM()
enum class EWWConfirmType : uint8
{
	Yes,
	No,
};

UENUM()
enum class EWWValidType : uint8
{
	Valid,
	InValid
};

UENUM()
enum class EWWSuccessType : uint8
{
	Success,
	Failed,
};


class WWCOPY_API WWEnumType
{
};
