// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : TankGameModeBase.cpp
// CLASSE : TankGameModeBase
// DESCRIPTION : Gère le GameMode : actions de début de partie et actions de fin de partie
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#include "TankGameModeBase.h"
#include "ToonTanks/Pawns/PawnTank.h"
#include "ToonTanks/Pawns/PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanks/PlayerControllers/PlayerControllerBase.h"

void ATankGameModeBase::BeginPlay()
{
	// Actions à faire dès le premier tick du jeu
	Super::BeginPlay();

	HandleGameStart();
}

void ATankGameModeBase::ActorDied(AActor* DeadActor)
{
	// Actions à faire quand un acteur meurt
	UE_LOG(LogTemp, Warning, TEXT("A Pawn died !"));

	if (DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		HandleGameOver(false);

		if (PlayerControllerRef)
		{
			PlayerControllerRef->SetPlayerEnabledState(false);
		}
	}
	else if (APawnTurret* DestroyedTurret = Cast<APawnTurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();

		// Si le nombre de tourelles en jeu == 0, alors game over
		if (--TargetTurrets == 0)
		{
			HandleGameOver(true);
		}
	}
}

void ATankGameModeBase::HandleGameStart()
{
	// Actions à faire au début de la partie de jeu
	TargetTurrets = GetTargetTurretCount();
	PlayerTank = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	PlayerControllerRef = Cast<APlayerControllerBase>(UGameplayStatics::GetPlayerController(this, 0));

	GameStart();

	if (PlayerControllerRef)
	{
		PlayerControllerRef->SetPlayerEnabledState(false);
		
		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(PlayerControllerRef, &APlayerControllerBase::SetPlayerEnabledState, true);
		GetWorld()->GetTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);

	}
}

void ATankGameModeBase::HandleGameOver(bool PlayerWon)
{
	// Actions à faire pour un game over
	GameOver(PlayerWon);
}

int32 ATankGameModeBase::GetTargetTurretCount()
{
	// Compte le nombre de tourelles encore en jeu
	TArray<AActor*> TurretActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawnTurret::StaticClass(), TurretActors);
	return TurretActors.Num();
}