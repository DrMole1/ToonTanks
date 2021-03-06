// Fill out your copyright notice in the Description page of Project Settings.

// ========================================================================================
// FICHIER : PawnTank.h
// CLASSE : PawnTank
// DESCRIPTION : G?re les caract?ristiques du tank, son instantiations avec ses components, capacit? ? tirer, d?placement, rotation
// DEVELOPPEUR : Prob Bastien
// ========================================================================================

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

// Forward d?clarations
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
	
private:

	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	// UPROPERTY pour permettre de voir partout, lire dans les blueprints, dans une cat?gorie Component, en accordant un acc?s priv?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	// Varkiables pour le d?placement et la rotation
	FVector MoveDirection;
	FQuat RotationDirection;

	// UPROPERTY pour permettre d'?diter partout, lire et ?diter dans les blueprints, dans une cat?gorie Movement, en accordant un acc?s priv?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 100.0f;
	// UPROPERTY pour permettre d'?diter partout, lire et ?diter dans les blueprints, dans une cat?gorie Movement, en accordant un acc?s priv?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 100.0f;

	APlayerController* PlayerControllerRef;
	bool bIsPlayerAlive = true;

	void CalculateMoveInput(float value);
	void CalculateRotateInput(float value);

	void Move();
	void Rotate();


public:

	APawnTank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void HandleDestruction() override;

	// Retourne si le joueur est en vie ou non
	bool GetIsPlayerAlive();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};