// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "NameTag.generated.h"

/**
 * 
 */
UCLASS()
class BUNGBUNG_API UNameTag : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool Initialize() override;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameTagText;

	UFUNCTION(Client, Reliable)
	void SetNameText(const FString& Name);
};
