// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class UNiagaraSystem;
struct FInputActionValue;
class APlayerCharacter;
class UCoolTimeSubsystem;
class USpringArmComponent;

UCLASS()
class UPORTFOLIO_RPG_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABasicPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void SetupInputComponent() override;

public:
	UCoolTimeSubsystem* GetCoolTimeManager() const;

protected:
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased(); 
	void OnDefaultAttack();
	void OnSkill_Q();
	void OnSkill_W();
	void OnSkill_E();
	void OnSkill_R();
	void OnSpace();

	void OnZoomWheel(const FInputActionValue& InputActionValue);
	
private:
	FVector CachedDestination;
	APlayerCharacter* PlayerCharacter;

protected:
	UPROPERTY()
	USpringArmComponent* PawnSpringArm = nullptr;
	float TargetArmLength = 500.f;
};
