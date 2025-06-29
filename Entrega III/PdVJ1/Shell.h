#pragma once
#include "Afichmation.h"

using namespace std;
using namespace sf;

class Shell
{
private:
	string currentAnimation;
	Afichmation characterAnim;

public:
	Shell(const char* path, int width, int height,
		float startX, float startY,
		const string& animationName,
		int fps,
		bool loop)
		: currentAnimation(animationName), characterAnim(path, false, width, height)
	{
		characterAnim.Add(currentAnimation, { 0 }, fps, loop);
		characterAnim.setPosition(startX, startY);
	}

	// Sé que arruino el encapsulamiento pero necesito saber si colisionan con Mario
	Afichmation GetCharacterAnim() const { return characterAnim; }

	void move(int deltaX) { // Los enemigos (caparazones) se mueven solo en X, no tienen jump
		characterAnim.move(deltaX, 0);
	}

	int getX() const { return characterAnim.getPosition().x; }
	int getY() const { return characterAnim.getPosition().y; }

	void setPosition(int newX) {
		characterAnim.setPosition(newX, characterAnim.getPosition().y);
	}

	void flipX(bool flip) {
		characterAnim.FlipX(flip);
	}

	void flipY(bool flip) {
		characterAnim.FlipY(flip);
	}

	void flipAndMoveX(bool flip, int deltaX) {
		flipX(flip);
		move(deltaX);
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

	bool isCollidingWith(const Afichmation& other) const {
		return characterAnim.getGlobalBounds().intersects(other.getGlobalBounds());
	}
};
