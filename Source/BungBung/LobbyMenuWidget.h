// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerSessionSubsystem.h"
#include "Components/Button.h"
#include "LobbyMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BUNGBUNG_API ULobbyMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UMultiplayerSessionSubsystem* MultiplayerSessionSubsystem;
	int32 NumPublicConnections;
	FString MatchType;
	FString PathToLevel;
	
	UPROPERTY(meta=(BindWidget))
		UButton* HostButton;
	
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	UFUNCTION()
	void OnCreateSession(bool bWasSuccessful);

	UFUNCTION(BlueprintCallable)
	void HostButtonClicked();
	
};
