// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TileView.h"
#include "MultiplayerTileView.generated.h"

/**
 * 
 */
UCLASS()
class BUNGBUNG_API UMultiplayerTileView : public UTileView
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTileView> PlayerInfoTile;
};
