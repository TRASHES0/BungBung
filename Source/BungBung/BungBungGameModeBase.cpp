// Copyright Epic Games, Inc. All Rights Reserved.


#include "BungBungGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"

void ABungBungGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if(CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromParent();
		CurrentWidget = nullptr;
	}
	if(NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget(GetWorld(), NewWidgetClass);
		if(CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ABungBungGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);
	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
}

