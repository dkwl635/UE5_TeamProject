// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ChaosDungeonSubsystem.generated.h"

class UChaosDungeonEndUserWidget;
class AEnemySpawner;

UCLASS()
class UPORTFOLIO_RPG_API UChaosDungeonSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UChaosDungeonSubsystem();

	void StartDungeon();
	void EndDungeon();

	void SpawnEnemy();

	bool IsStarted() { return bIsStarted; }
	void AddPurification(int32 InValue);
	int32 GetPurification() { return Purification; }
	void SetEndWidget(UChaosDungeonEndUserWidget* InWidget) { EndMessage = InWidget; }

protected:
	bool bIsStarted = false;
	const float SpawnInterval = 5.f;
	const float TimeLimit = 300.f;
	int32 Purification = 0.f;

	FTimerHandle SpawnTimer;
	FTimerHandle FirstSpawnTimer;
	FTimerHandle DungeonLimitTimer;

	AEnemySpawner* Spawner = nullptr;
	UChaosDungeonEndUserWidget* EndMessage;
};
