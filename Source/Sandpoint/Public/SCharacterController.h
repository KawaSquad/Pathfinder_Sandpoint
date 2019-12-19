// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacterController.generated.h"

class USkeletalMesh;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SANDPOINT_API ASCharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacterController();

protected:

	//UPROPERTY(VisibleAnywhere,Category = "Components")
	//	USkeletalMesh * SkinMeshComp;

	UPROPERTY(VisibleAnywhere,Category = "Components")
		UCameraComponent * CameraComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USpringArmComponent * ArmCameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Values")
		float AnimationsSpeed;

	FRotator OriginRotation;
	FRotator CurrentRotation;


	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);
	void MoveRight(float value);

	void BeginCrouch();
	void EndCrouch();

	//void LookUp(float value);
	//void LookUp(float value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
