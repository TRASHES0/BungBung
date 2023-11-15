// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayListElement.h"

#include "MultiplayRoomSessionObject.h"
#include "OnlineSubsystem.h"
#include "RoomMenuWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UMultiplayListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UMultiplayRoomSessionObject* Item = Cast<UMultiplayRoomSessionObject>(ListItemObject);
	if(Item == nullptr) return;

	Session = Item->Session;

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();

	// Binding callbacks to Delegates of the MultiplayerSessionSubsystem class
	if (MultiplayerSessionSubsystem)
		MultiplayerSessionSubsystem->MultiplayerOnJoinSessionComplete.AddUObject(this, &ThisClass::OnJoinSession);

	if(RoomNameText)
		RoomNameText->SetText(FText::FromString(Session.Session.OwningUserName));

	if(RoomJoinBtn)
	{
		RoomJoinBtn->OnClicked.AddDynamic(this, &UMultiplayListElement::JoinButtonClicked);
	}
}

void UMultiplayListElement::JoinButtonClicked()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString(TEXT("Join Clicked")));
	}
	if(MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->JoinSession(Session);
	}
	if(RoomWidget)
	{
		if(Cast<URoomMenuWidget>(RoomWidget))
			Cast<URoomMenuWidget>(RoomWidget)->ClientSession = Session;
		UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
		CreateWidget(GetWorld(), RoomWidget)->AddToViewport();
	}
}

void UMultiplayListElement::OnJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	
	FString tmp = Session.Session.OwningUserName;
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString::Printf(TEXT("To %s"), *tmp));
	}
	
	// SessionInterface
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if(Subsystem)
	{
		IOnlineSessionPtr SessionInterface = Subsystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			//Join Session
			FString Address;
			if(SessionInterface->GetResolvedConnectString(NAME_GameSession, Address))
			{
				APlayerController* PlayerController = GetGameInstance()->GetFirstLocalPlayerController();
				if(PlayerController)
				{
					PlayerController->ClientTravel(Address, TRAVEL_Absolute);
				}
			}
		}
	}

	if(Result != EOnJoinSessionCompleteResult::Success)
	{
		RoomJoinBtn->SetIsEnabled(true);
	}
}
