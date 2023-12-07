// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGameMode.h"

#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (GameState)
	{
		int32 NumberOfPlayers= GameState.Get()->PlayerArray.Num();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage
			(	
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Players in Game:%d "),NumberOfPlayers)
			);
		}
		APlayerState* PlayerState=NewPlayer->GetPlayerState<APlayerState>();
		if (PlayerState)
		{
			FString Playername=PlayerState->GetPlayerName();
			GEngine->AddOnScreenDebugMessage
			(
				-1,
				15.f,
				FColor::Cyan,
				FString::Printf(TEXT("%s has Joined Game! "), *Playername)

			);
		}
	}
}

void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>();
	if (PlayerState)
	{
		int32 NumberOfPlayers = GameState->PlayerArray.Num();
		if(GEngine)
			GEngine->AddOnScreenDebugMessage
			(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Players in Game:%d "), NumberOfPlayers-1)
			);
		FString Playername = PlayerState->GetPlayerName();
		GEngine->AddOnScreenDebugMessage
		(
			-1,
			15.f,
			FColor::Cyan,
			FString::Printf(TEXT("%s has Exited Game! "), *Playername)
		);
	}
}
