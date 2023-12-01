// Fill out your copyright notice in the Description page of Project Settings.


#include "NameTag.h"
#include "GameFramework/PlayerState.h"

void UNameTag::SetNameText_Implementation(const FString& Name)
{
    if(NameTagText)
    {
        NameTagText->SetText(FText::FromString(Name));
    }
}

bool UNameTag::Initialize()
{
    if(!Super::Initialize()) return false;

    if(ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
    {
        SetNameText(LocalPlayer->GetNickname());
    }
    
    return true;
}
