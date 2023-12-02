// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BungBungGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BUNGBUNG_API UBungBungGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FText PlayerName=FText(FText::FromString("NAME"));
	
};
