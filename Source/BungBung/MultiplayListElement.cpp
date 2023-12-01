// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayListElement.h"
#include "MultiplayRoomSessionObject.h"
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

	if(RoomNameText)
	{
		RoomNameText->SetText(FText::FromString(Session.Session.OwningUserName));
	}

	if(CurrentPlayerCntText)
	{
		FString tmp = FString::Printf(TEXT("%d/%d"), Session.Session.SessionSettings.NumPublicConnections - Session.Session.NumOpenPublicConnections, Session.Session.SessionSettings.NumPublicConnections);
		CurrentPlayerCntText->SetText(FText::FromString(tmp));
	}
	
}