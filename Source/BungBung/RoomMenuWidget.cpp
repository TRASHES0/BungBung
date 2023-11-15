// Fill out your copyright notice in the Description page of Project Settings.


#include "RoomMenuWidget.h"

#include "OnlineSubsystem.h"
#include "GameFramework/GameSession.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"

void URoomMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController();
	if(ClientSession.IsValid())
	{
		if(ClientSession.Session.OwningUserId->ToString() == *LocalPlayer->GetPreferredUniqueNetId()->ToString())
			if(StartButton)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("IS NOT MASTER CLIENT")));
				}
				StartButton->SetIsEnabled(false);
				return;
			}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Session Not Valid")));
		}
	}
	
	if(StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &ThisClass::URoomMenuWidget::StartButtonClicked);
	}
}

void URoomMenuWidget::StartButtonClicked()
{
	MenuTearDown();
	UWorld* World = GetWorld();
	if(World)
	{
		World->ServerTravel("/Game/Map/TestLand?listen");
	}
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
