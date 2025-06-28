#pragma once
#include "Afichmation.h"

using namespace std;
using namespace sf;

// Disclaimer: Mario no es animado asi que me tome algunas licencias.

class Mario
{
private:
    int lives;
    string currentAnimation;
    Afichmation characterAnim;

public:
    Mario(const char* path, int width, int height,
        float startX, float startY,
        int initialLives,
        const string& animationName,
        //const vector<int>& frames, // no me salió :-( https://s3.amazonaws.com/rails-camp-tutorials/blog/programming+memes/works-doesnt-work.jpg
        int fps,
        bool loop)
        : lives(initialLives),
        currentAnimation(animationName),
        characterAnim(path, false, width, height)
    {
        characterAnim.Add(currentAnimation, { 0 }, fps, loop);
        characterAnim.setPosition(startX, startY);
    }

    void move(int deltaX, int deltaY) {
        characterAnim.move(deltaX, deltaY);
    }

    void loseLife() {
        if (lives > 0) {
            lives--;
        }
    }

    int getX() const { return characterAnim.getPosition().x; }
    int getY() const { return characterAnim.getPosition().y; }
    int getLives() const { return lives; }

    void setPosition(int newX, int newY) {
        characterAnim.setPosition(newX, newY);
    }

    void flipX(bool flip) {
        characterAnim.FlipX(flip);
    }

    void flipY(bool flip) {
        characterAnim.FlipY(flip);
    }

    void playAnimation(const string& animation) {
        characterAnim.Play(animation);
    }

    void update() {
        characterAnim.Update();
    }

    void draw(RenderWindow* w) {
        w->draw(characterAnim);
    }

    void flipAndMove(bool flip, int deltaX, int deltaY) {
        flipX(flip);
        move(deltaX, deltaY);
	}

    void flipAndMoveX(bool flip, int deltaX) {
        flipX(flip);
        move(deltaX, 0);
    }

    void flipAndJump(bool flip, int deltaY) {
        flipY(flip);
        setPosition(getX(), deltaY);
	}

    bool isCollidingWith(const Afichmation& other) const {
        return characterAnim.getGlobalBounds().intersects(other.getGlobalBounds());
    }
};
