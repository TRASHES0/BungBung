// Fill out your copyright notice in the Description page of Project Settings.


#include "NameTag.h"
#include "GameFramework/PlayerState.h"

void UNameTag::NativeConstruct()
{
	Super::NativeConstruct();
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if(APlayerState* PS = PC->GetPlayerState<APlayerState>())
	{
		FString Name = PS->GetPlayerName();
		if(NameTagText)
			NameTagText->SetText(FText::FromString(Name));
	}
}
