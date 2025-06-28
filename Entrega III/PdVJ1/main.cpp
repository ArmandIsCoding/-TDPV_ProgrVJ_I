#include <SFML/Graphics.hpp>
#include "Afichmation.h"
#include "Mario.h"
#include "Shell.h"

using namespace sf;

int main(int argc, char* argv[]) {
	RenderWindow* w = new RenderWindow(VideoMode(800, 600), "Unidad 2 - Plan de Trabajo 4");
	w->setFramerateLimit(60);

	// Los niveles (alturas en el eje Y de abajo hacia arriba, mayor a menor).
	float groundLevels[] = { 495, 420, 345, 270, 195, 120, 40 };
	const int totalNiveles = sizeof(groundLevels) / sizeof(float);
	int currentLevel = 0;
	int turnoEnemigo[7] = { 0 }; // Índice del enemigo activo por piso

	// Cargar la imagen de fondo
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("../recursos_TP2/fondo_plataformas.png")) {
		return -1;
	}

	Sprite background(backgroundTexture);

	// Personaje principal (Mario)
	Mario mario("../recursos_TP2/jumper.png", 46, 60, 200.f, groundLevels[currentLevel], /* Una forma copada de decir 0 pero con mas palabras.*/	5, "idle", 1, false);

	// Enemigos
	// Por defecto todos los enemigos son nullptr.... CREO. C# me malacostumbró a que los arrays se inicializan solos. Todo es mágico en C#, no hay inseguridad, tampoco inflación. Las plantitas no se secan. Lo extraño.
	Shell* enemigos[7][4] = {};

	const char* shellSprites[4] = {
		"../recursos_TP2/shell_amarillo.png",
		"../recursos_TP2/shell_azul.png",
		"../recursos_TP2/shell_rojo.png",
		"../recursos_TP2/shell_verde.png"
	};

	for (int piso = 1; piso < 7; ++piso) { // El piso 0 no tiene enemigos, por eso empiezo en 1
		for (int i = 0; i < 4; ++i) {
			// Solo el primero por piso activo por ahora
			if (i == 0) {
				const char* spritePath = shellSprites[piso % 4]; // Para ir variando
				enemigos[piso][i] = new Shell(spritePath, 30, 24, 200.f, groundLevels[piso], "idle", 2, true);
				enemigos[piso][i]->playAnimation("idle");
			}
			else {
				enemigos[piso][i] = nullptr;
			}
		}
	}

	while (w->isOpen()) {
		Event e;

		while (w->pollEvent(e)) {
			if (e.type == Event::Closed) { w->close(); }

			// Mario:
			// Detecto el salto solo UNA VEZ por tecla presionada
			if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
				if (currentLevel + 1 < totalNiveles) { // Sin esto nos vamos del array. Todo explota.
					currentLevel++;
					mario.flipAndJump(false, groundLevels[currentLevel]);
				}
			}
		}

		// Movimiento horizontal continuo
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			mario.flipAndMoveX(false, -8);
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			mario.flipAndMoveX(true, 8);
		}

		w->clear(Color(255, 255, 255, 255));
		w->draw(background);

		mario.playAnimation("idle");
		mario.update();
		mario.draw(w);

		// Enemigos:

		for (int piso = 1; piso < 7; ++piso) {
			int turno = turnoEnemigo[piso];
			Shell* enemigo = enemigos[piso][turno];

			if (enemigo != nullptr) {
				float x = enemigo->getX();

				// Movimiento ida y vuelta entre dos extremos
				static bool movingRight[7] = { true }; // Dirección por piso
				if (movingRight[piso]) {
					enemigo->flipAndMoveX(true, 2);
					if (x > 700) movingRight[piso] = false;
				}
				else {
					enemigo->flipAndMoveX(false, -2);
					if (x < 100) movingRight[piso] = true;
				}

				// En un futuro: cuando termine su "recorrido", avanzar al siguiente enemigo
				// turnoEnemigo[piso] = (turnoEnemigo[piso] + 1) % 4;
			}
		}


		for (int piso = 0; piso < 7; ++piso) {
			for (int i = 0; i < 4; ++i) {
				if (enemigos[piso][i] != nullptr) {
					enemigos[piso][i]->update();
					enemigos[piso][i]->draw(w);
				}
			}
		}

		w->display();

	}

	return 0;
}
