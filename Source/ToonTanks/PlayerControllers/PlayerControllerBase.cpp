// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PlayerControllerBase.cpp
// CLASSE : PlayerControllerBase
// DESCRIPTION : G?re le player controller, et la d?sactivation d'inputs
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#include "PlayerControllerBase.h"

void APlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled)
{
	if (SetPlayerEnabled)
	{
		GetPawn()->EnableInput(this); // Active les inputs
	}
	else
	{
		GetPawn()->DisableInput(this); // D?sactive les inputs
	}

	bShowMouseCursor = SetPlayerEnabled; // Active ou d?sactive le cursor
}