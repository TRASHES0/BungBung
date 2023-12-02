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
public:
	void SetNameTag(const FText& Name);

protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* NameTagText;

	UFUNCTION(Server, Reliable)
	void ServerSetNameText(const FText& Name);
	UFUNCTION(NetMulticast, Reliable)
	void MulticastSetNameText(const FText& Name);
};
