// Fill out your copyright notice in the Description page of Project Settings.


#include "PCCharacter.h"
#include "Asadal/Asadal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
APCCharacter::APCCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	
	//Arm을 Root에 붙여준다.
	SpringArmComponent->SetupAttachment(RootComponent);

	//Camera를 Arm에 붙여준다.
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void APCCharacter::InputMoveForward(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("MoveForward <%.2f>"), Value);
	
	if (IsValid(Controller))
	{
		//if (Cast<ACPlayerController>(Controller)->bOnClick) return;
		// find out which way is forward
		//const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FRotator YawRotation(0, QUARTER_VIEW_ANGLE, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APCCharacter::InputMoveRight(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("MoveRight <%.2f>"), Value);
	
	if (IsValid(Controller))
	{
		//	if (Cast<ACPlayerController>(Controller)->bOnClick) return;
		// find out which way is right
		//const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, QUARTER_VIEW_ANGLE, 0.f);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

// Called when the game starts or when spawned
void APCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}