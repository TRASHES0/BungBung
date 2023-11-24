// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMenuWidget.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Blueprint/WidgetLayoutLibrary.h"


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

	MatchType = "FreeForAll";
	NumPublicConnections = 4;

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
		MultiplayerSessionSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSessionComplete);
	}
}


void ULobbyMenuWidget::OnCreateSessionComplete(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("Session created successfully!")));
		}
		MenuTearDown();
		UWorld* World = GetWorld();
		if(World)
		{
			World->ServerTravel("/Game/Map/TestLand?listen");
		}
		if(RoomWidget)
		{
			RemoveFromParent();
			UUserWidget* Room = CreateWidget(GetWorld(), RoomWidget);
			Room->AddToViewport();
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
		MultiplayListView->OnItemClicked().AddUObject(this, &ULobbyMenuWidget::RoomClicked);
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

void ULobbyMenuWidget::RoomClicked(UObject* Obj)
{
	UMultiplayRoomSessionObject* pData = Cast<UMultiplayRoomSessionObject>(Obj);

	if(pData)
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString(TEXT("Join Clicked")));
		}
		if(MultiplayerSessionSubsystem)
		{
			SelectedSession = pData->Session;
			MultiplayerSessionSubsystem->JoinSession(pData->Session);
		}
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

void ULobbyMenuWidget::OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result)
{
	// SessionInterface
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			//Join Session
			FString Address;
			if(SessionInterface->GetResolvedConnectString(SelectedSession, NAME_GamePort, Address))
			{
				APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
				if(PlayerController)
				{
					if(GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, Address);
					}
					PlayerController->ClientTravel(Address, TRAVEL_Absolute);
					if(RoomWidget)
					{
						RemoveFromParent();
						UUserWidget* tmp = CreateWidget(GetWorld(), RoomWidget);
						tmp->AddToViewport();
					} 
				}
			}
		}
	}
}

