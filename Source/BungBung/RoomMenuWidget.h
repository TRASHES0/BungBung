// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayRoomSessionObject.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "RoomMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BUNGBUNG_API URoomMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* StartButton;

	UFUNCTION(BlueprintCallable)
	void StartButtonClicked();

private:
	void MenuTearDown();
	
};
