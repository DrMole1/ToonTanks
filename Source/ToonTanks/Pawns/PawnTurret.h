// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PawnTurret.h
// CLASSE : PawnTurret
// DESCRIPTION : G?re les caract?ristiques des tourelles, leur instantiations avec leurs components, capacit? ? tirer, port?e, vitesse de tir
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTurret.generated.h"

// D?claration forward
class APawnTank;

UCLASS()
class TOONTANKS_API APawnTurret : public APawnBase
{
	GENERATED_BODY()

private:

	// UPROPERTY pour permettre d'?diter partout, lire et ?diter dans les blueprints, dans une cat?gorie Combat, en accordant un acc?s priv?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRate = 2.0f;
	// UPROPERTY pour permettre d'?diter partout, lire et ?diter dans les blueprints, dans une cat?gorie Combat, en accordant un acc?s priv?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float FireRange = 500.0f;

	FTimerHandle FireRateTimerHandle;

	// R?f?rence au pawn
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
