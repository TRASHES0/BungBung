// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "PlayerInfoElement.generated.h"

/**
 * 
 */
UCLASS()
class BUNGBUNG_API UPlayerInfoElement : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerNameText;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* PlayerImage;
};
