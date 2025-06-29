#pragma once
#include "Afichmation.h"
#include <SFML/Audio.hpp>
#include "SoundManager.h"

using namespace std;
using namespace sf;

// Disclaimer: Mario no es animado asi que me tome algunas licencias.

class Mario
{
private:
	string currentAnimation;
	Afichmation characterAnim;

	// Sonidos (ahora tengo un soundManager porque habia demasiado codigo solo para reproducir sonidos)
	SoundManager* soundManager;

public:
	Mario(const char* path, int width, int height,
		float startX, float startY,
		int initialLives,
		const string& animationName,
		//const vector<int>& frames, // no me salió :-( https://s3.amazonaws.com/rails-camp-tutorials/blog/programming+memes/works-doesnt-work.jpg
		int fps,
		bool loop,
		SoundManager* sm)
		: currentAnimation(animationName), characterAnim(path, false, width, height), soundManager(sm)
	{
		characterAnim.Add(currentAnimation, { 0 }, fps, loop);
		characterAnim.setPosition(startX, startY);

		//// Cargar buffers de sonidos, y los sonidos mismos
		//if (!jumpBuffer.loadFromFile("../recursos_TP2/sonidos/land.wav")) {
		//	cerr << "Error al cargar el sonido" << endl;
		//}
		//jumpSound.setVolume(100);
		//jumpSound.setBuffer(jumpBuffer);

		//if (!gameOverBuffer.loadFromFile("../recursos_TP2/sonidos/game-over.wav")) {
		//	cerr << "Error al cargar el sonido" << endl;
		//}
		//gameOverSound.setVolume(100);
		//gameOverSound.setBuffer(gameOverBuffer);

		//if (!winBuffer.loadFromFile("../recursos_TP2/sonidos/win.wav")) {
		//	cerr << "Error al cargar win.wav" << endl;
		//}
		//winSound.setVolume(100);
		//winSound.setBuffer(winBuffer);
	}

	void move(int deltaX, int deltaY) {
		characterAnim.move(deltaX, deltaY);
	}

	int getX() const { return characterAnim.getPosition().x; }
	int getY() const { return characterAnim.getPosition().y; }

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

	// Salta! Con o sin flip.
	void flipAndJump(bool flip, int deltaY) {
		flipY(flip);
		setPosition(getX(), deltaY);

		// Reproducir el sonido de salto
		//jumpSound.play();\
		
		if (soundManager) soundManager->play("jump");
	}

	bool isCollidingWith(const Afichmation& other) {
		if (characterAnim.getGlobalBounds().intersects(other.getGlobalBounds())) {
			//gameOverSound.play();
			if (soundManager) soundManager->play("gameover");
			return true;
		}
		return false;
	}

	void playWinSound() {
		if (soundManager) soundManager->play("win");
	}
};
