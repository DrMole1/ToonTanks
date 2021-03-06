// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : ProjectileBase.h
// CLASSE : ProjectileBase
// DESCRIPTION : G?re les caract?ristiques des projectiles, mouvement, polish, temps de vie
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;
UCLASS()
class TOONTANKS_API AProjectileBase : public AActor
{
	GENERATED_BODY()

private:
	// ==== COMPONENTS ====
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* ParticleTrail;

	// ==== VARIABLES ====
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TSubclassOf<UDamageType> DamageType;
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Move", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1300;
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float Damage = 50;

	UPROPERTY(EditAnywhere, Category = "Effects") // Particle au touch?
	UParticleSystem* HitParticle;
	UPROPERTY(EditAnywhere, Category = "Effects") // Son au touch?
	USoundBase* HitSound;
	UPROPERTY(EditAnywhere, Category = "Effects") // Son au lancement
	USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category = "Effects") // Camera shake au touch?
	TSubclassOf<UCameraShake> HitShake;

	// ==== FUNCTIONS ====
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
