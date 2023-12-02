// Fill out your copyright notice in the Description page of Project Settings.


#include "NameTag.h"
#include "GameFramework/PlayerState.h"

void UNameTag::ServerSetNameText_Implementation(const FText& Name)
{
    if(NameTagText)
    {
        NameTagText->SetText(Name);
    }
}

void UNameTag::SetNameTag(const FText& Name)
{
    ServerSetNameText(Name);
}