// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/Enemy.h"
#include "AI/EnemyAIController.h"
#include "Components/WidgetComponent.h"
#include "Enemy/EnemyPool.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
    IsAttacking = false;
    IsDead = false;
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    //BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Hpbarwidget"));
    EnemyState = CreateDefaultSubobject<UStatusComponent>(TEXT("EnemyState"));
    ParticleAttackSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleAttackSystemComponent"));
    ParticleAttackSystem = nullptr;

    Movement->MaxSpeed = 100.0f;
    Movement->Acceleration = 500.0f;
    Movement->Deceleration = 500.0f;
   
    SetRootComponent(CapsuleComponent);
    SkeletalMeshComponent->SetupAttachment(GetRootComponent());
    ParticleAttackSystemComponent->SetupAttachment(GetRootComponent());
  //  SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CapsuleComponent->SetCollisionProfileName(TEXT("Enemy"));

    StatusWidget->SetupAttachment(SkeletalMeshComponent);
    
    StatusWidget->SetWidgetSpace(EWidgetSpace::Screen);

    {
        static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/LJY/UI/UI_EnemyHPBar.UI_EnemyHPBar_C'"));
        if (UI_HUD.Succeeded())
        {
            StatusWidget->SetWidgetClass(UI_HUD.Class);
            StatusWidget->SetDrawSize(FVector2D(100.f, 50.0f));
        }
    }

    //AIController설정
    AIControllerClass = AEnemyAIController::StaticClass(); //나중에 데이터 테이블화 시키기
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

AEnemy::~AEnemy()
{
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
    DataSubsystem = GetGameInstance()->GetSubsystem<UDataSubsystem>();
    
    Init();
    UUserWidget* StatusUserWidget = StatusWidget->GetWidget();
    if (StatusUserWidget)
    {
        EnemyStatusUserWidget = Cast<UStatusbarUserWidget>(StatusUserWidget);
        if (EnemyStatusUserWidget)
        {
            EnemyStatusUserWidget->SetHP(this);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Error"));
        }
    }
}

void AEnemy::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController && !IsDead && !IsSpawn)
    {
        FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
        FVector MonsterLocation = GetActorLocation();
        FVector DirectionToPlayer = PlayerLocation - MonsterLocation;
        DirectionToPlayer.Z = 0.f;

        FRotator MonsterRotation = FRotationMatrix::MakeFromX(DirectionToPlayer).Rotator();
        MonsterRotation.Yaw -= 90.0f;

        SetActorRotation(MonsterRotation);
    }
}

void AEnemy::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    // Call the base class version of TakeDamage
    float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    if (!IsDead)
    {
        DisplayDamage(Damage);
        EnemyState->DamageToCurrentHP(Damage);
        UE_LOG(LogTemp, Warning, TEXT("Enemy_HP : %f"), EnemyState->GetCurrentHP());
    }

    if (EnemyState->GetCurrentHP() <= 0.f)
    {
        StatusWidget->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
        IsDead = true;
        EnemyAnim->Montage_Stop(0.1f);
    }

    return Damage;
}

void AEnemy::Attack()
{
    if (IsAttacking) return;
    if (IsDead) return;

    EnemyAnim->PlayAttackMontage();
    IsAttacking = true;
}

void AEnemy::AttackCheck()
{
    auto PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter)
    {
        FVector PlayerLocation = PlayerCharacter->GetActorLocation();
        FVector EnemyLocation = GetActorLocation();

        // 플레이어와 Enemy 사이의 거리 계산
        float Distance = FVector::Distance(PlayerLocation, EnemyLocation);

        // 공격 범위 내에 있는지 확인
        if (Distance <= 200.f)
        {
            ACharacter* Player = Cast<ACharacter>(PlayerCharacter);
            if (Player)
            {
                float Damage = EnemyState->GetRandDamage();
                UGameplayStatics::ApplyDamage(Player, Damage, GetController(), this, UDamageType::StaticClass());
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("NoAttackRange"));
        }
    }
}

void AEnemy::PlayAttackParticle()
{
    if (ParticleAttackSystem)
    {
        UGameplayStatics::SpawnEmitterAttached(
            ParticleAttackSystem, 
            CapsuleComponent, 
            FName(TEXT("EffectSocket")), 
            FVector(50.f,0,0), 
            FRotator(0,0,-90), 
            FVector(3.0f, 3.0f, 3.0f), 
            EAttachLocation::SnapToTargetIncludingScale, 
            true 
        );
    }
}

#include "UI/Damage/PrintDamageUserWidget.h"
#include "Actors/Damage/PrintDamageTextActor.h"
void AEnemy::DisplayDamage(float InDamage)
{
    const float RandX = FMath::RandRange(0, 50);
    const float RandY = FMath::RandRange(0, 50);
    const float RandZ = FMath::RandRange(0, 50);
    const FVector RandVector = FVector(RandX, RandY, RandZ);
    APrintDamageTextActor* Actor = GetWorld()->SpawnActor<APrintDamageTextActor>
        (APrintDamageTextActor::StaticClass());
    Actor->SetWidgetText(this, InDamage, GetActorLocation() + RandVector);
}

bool AEnemy::Init()
{
    AddEnemy(EnemyTypes[FMath::RandRange(0, EnemyTypes.Num()-1)]);
    return true;
}

bool AEnemy::AddEnemy(const FName& InKey)
{
    FEnemyData* InData = DataSubsystem->FindEnemyData(InKey);
    FStatusDataTableRow* InStatus = DataSubsystem->FindEnemyStatusData(InKey);
    if (!InData && !InStatus)
    {
        check(false);
        return false;
    }
    else
    {
        CapsuleComponent->SetCapsuleRadius(InData->CapsuleRadius);
        CapsuleComponent->SetCapsuleHalfHeight(InData->CapsuleHalfHeight);
        
        SkeletalMeshComponent->SetSkeletalMesh(InData->SkeletalMesh);
        SkeletalMeshComponent->SetAnimClass(InData->AnimClass);
        SkeletalMeshComponent->SetRelativeTransform(InData->SkeletalMeshTransform);

        EnemyState->SetStatusData(InStatus);

        Movement->MaxSpeed = EnemyState->GetSpeed();
        PurificationScore = FMath::RandRange(100, 200);

        FVector HeadPosition = SkeletalMeshComponent->GetBoneLocation(TEXT("head"));
        StatusWidget->SetWorldLocation(HeadPosition + FVector(0.0f, 0.0f, 30.0f));

        ParticleAttackSystem = InData->ParticleAttackSystem;

        if (ParticleAttackSystem)
        {
            ParticleAttackSystemComponent->SetTemplate(ParticleAttackSystem);
        }
        ParticleAttackSystemComponent->SetRelativeTransform(InData->ParticleTransform);

        EnemyAnim = Cast<UEnemyAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
        ensure(EnemyAnim);

        OwningController = Cast<AEnemyAIController>(GetController());

        return true;
    }

}

void AEnemy::Reset()
{
    IsSpawn = false;
    IsAttacking = false;
    EnemyState->SetCurrentHP(EnemyState->GetMaxHP());
    StatusWidget->GetWidget()->SetVisibility(ESlateVisibility::Visible);
}
//Impact

