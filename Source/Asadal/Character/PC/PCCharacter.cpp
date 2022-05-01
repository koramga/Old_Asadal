// Fill out your copyright notice in the Description page of Project Settings.


#include "PCCharacter.h"

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
}

void APCCharacter::InputMoveRight(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("MoveRight <%.2f>"), Value);
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