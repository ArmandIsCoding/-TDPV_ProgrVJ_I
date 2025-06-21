#include "Avatar.h"

Avatar::Avatar(Vector2f pos, float worldGravity)
	: GameObject("assets/personaje/super_mario.png", pos, { 62, 92 }, 1.5f), gravity(worldGravity) {

	// Cargamos las animaciones del personaje. Est�n organizadas en grupos de 8 frames.
	background.Add("idle", { 0 }, 1, false);
	background.Add("walk", { 1,2 }, 8, true);
	background.Add("run", { 1,2 }, 18, true);
	background.Add("jump", { 3 }, 1, false);
	background.Add("fall", { 4 }, 1, false);
	background.Add("land", { 4 }, 1, false);

	// Configuramos los sonidos del personaje. Algunos reutilizan el mismo archivo con tonos diferentes.
	running.Load("assets/sonidos/running.wav");
	running.SetTone(0.6f);
	walk.Load("assets/sonidos/running.wav");
	walk.SetTone(0.52f);
	jump.Load("assets/sonidos/jump.wav");
	land.Load("assets/sonidos/land.wav");
}

void Avatar::Update(float deltaTime) {
	GameObject::Update(deltaTime);  // Llamamos al update base (puede manejar animaci�n, etc.)
	Move(deltaTime);                // Procesamos el movimiento lateral del jugador
	CheckScreenBounds();            // Evitamos que se salga de la pantalla horizontalmente
	ApplyGravity(deltaTime);		// Aplicamos gravedad para simular ca�da

	// Si el personaje est� quieto y no est� en el aire, mostramos la animaci�n de idle
	if (IsIdle() && !inAir) {
		background.Play("idle");
	}
}

void Avatar::HandleEvents(Event& e) {
	// Si presionamos la tecla de salto y no estamos en el aire, realizamos el salto
	if (e.type == Event::KeyPressed && (e.key.code == jumpKey1 || e.key.code == jumpKey2) && !inAir) {
		velocityY = -jumpSpeed;
		inAir = true;
	}
}

void Avatar::Move(float deltaTime) {
	const float displacement = speed * deltaTime;
	bool runningFlag = false;
	bool walkingFlag = false;

	// Movimiento a la derecha
	if (Keyboard::isKeyPressed(rightKey)) {
		background.FlipX(false);  // Miramos a la derecha
		background.move(displacement, 0);
		if (!inAir) {
			background.Play("walk");
			walkingFlag = true;
		}
	}

	// Movimiento a la izquierda
	if (Keyboard::isKeyPressed(leftKey)) {
		background.FlipX(true);  // Miramos a la izquierda
		background.move(-displacement, 0);
		if (!inAir) {
			background.Play("walk");
			walkingFlag = true;
		}
	}

	// Correr a la derecha
	if (Keyboard::isKeyPressed(rightKey) && Keyboard::isKeyPressed(runKey)) {
		background.FlipX(false);
		background.move(displacement * 1.5f, 0);
		if (!inAir) {
			background.Play("run");
			runningFlag = true;
		}
	}

	// Correr a la izquierda
	if (Keyboard::isKeyPressed(leftKey) && Keyboard::isKeyPressed(runKey)) {
		background.FlipX(true);
		background.move(-displacement * 1.5f, 0);
		if (!inAir) {
			background.Play("run");
			runningFlag = true;
		}
	}

	// Reproducimos sonido de correr si corresponde
	if (runningFlag) {
		if (!running.Playing()) running.Play();
	}
	else {
		running.Stop();
	}

	// Reproducimos sonido de caminar (s�lo si no estamos corriendo)
	if (walkingFlag && !runningFlag) {
		if (!walk.Playing()) walk.Play();
	}
	else {
		walk.Stop();
	}
}

void Avatar::ApplyGravity(float deltaTime) {
	// Aumentamos velocidad vertical por la gravedad
	velocityY += gravity * deltaTime;

	// Movemos al personaje en el eje Y seg�n la velocidad vertical
	background.move(0, velocityY * deltaTime);

	// L�mite inferior del mundo (suelo virtual a Y=520)
	if (background.getPosition().y >= 520) {
		background.setPosition(background.getPosition().x, 520);
		velocityY = 0;
		inAir = false;
	}
}

void Avatar::Animate(float deltaTime) {
	if (inAir) {
		// Animaci�n de salto (s�lo una vez por salto)
		if (velocityY < 0 && !jumpStarted) {
			background.Play("jump");
			jumpStarted = true;
			fallStarted = false;
			jump.Play();
		}
		// Animaci�n de ca�da (cuando empezamos a caer)
		else if (velocityY > 0 && !fallStarted) {
			background.Play("fall");
			fallStarted = true;
		}
	}
	else {
		// Si aterrizamos, reproducimos la animaci�n y el sonido de aterrizaje
		if (jumpStarted || fallStarted) {
			jumpStarted = false;
			fallStarted = false;
			background.Play("land");
			land.Play();
		}
	}
}

// Verificamos si el jugador no est� presionando teclas de movimiento
inline bool Avatar::IsIdle() {
	return !(Keyboard::isKeyPressed(rightKey) || Keyboard::isKeyPressed(leftKey));
}

void Avatar::CheckScreenBounds() {
	// Obtenemos los l�mites del sprite y su posici�n
	const FloatRect bounds = background.getGlobalBounds();
	const Vector2f pos = background.getPosition();

	constexpr float leftMargin = 55.f;
	constexpr float rightMargin = 55.f;

	const float realLeft = pos.x - bounds.width / 2 + leftMargin;
	const float realRight = pos.x + bounds.width / 2 - rightMargin;

	// Correcci�n para que no se salga por la izquierda
	if (realLeft < 0) {
		background.setPosition(bounds.width / 2 - leftMargin, pos.y);
	}
	// Correcci�n para que no se salga por la derecha
	if (realRight > 800) {
		background.setPosition(800 - bounds.width / 2 + rightMargin, pos.y);
	}
}

// Devolvemos el rect�ngulo de colisi�n ajustado seg�n si est� en el aire o no
inline FloatRect Avatar::getBounds() {
	return inAir
		? adjustHitbox(background.getGlobalBounds(), 33, 45, 70, 70)
		: adjustHitbox(background.getGlobalBounds(), 43, 40, 70, 70);
}
