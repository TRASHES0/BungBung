// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMenuWidget.h"


bool ULobbyMenuWidget::Initialize()
{
	if(!Super::Initialize()) return false;

	if(HostButton)
	{
		HostButton->OnClicked.AddDynamic(this, &ULobbyMenuWidget::HostButtonClicked);
	}

	return true;
}

void ULobbyMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UGameInstance* GameInstance = GetGameInstance();
	if (GameInstance)
	{
		MultiplayerSessionSubsystem = GameInstance->GetSubsystem<UMultiplayerSessionSubsystem>();
	}

	// Binding callbacks to Delegates of the MultiplayerSessionSubsystem class
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->MultiplayerOnCreateSessionComplete.AddDynamic(this, &ThisClass::OnCreateSession);
	}
}

void ULobbyMenuWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void ULobbyMenuWidget::OnCreateSession(bool bWasSuccessful)
{
	if (bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString(TEXT("Session created successfully!")));
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString(TEXT("Failed to create session!")));
		}

		HostButton->SetIsEnabled(true);
	}
}

void ULobbyMenuWidget::HostButtonClicked()
{
	HostButton->SetIsEnabled(false);
	if (MultiplayerSessionSubsystem)
	{
		MultiplayerSessionSubsystem->CreateSession(NumPublicConnections, MatchType);
	}
}
