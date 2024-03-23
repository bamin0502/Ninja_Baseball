﻿#include "pch.h"
#include "Enemy.h"
#include "Player.h"
#include "SceneDev1.h"

Enemy::Enemy(const std::string& name): SpriteGo(name), Scene(nullptr), player(nullptr), dashYPos(0)
{
}

void Enemy::Init()
{
    SpriteGo::Init();
    enemyAnimator.SetTarget(&sprite);
}

void Enemy::Release()
{
    SpriteGo::Release();
}

void Enemy::Reset()
{
    health = maxHealth;
    Scene = dynamic_cast<SceneDev1*>(SCENE_MANAGER.GetCurrentScene());
    if (Scene != nullptr)
    {
        position = Scene->ClampByTileMap(position);
    }

    player = dynamic_cast<Player*>(SCENE_MANAGER.GetCurrentScene()->FindGameObject("Player"));
    sf::Vector2f targetPosition = player->GetPosition();
    playerPos= targetPosition;
}

void Enemy::Update(float dt)
{

    if (isDead || player == nullptr) return;
    
    sf::Vector2f playerPosition = player->GetPosition();
    sf::Vector2f currentPosition = sprite.getPosition();
    TargetDirection(playerPosition);
    float yDistance = std::abs(playerPosition.y - currentPosition.y);
    float xDistance = std::abs(playerPosition.x - currentPosition.x);

    // 대쉬 쿨다운 업데이트
    if (dashCooldownTimer > 0) dashCooldownTimer -= dt;

    // 대쉬 조건 체크
    if (!isDash && xDistance >= 400 && yDistance <= acceptableYDistance && dashCooldownTimer <= 0) {
        StartDash(playerPosition, currentPosition);
    }

    if (isDash) {
        // 대쉬 이동 로직
        DashToPlayer(dt, currentPosition);
    } else {
        // 일반 이동 로직
        NormalMovement(dt, currentPosition, playerPosition, xDistance, yDistance);
    }

    // 위치 업데이트
    sprite.setPosition(currentPosition);
    // 애니메이션 및 기타 업데이트
    enemyAnimator.Update(dt);
}

void Enemy::LateUpdate(float dt)
{
    SpriteGo::LateUpdate(dt);
}

void Enemy::FixedUpdate(float dt)
{
    SpriteGo::FixedUpdate(dt);
}

void Enemy::Draw(sf::RenderWindow& window)
{
    SpriteGo::Draw(window);

    if (SCENE_MANAGER.GetDeveloperMode())
    {
        window.draw(damageBox);
        window.draw(attackBox);
    }
   
}

void Enemy::OnDamage(int damage)
{
    health -= damage;
    if(health <= 0)
    {
        isDead = true;
    }
}

void Enemy::DashTowards(const sf::Vector2f& target, float dt)
{
    if (!isReadyToDash) return;
    sf::Vector2f direction = Normalize(player->GetPosition() - sprite.getPosition());
    sprite.move(direction * speed * dt);
}

void Enemy::Attack()
{
    attackTimer = attackCooldown;
    if(player != nullptr)
    {
        //player->OnDamage(damage);
        std::cout << "Player Hit" << std::endl;
        
    }
}

void Enemy::MoveTowards(const sf::Vector2f& target, float dt)
{
    sf::Vector2f currentPosition = sprite.getPosition();
    float distanceToTarget = Utils::MyMath::Distance(target, currentPosition);
    
    const float minDistance = 500.0f;  
    
    if (distanceToTarget > minDistance)
    {
        float yDistance = std::abs(target.y - currentPosition.y);
        float xDistance = std::abs(target.x - currentPosition.x);

        sf::Vector2f moveDirection(0.0f, 0.0f);


        if (yDistance > acceptableYDistance) {
            moveDirection.y = (target.y > currentPosition.y) ? 1.0f : -1.0f;
        }


        if (yDistance <= acceptableYDistance) {
            moveDirection.x = (target.x > currentPosition.x) ? 1.0f : -1.0f;
        }


        if (moveDirection != sf::Vector2f(0.0f, 0.0f)) {
            sf::Vector2f normalizedDirection = Normalize(moveDirection);
            sprite.move(normalizedDirection * speed * dt);
            position = sprite.getPosition(); 
        }
    }
}

sf::Vector2f Enemy::Normalize(const sf::Vector2f& source)
{
    float length = std::hypot(source.x, source.y);
    if (length != 0) {
        return sf::Vector2f(source.x / length, source.y / length);
    }
    return source;
}

void Enemy::TargetDirection(const sf::Vector2f& playerPosition)
{
    if (playerPosition.x < sprite.getPosition().x) {
        sprite.setScale(1.0f, 1.0f);
    }
    else {
        sprite.setScale(-1.0f, 1.0f);
    }
}

void Enemy::SetBox(bool flip)
{
    if (flip)
    {
        attackBox.setPosition({ sprite.getPosition().x - attackBox.getSize().x, sprite.getPosition().y - attackBox.getSize().y });
        damageBox.setPosition({ sprite.getPosition().x - damageBox.getSize().x, sprite.getPosition().y - damageBox.getSize().y });
    }
    else
    {
        attackBox.setPosition({ sprite.getPosition().x, sprite.getPosition().y - attackBox.getSize().y });
        damageBox.setPosition({ sprite.getPosition().x, sprite.getPosition().y - damageBox.getSize().y });
    }
}


void Enemy::DashToPlayer(float dt, sf::Vector2f& currentPosition)
{
    // 대쉬 이동
    currentPosition += dashDirection * dashSpeed * dt;

    // 대쉬 종료 조건 (예: 일정 거리 이동)
    if (Utils::MyMath::Distance(dashStartPosition, currentPosition) >= dashMaxDistance) {
        isDash = false;
    }
}


void Enemy::StartDash(const sf::Vector2f& playerPosition, const sf::Vector2f& currentPosition)
{
    dashDirection = Normalize(playerPosition - currentPosition);
    dashStartPosition = currentPosition;
    isDash = true;
    dashCooldownTimer = dashCooldown; // 대쉬 후 쿨다운 재설정
}


void Enemy::NormalMovement(float dt, sf::Vector2f& currentPosition, const sf::Vector2f& playerPosition, float xDistance,
    float yDistance)
{
    // Y축 조정
    if (yDistance > acceptableYDistance) {
        currentPosition.y += (playerPosition.y > currentPosition.y ? 1 : -1) * speed * dt;
    }
    // X축으로 접근하지만 플레이어와 200 이상의 거리 유지
    if (xDistance > 200) {
        currentPosition.x += (playerPosition.x > currentPosition.x ? 1 : -1) * speed * dt;
    }
}
