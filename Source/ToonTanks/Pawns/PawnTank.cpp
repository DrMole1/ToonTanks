// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PawnTank.cpp
// CLASSE : PawnTank
// DESCRIPTION : Gère les caractéristiques du tank, son instantiations avec ses components, capacité à tirer, déplacement, rotation
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
	// Création d'un Spring Arm et attachement à la racine (en tant qu'enfant)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	// Création d'une Camera et attachement au spring arm précédent (en tant qu'enfant)
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void APawnTank::HandleDestruction()
{
	Super::HandleDestruction();
	// Cache le joueur
	bIsPlayerAlive = false;

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

bool APawnTank::GetIsPlayerAlive()
{
	return bIsPlayerAlive;
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Fonctions appelées à chaque tick
	Rotate();
	Move();

	//Tourne la tourelle du tank selon le curseur
	if (PlayerControllerRef)
	{
		FHitResult TraceHitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);
		FVector HitLocation = TraceHitResult.ImpactPoint;

		RotateTurret(HitLocation);
	}
}

// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Bind pour toujours check si joueurs appuie sur inputs correspondants, puis lance la fonction
	PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
}

void APawnTank::CalculateMoveInput(float value)
{
	// Calcule un vecteur de direction
	MoveDirection = FVector(value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0);
}

void APawnTank::CalculateRotateInput(float value)
{
	// Calcule le quaternion à partir d'une rotation
	float RotateAmount = value * RotateSpeed * GetWorld()->DeltaTimeSeconds;
	FRotator Rotation = FRotator(0, RotateAmount, 0);
	RotationDirection = FQuat(Rotation);

}

void APawnTank::Move()
{
	// Bouger le tank
	AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate()
{
	// Pivoter le tank
	AddActorLocalRotation(RotationDirection, true);
}