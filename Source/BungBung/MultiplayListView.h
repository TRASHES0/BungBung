// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ListView.h"
#include "MultiplayListView.generated.h"

/**
 * 
 */
UCLASS()
class BUNGBUNG_API UMultiplayListView : public UListView
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UListView> MultiplayRoomList;
};
