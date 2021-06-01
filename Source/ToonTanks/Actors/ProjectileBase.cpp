// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : ProjectileBase.cpp
// CLASSE : ProjectileBase
// DESCRIPTION : Gère les caractéristiques des projectiles, mouvement, polish, temps de vie
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#include "ProjectileBase.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Mesh du projectile
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	RootComponent = ProjectileMesh;

	// Vitesse du projectile
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = MovementSpeed;
	ProjectileMovement->MaxSpeed = MovementSpeed;

	// Création du Particle Trail
	ParticleTrail = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Trail"));
	ParticleTrail->SetupAttachment(RootComponent);

	// Temps de vie du projectile avant destruction
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Essaie d'avoir la référence de la owing class
	AActor* MyOwner = GetOwner();

	// Si c'est pas le cas, return
	if (!MyOwner)
	{
		return;
	}

	// Si l'acteur n'est pas lui-même ou l'owner, et que celui-ci existe : applique damage
	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner->GetInstigatorController(), this, DamageType);  // Applique dégâts
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticle, GetActorLocation());                          // Particle
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());                                // Sound
		GetWorld()->GetFirstPlayerController()->ClientPlayCameraShake(HitShake);                                  // Camera shake
		Destroy();
	}
}