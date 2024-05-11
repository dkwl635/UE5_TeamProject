// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UPORTFOLIO_RPG_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	float GetHP() { return HP; }
	void SetHP(float InHP) { HP = InHP; }
	float GetMP() { return MP; }
	void SetMP(float InMP) { MP = InMP; }
	float GetAttackDamage() { return AttackDamage; }
	void SetAttackDamage(float Damage) { AttackDamage = Damage; }
	void SetSuperArmor(bool InSuperArmor) { bSuperArmor = InSuperArmor; }
	void SetSuperStance(bool InSuperStance) { bSuperStance = InSuperStance; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HP = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MP = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackDamage = 100.f;

	bool bSuperArmor;
	bool bSuperStance;



	//add LJY EnemyState
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Enemy_HP = 0.f;  //datatable init, not zero
	float Enemy_AttackDamage = 10.f;

public:
	float GetEnemyHP() { return Enemy_HP; }
	void SetEnemyHP(float InHP) { Enemy_HP = InHP; }
	float GetEnemyAttackDamage() { return Enemy_AttackDamage; }
	void SetEnemyAttackDamage(float Damage) { Enemy_AttackDamage = Damage; }

};
