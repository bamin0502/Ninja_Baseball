﻿#pragma once
#include "Animator.h"
#include "SpriteGo.h"

class SceneDev1;
class Player;

class Enemy:public SpriteGo
{
public :
    enum class EnemyState
    {
        IDLE,
        MOVE,
        ATTACK,
        DASH,
        HURT,
        DEAD,
        CATCHED,
    };
    EnemyState currentEnemy=EnemyState::IDLE;
    enum class EnemyPattern
    {
        MOVE,
        DASH,
        ATTACK,
        CATCH,
        DAMAGE,
    };
    EnemyPattern currentPattern=EnemyPattern::MOVE;
protected:
    SceneDev1* Scene;
    Player* player;
    Animator enemyAnimator;
    
    float speed = 60.f;

    int health = 100;
    int maxHealth=100;
    int damage = 10;
    int damageCount;
    
    bool isDead = false;
    
    bool isReadyToDash =false;
    bool isDash =false;
    
    bool isAttack = false;
    bool isAttackCoolOn = false;
    bool isAttacking=false;
    bool isAttackReady = false;
    
    bool isYPositionLocked = false;
    bool isCatched = false;
    
    
    bool isInvincible = false;
    float invincibleTime = 0.2f;
    
    float dashSpeed = 400.f;
    float dashCooldown = 3.f;
    float dashCooldownTimer = 0.f;
    float acceptableYDistance = 15.f;
    float attackTimer = 0.f;
    const float attackCooldown = 2.5f;
    float dashYPos;
    float attackReadyTimer = 0.0f;
    
    sf::Vector2f dashDirection;
    sf::Vector2f dashStartPosition;
    float dashMaxDistance=300;
    
    sf::FloatRect playerBounds;
    sf::FloatRect damageBounds;

    sf::FloatRect playerHitBox;

    sf::RectangleShape damageBox;
    sf::RectangleShape attackBox;
    sf::Vector2f attackBoxSize = { 20, 20 };
    sf::Vector2f playerPos;
public:
    Enemy(const std::string& name);
    
    void Init() override;
    void Release() override;
    void Reset() override;
    
    void Update(float dt) override;
    void LateUpdate(float dt) override;
    void FixedUpdate(float dt) override;
    void Draw(sf::RenderWindow& window) override;
    
    void SetSpeed(float newSpeed) { speed = newSpeed; }
    float GetHealth() const { return health; }
    void SetPosition(const sf::Vector2f& position) override
    {
        SpriteGo::SetPosition(position);
        //sprite.setPosition(position);
    }

    void DashTowards(float dt);
    virtual void Attack();
    virtual void OnDamage(int damage,int count);
    
    void MoveTowards(const sf::Vector2f& target, float dt);
    static sf::Vector2f Normalize(const sf::Vector2f& source);
    virtual void TargetDirection(const sf::Vector2f& playerPosition);
    
    void SetPlayerHitBox(const sf::FloatRect& hitBox) { playerHitBox = hitBox; }
    bool CheckHitBox() const { return attackBox.getGlobalBounds().intersects(playerHitBox); }
    virtual void DashToPlayer(float dt, sf::Vector2f& currentPosition);
    virtual void StartDash(const sf::Vector2f& playerPosition, const sf::Vector2f& currentPosition);
    virtual void NormalMovement(float dt, sf::Vector2f& currentPosition, const sf::Vector2f& playerPosition, float xDistance, float yDistance);
    virtual void CheckAndResolveOverlap(std::vector<Enemy*>& allEnemies);
    virtual sf::FloatRect GetHitBox() const;
    virtual sf::FloatRect GetDamageBox() const;
    virtual void Catch();
    virtual void Damage();

    virtual void SetEnemyPettarn(float dt);
};
