// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayListElement.h"

#include "OnlineSubsystem.h"

void UMultiplayListElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	if(RoomJoinBtn)
	{
		RoomJoinBtn->OnClicked.AddDynamic(this, &UMultiplayListElement::JoinButtonClicked);
	}
}

void UMultiplayListElement::JoinButtonClicked()
{
	
}
