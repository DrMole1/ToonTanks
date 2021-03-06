// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PawnBase.h
// CLASSE : PawnBase
// DESCRIPTION : G?re les caract?ristiques des pawns, leur instantiations avec leurs components, leur d?placement, rotation, capacit? ? tirer
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

// D?claration forward
class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

private:
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComp;
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	// VARIABLES
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AProjectileBase> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects") // Particle de mort
	UParticleSystem* DeathParticle;
	UPROPERTY(EditAnywhere, Category = "Effects") // Son de mort
	USoundBase* DeathSound;
	UPROPERTY(EditAnywhere, Category = "Effects") // Camera shake de mort
	TSubclassOf<UCameraShake> DeathShake;

public:
	// Sets default values for this pawn's properties
	APawnBase();

	virtual void HandleDestruction();

protected:

	void RotateTurret(FVector LookAtTarget);

	void Fire();
};
