// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "StatusbarUserWidget.generated.h"

class AEnemy;
class AMonster;

UCLASS()
class UPORTFOLIO_RPG_API UStatusbarUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHP(AEnemy* InEnemy);
	void SetMonsterHP(AMonster* InMonster);

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HPBar = nullptr;

	AEnemy* Owner = nullptr;
	AMonster* MonsterOwner = nullptr;
};
