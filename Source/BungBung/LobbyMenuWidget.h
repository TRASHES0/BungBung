// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MultiplayerSessionSubsystem.h"
#include "MultiplayListView.h"
#include "MultiplayRoomSessionObject.h"
#include "RoomMenuWidget.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Widget)
	TSubclassOf<UUserWidget> RoomWidget;
	
	UPROPERTY(meta=(BindWidget))
	UButton* HostButton;
	UPROPERTY(meta=(BindWidget))
	UButton* SearchButton;
	UPROPERTY(meta=(BindWidget))
	UMultiplayListView* MultiplayListView;
	
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnCreateSessionComplete(bool bWasSuccessful);
	void OnFindSessionComplete(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful);

	UFUNCTION(BlueprintCallable)
	void HostButtonClicked();
	UFUNCTION(BlueprintCallable)
	void SearchButtonClicked();
	UFUNCTION(BlueprintCallable)
	void RoomClicked(UObject* Obj);

private:
	UMultiplayRoomSessionObject* SessionObject;
};
