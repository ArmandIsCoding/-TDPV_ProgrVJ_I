#pragma once
#include "Afichmation.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject {
protected:
    Afichmation background;

public:
    GameObject(const std::string& spritePath, Vector2f pos, Vector2i frameSize, float scale = 1.f)
        : background(spritePath, true, frameSize.x, frameSize.y) {
        background.setPosition(pos);
        background.setScale(scale, scale);
    }

    virtual void Update(float deltaTime) {
        Animate(deltaTime);
        background.Update();
    }

    virtual void Animate(float deltaTime) = 0;

    virtual void Render(RenderWindow& window) {
        window.draw(background);
    }

    virtual void SetPosition(Vector2f pos) {
        background.setPosition(pos);
    }

    Vector2f getPosition() const {
        return background.getPosition();
    }

    virtual FloatRect getBounds() {
        return background.getGlobalBounds();
    }

    FloatRect adjustHitbox(FloatRect original, float top, float bottom, float left, float right) {
        original.top += top;
        original.left += left;
        original.width -= (left + right);
        original.height -= (top + bottom);
        return original;
    }

    void drawHitbox(RenderWindow& window) {
        FloatRect bounds = getBounds();
        RectangleShape hitboxVisual;
        hitboxVisual.setPosition(bounds.left, bounds.top);
        hitboxVisual.setSize(Vector2f(bounds.width, bounds.height));
        hitboxVisual.setFillColor(Color::Transparent);
        hitboxVisual.setOutlineColor(Color::Red);
        hitboxVisual.setOutlineThickness(1.f);
        window.draw(hitboxVisual);
    }
};
