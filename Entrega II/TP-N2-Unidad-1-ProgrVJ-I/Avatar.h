#pragma once

#include <SFML/Graphics.hpp>
#include "Afichmation.h"
#include "Audio.h"
#include "GameObject.h"

class Avatar : public GameObject {
    Audio jump, land, running, walk;

    float speed = 90.f;
    float jumpSpeed = 330.f;
    float gravity;
    float velocityY = 0.f;

    bool inAir = false;
    bool jumpStarted = false;
    bool fallStarted = false;

    sf::Keyboard::Key leftKey = sf::Keyboard::A;
    sf::Keyboard::Key rightKey = sf::Keyboard::D;
    sf::Keyboard::Key runKey = sf::Keyboard::LShift;
    sf::Keyboard::Key jumpKey1 = sf::Keyboard::Space;
    sf::Keyboard::Key jumpKey2 = sf::Keyboard::W;

public:
    Avatar(sf::Vector2f pos, float worldGravity);

    void Update(float deltaTime) override;
    void HandleEvents(sf::Event& e);
    void Animate(float deltaTime) override;

    void Move(float deltaTime);
    void ApplyGravity(float deltaTime);

    bool IsIdle();
    void CheckScreenBounds();

    sf::FloatRect getBounds() override;

    float GetVelocityY() const { return velocityY; }
    void SetVelocityY(float v) { velocityY = v; }
};