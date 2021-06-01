// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PawnTurret.cpp
// CLASSE : PawnTurret
// DESCRIPTION : Gère les caractéristiques des tourelles, leur instantiations avec leurs components, capacité à tirer, portée, vitesse de tir
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#include "PawnTurret.h"
#include "Kismet/GameplayStatics.h"
#include "PawnTank.h"

// Called when the game starts or when spawned
void APawnTurret::BeginPlay()
{
	Super::BeginPlay();

	// Déclaration du timer
	GetWorld()->GetTimerManager().SetTimer(FireRateTimerHandle, this, &APawnTurret::CheckFireCondition, FireRate, true);

	// Variable de type PawnTank (avec un cast) où on affecte le premier pawn du jeu
	PlayerPawn = Cast<APawnTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APawnTurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

// Called every frame
void APawnTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ReturnDistanceToPlayer() > FireRange)
	{
		return;
	}

	RotateTurret(PlayerPawn->GetActorLocation());
}

void APawnTurret::CheckFireCondition()
{
	// If player == null || is dead then bail
	if (!PlayerPawn || !PlayerPawn->GetIsPlayerAlive())
	{
		return;
	}
	// If player is in range then fire
	if (ReturnDistanceToPlayer() <= FireRange)
	{
		//Fire
		Fire();
	}
}

float APawnTurret::ReturnDistanceToPlayer()
{
	if (!PlayerPawn)
	{
		return 0.0f;
	}

	// Calcule la distance entre la tourelle et le joueur
	return FVector::Dist(PlayerPawn->GetActorLocation(), GetActorLocation());
}