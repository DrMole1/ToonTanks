// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PlayerControllerBase.h
// CLASSE : PlayerControllerBase
// DESCRIPTION : Gère le player controller, et la désactivation d'inputs
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APlayerControllerBase : public APlayerController
{
	GENERATED_BODY()

public:

	void SetPlayerEnabledState(bool SetPlayerEnabled);
};
