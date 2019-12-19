// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacterController.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASCharacterController::ASCharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SkinMeshComp = CreateDefaultSubobject<USkeletalMesh>(TEXT("SkinMeshComp"));

	ArmCameraComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("ArmCameraComp"));
	ArmCameraComp->bUsePawnControlRotation = true;
	ArmCameraComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(ArmCameraComp);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

}

// Called when the game starts or when spawned
void ASCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	OriginRotation = GetActorRotation();
}

void ASCharacterController::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector()*value);
}

void ASCharacterController::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector()*value);
}

void ASCharacterController::BeginCrouch()
{

}

void ASCharacterController::EndCrouch()
{

}

// Called every frame
void ASCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector velocity = GetVelocity();
	AnimationsSpeed = velocity.Size();
	
	FVector ActorLocation = GetActorLocation();
	
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, ActorLocation + velocity);

	CurrentRotation = FMath::Lerp(CurrentRotation, rotation, DeltaTime);
	
	USkeletalMeshComponent * MeshComp = GetMesh();
	MeshComp->SetRelativeRotation(CurrentRotation);
}

// Called to bind functionality to input
void ASCharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacterController::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacterController::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacterController::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacterController::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ASCharacterController::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &ASCharacterController::EndCrouch);
}

