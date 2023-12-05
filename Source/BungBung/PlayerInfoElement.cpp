// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInfoElement.h"

#include "UserObject.h"

void UPlayerInfoElement::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

	const UUserObject* Item = Cast<UUserObject>(ListItemObject);
	if(Item == nullptr) return;

	if(PlayerNameText)
	{
		PlayerNameText->SetText(FText::FromString(Item->PlayerName));
	}
}
