// Fill out your copyright notice in the Description page of Project Settings.


#include "NameTag.h"
#include "GameFramework/PlayerState.h"

void UNameTag::NativeConstruct()
{
	Super::NativeConstruct();
	ULocalPlayer* PC = GetWorld()->GetFirstLocalPlayerFromController();
	
	if(PC)
	{
		FString Name = PC->GetNickname();
		if(NameTagText)
			NameTagText->SetText(FText::FromString(Name));
	}
}
