// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMenuWidget.h"

#include "OnlineSessionSettings.h"


bool ULobbyMenuWidget::Initialize()
{
	if(!Super::Initialize()) return false;

	if(HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ULobbyMenuWidget::HostButtonClicked);
	}
	if(SearchButton)
	{
		SearchButton->OnClicked.AddDynamic(this, &ThisClass::SearchButtonClicked);
	}

	return true;
}

void ULobbyMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
	}

	// Binding callbacks to Delegates of the MultiplayerSessionSubsystem class
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSessionComplete);
		MultiplayerSessionSubsystem->MultiplayerOnFindSessionComplete.AddUObject(this, &ThisClass::OnFindSessionComplete);
	}
}

void ULobbyMenuWidget::NativeDestruct()
{
	MenuTearDown();
	Super::NativeDestruct();
}

void ULobbyMenuWidget::OnCreateSessionComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("Session created successfully!")));
		}
		UWorld* World = GetWorld();
		if(World)
		{
			World->ServerTravel("/Game/Map/TestLand?listen");
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to create session!")));
		}

		HostButton->SetIsEnabled(true);
	}
}

void ULobbyMenuWidget::OnFindSessionComplete(const TArray<FOnlineSessionSearchResult>& SessionResults, bool bwasSuccessful)
{
	if(MultiplayListView)
	{
		MultiplayListView->ClearListItems();
	}
	if(!bwasSuccessful || SessionResults.Num() <= 0)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("No Session Found")));
		}
		return;
	}
	for(auto S : SessionResults)
	{
		SessionObject = NewObject<UMultiplayRoomSessionObject>();
		if(SessionObject)
		{
			SessionObject->Session = S;
		}
		if(MultiplayListView)
		{
			MultiplayListView->AddItem(SessionObject);
		}
	}
}

void ULobbyMenuWidget::HostButtonClicked()
{
	HostButton->SetIsEnabled(false);
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}

void ULobbyMenuWidget::SearchButtonClicked()
{
	if(MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->FindSession(10);
	}
}

void ULobbyMenuWidget::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController =World->GetFirstPlayerController();
		if(PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
