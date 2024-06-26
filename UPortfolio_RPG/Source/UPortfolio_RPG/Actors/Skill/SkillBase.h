// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"

class UAnimInstance;
class UNiagaraComponent;

enum class ESkillState
{
	Idle,
	Targeting
};

UCLASS()
class UPORTFOLIO_RPG_API ASkillBase : public AActor
{
	GENERATED_BODY()
	
public:
	virtual void ActiveSkill(UAnimInstance* AnimInstance);

protected:
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* Effect;

public:
	UPROPERTY(EditAnywhere)
	FName Sk_Name;
	UPROPERTY(EditAnywhere)
	FText Sk_Desc;
	UPROPERTY(EditAnywhere)
	float Sk_CoolTime;
	UPROPERTY(EditAnywhere)
	float Sk_Damage;
	UPROPERTY(EditAnywhere)
	float Sk_ManaUsage;
	UPROPERTY(EditAnywhere)
	float Sk_MaxDistance;
	UPROPERTY(EditAnywhere)
	UTexture2D* Sk_Image;
	UPROPERTY(EditAnywhere)
	UTexture2D* Sk_Image_Cool;
	UPROPERTY(EditAnywhere)
	UAnimMontage* Montage;
	
	bool bSuperArmor = false;	// 피면
	bool bSuperStance = false;	// 경면

	ESkillState CurrentSkillState = ESkillState::Idle;
};
