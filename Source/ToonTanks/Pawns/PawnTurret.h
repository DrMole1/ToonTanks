// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PawnTurret.h
// CLASSE : PawnTurret
// DESCRIPTION : Gère les caractéristiques des tourelles, leur instantiations avec leurs components, capacité à tirer, portée, vitesse de tir
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

// Déclaration forward
class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:

	// UPROPERTY pour permettre d'éditer partout, lire et éditer dans les blueprints, dans une catégorie Combat, en accordant un accés privé
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;
	// UPROPERTY pour permettre d'éditer partout, lire et éditer dans les blueprints, dans une catégorie Combat, en accordant un accés privé
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.0f;

	FTimerHandle FireRateTimerHandle;

	// Référence au pawn
	APawnTank* PlayerPawn;

	void CheckFireCondition();

	float ReturnDistanceToPlayer();

	

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void HandleDestruction() override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
