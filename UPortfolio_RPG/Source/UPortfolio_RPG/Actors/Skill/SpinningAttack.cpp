// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/SpinningAttack.h"
#include "Enemy/Enemy.h"

ASpinningAttack::ASpinningAttack()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMesh);
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
		ensure(Asset.Object);
		StaticMesh->SetStaticMesh(Asset.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/Skill/SpinningAttack_Montage.SpinningAttack_Montage'"));
		ensure(Asset.Object);
		this->Montage = Asset.Object;
	}
	StaticMesh->SetRelativeScale3D(FVector(4.565000, 3.735000, 1.660000));
	StaticMesh->SetCollisionProfileName(TEXT("PlayerSkill"));
	StaticMesh->bHiddenInGame = false;
}

void ASpinningAttack::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnAttack);
}

float ASpinningAttack::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Owner = DamageCauser;

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ASpinningAttack::OnAttack(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if(Enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpinningAttack Hit!"));
	}
}