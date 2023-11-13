// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionSettings.h"
#include "UObject/NoExportTypes.h"
#include "MultiplayRoomSessionObject.generated.h"

/**
 * 
 */
UCLASS()
class BUNGBUNG_API UMultiplayRoomSessionObject : public UObject
{
	GENERATED_BODY()
	
public:
	FOnlineSessionSearchResult Session;
	
};
