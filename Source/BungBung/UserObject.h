// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserObject.generated.h"

/**
 * 
 */
UCLASS()
class BUNGBUNG_API UUserObject : public UObject
{
	GENERATED_BODY()

public:
	FString PlayerName;
	
};
