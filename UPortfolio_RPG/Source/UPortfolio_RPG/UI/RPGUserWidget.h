// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIEnum.h"
#include "RPGUserWidget.generated.h"

/**
 * 
 */	
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Dynamic_OneParam, ERPG_UI, SomeParameter);

UCLASS(BlueprintType)
class UPORTFOLIO_RPG_API URPGUserWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_Type")
	ERPG_UI UI_Type;

protected:
	UFUNCTION(BlueprintCallable)
	void HideUI();

public:
	UFUNCTION(BlueprintCallable)
	virtual void RefreshUI();
	UFUNCTION(BlueprintCallable)
	virtual void Init();
	
	UFUNCTION(BlueprintCallable)
	virtual void ShowInitUI();

	UFUNCTION(BlueprintCallable)
	virtual void HideSetUI();

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic_OneParam StartUIMove;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic_OneParam EndUIMove;

public:
	class UCanvasPanelSlot* GetCanvasPanelSlot();

private:
	class UCanvasPanelSlot* CanvasPaneSlot;
};
