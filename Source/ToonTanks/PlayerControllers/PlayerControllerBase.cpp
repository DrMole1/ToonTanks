// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PlayerControllerBase.cpp
// CLASSE : PlayerControllerBase
// DESCRIPTION : Gère le player controller, et la désactivation d'inputs
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
		GetPawn()->DisableInput(this); // Désactive les inputs
	}

	bShowMouseCursor = SetPlayerEnabled; // Active ou désactive le cursor
}