// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PawnBase.cpp
// CLASSE : PawnBase
// DESCRIPTION : Gère les caractéristiques des pawns, leur instantiations avec leurs components, leur déplacement, rotation, capacité à tirer
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "ToonTanks/Actors/ProjectileBase.h"
#include "ToonTanks/Components/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APawnBase::APawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// On créée directement les components et on les mets enfant d'un autre component
	// Création d'une Capsule et attachement à la racine (en tant qu'enfant)
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	// Création d'un Static Mesh et attachement à la racine (en tant qu'enfant)
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	// Création d'un Static Mesh et attachement au static mesh précédent (en tant qu'enfant)
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	// Création d'une Scene et attachement au static mesh précédent (en tant qu'enfant)
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void APawnBase::RotateTurret(FVector LookAtTarget)
{
	// Update la rotation de la tourelle face à la cible 

	FVector LookAtTargetCleaned = FVector(LookAtTarget.X, LookAtTarget.Y, TurretMesh->GetComponentLocation().Z);
	FVector StartLocation = TurretMesh->GetComponentLocation();

	FRotator TurretRotation = FVector(LookAtTargetCleaned - StartLocation).Rotation();
	TurretMesh->SetWorldRotation(TurretRotation);
}

void APawnBase::Fire()
{
	// Spawn d'un projectile qui s'élance à la position ciblée
	//UE_LOG(LogTemp, Warning, TEXT("Fire Condition Success"));

	if (ProjectileClass)
	{
		FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();

		AProjectileBase* TempProjectile = GetWorld()->SpawnActor<AProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation);
		TempProjectile->SetOwner(this);
	}
}

void APawnBase::HandleDestruction()
{
	// Joue un effet de mort, son et camera shake
	// Destruction de l'objet
	// Informe le GameMode Player que l'objet est détruit et arrêt des inputs

	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation()); // Particles
	UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());      // Son
	GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(DeathShake);         // Camera shake
}