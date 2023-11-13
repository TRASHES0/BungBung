// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayListElement.h"

#include "MultiplayRoomSessionObject.h"
#include "OnlineSubsystem.h"

void UMultiplayListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UMultiplayRoomSessionObject* Item = Cast<UMultiplayRoomSessionObject>(ListItemObject);
	if(Item == nullptr) return;

	if(RoomNameText)
		RoomNameText->SetText(FText::FromString(Item->SessionName));

	if(RoomJoinBtn)
	{
		RoomJoinBtn->OnClicked.AddDynamic(this, &UMultiplayListElement::JoinButtonClicked);
	}
}

void UMultiplayListElement::JoinButtonClicked()
{
	
}
