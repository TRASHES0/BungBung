// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomMenuWidget.h"

#include "OnlineSubsystem.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

void URoomMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(GetWorld())
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString(TEXT("I AM MASTER")));
		}
		bIsMaster = true;
	}
	else
	{
		if(GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, FString(TEXT("I AM CLIENT")));
		}
		StartButtonText->SetText(FText::FromString("준비"));
		bIsMaster = false;
	}
	
	UserData = NewObject<UUserObject>();
	if(UserData)
	{
		UserData->PlayerName = GetWorld()->GetFirstPlayerController()->GetPlayerState<APlayerState>()->GetPlayerName();
		UserData->bIsMaster = bIsMaster;
		UserData->bIsReady = false;
	}

	SendPlayerData();
	
	UWorld* World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if(PlayerController)
		{
			PlayerController->SetShowMouseCursor(true);
		}
	}
	
	if(StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ThisClass::URoomMenuWidget::StartButtonClicked);
	}
}

void URoomMenuWidget::StartButtonClicked()
{
	if(bIsMaster)
	{
		MenuTearDown();
		UWorld* World = GetWorld();
		if(World)
		{
			World->ServerTravel("/Game/Map/TestLand", true);
		}
	}
	else
	{
		if(UserData->bIsReady)
		{
			UserData->bIsReady = false;
			StartButtonText->SetText(FText::FromString("READY"));
		}
		else
		{
			UserData->bIsReady = true;
			StartButtonText->SetText(FText::FromString("UNREADY"));
		}
		UpdatePlayerData();
	}
}

void URoomMenuWidget::SendPlayerData_Implementation()
{
	if(MultiplayerTileView)
	{
		MultiplayerTileView->AddItem(UserData);
	}
}

void URoomMenuWidget::UpdatePlayerData_Implementation()
{
	
}

void URoomMenuWidget::MenuTearDown()
{
	RemoveFromParent();
	UWorld* World = GetWorld();
	if(World)
	{
		APlayerController* PlayerController =World->GetFirstPlayerController();
		if(PlayerController)
		{
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(false);
		}
	}
}
