#include <SFML/Graphics.hpp>
#include "Afichmation.h"
#include "Mario.h"
#include "Shell.h"
#include <sstream> // para std::stringstream, por el contador de tiempo
#include <SFML/Audio.hpp>
#include "SoundManager.h"

using namespace sf;

int main(int argc, char* argv[]) {
	RenderWindow* w = new RenderWindow(VideoMode(800, 600), "Unidad 2 - Plan de Trabajo 4");
	w->setFramerateLimit(60);

	SoundManager soundManager;
	soundManager.loadSound("tictac", "../recursos_TP2/sonidos/tic-tac.wav");
	soundManager.loadSound("jump", "../recursos_TP2/sonidos/land.wav");
	soundManager.loadSound("gameover", "../recursos_TP2/sonidos/game-over.wav");
	soundManager.loadSound("win", "../recursos_TP2/sonidos/win.wav");

	soundManager.play("tictac", true); // Reproducir sonido de fondo en loop

	// Contador de tiempo
	sf::Font font;
	if (!font.loadFromFile("../recursos_TP2/StalinistOne-Regular.ttf")) {
		return -1;
	}

	sf::Text timerText;
	timerText.setFont(font);
	timerText.setCharacterSize(24);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(10.f, 10.f); // Arriba, izquierda

	sf::Clock gameClock;
	const float totalGameTime = 30.f; // en segundos

	// Otros labels
	sf::Text instructionsText;
	instructionsText.setFont(font);
	instructionsText.setCharacterSize(22);
	instructionsText.setFillColor(sf::Color::Red);
	instructionsText.setStyle(sf::Text::Bold);
	instructionsText.setString("Mover: A, D. Saltar/Reiniciar: Espacio");
	instructionsText.setPosition(25.f, 550.f);
	
	bool gameOver = false;
	sf::Text gameOverText;
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(36);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setStyle(sf::Text::Bold);
	gameOverText.setString("GAME OVER");
	gameOverText.setPosition(250.f, 250.f);

	sf::Text restartText;
	restartText.setFont(font);
	restartText.setCharacterSize(20);
	restartText.setFillColor(sf::Color::White);
	restartText.setString("Presiona ESPACIO para reiniciar");
	restartText.setPosition(130.f, 300.f);

	// Los niveles (alturas en el eje Y de abajo hacia arriba, mayor a menor).
	float groundLevels[] = { 495, 420, 345, 270, 195, 120, 40 };
	const int totalNiveles = sizeof(groundLevels) / sizeof(float);
	int currentLevel = 0;
	int turnoEnemigo[7] = { 0 }; // Índice del enemigo activo por piso
	bool usaCola[7] = { false, true, false, true, false, true, false };
	float velocidad = 5.0f; // Velocidad de los enemigos

	// Cargar la imagen de fondo
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("../recursos_TP2/fondo_plataformas.png")) {
		return -1;
	}
	Sprite background(backgroundTexture);

	// Personaje principal (Mario)
	Mario mario("../recursos_TP2/jumper.png", 46, 60, 200.f, groundLevels[currentLevel], /* Una forma copada de decir 0 pero con mas palabras.*/	5, "idle", 1, false, &soundManager);

	// Puertita
	Afichmation puerta("../recursos_TP2/puerta.png", false, 29, 48);
	puerta.Add("idle", { 0 }, 1, true); // Animación de un solo frame, deberia haber usado sprite... pero ya hice las colisiones entre afichmations
	puerta.Play("idle");

	// Posición aleatoria en X dentro del rango visible (ajustá si querés que esté centrada)
	float puertaX = static_cast<float>(100 + rand() % 600);
	puerta.setPosition(puertaX, groundLevels[6]);

	// Enemigos
	// Por defecto todos los enemigos son nullptr.... CREO...?
	// C# me malacostumbró a que los arrays se inicializan solos.
	// Todo es mágico en C#, no hay inseguridad, tampoco inflación. Las plantitas no se secan. El gato viene cuando lo llamo.
	// Todo es más fácil. En fin, a lo que iba, los enemigos son punteros a Shell, y por defecto son nullptr.
	Shell* enemigos[7][4] = {};

	const char* shellSprites[4] = {
		"../recursos_TP2/shell_amarillo.png",
		"../recursos_TP2/shell_azul.png",
		"../recursos_TP2/shell_rojo.png",
		"../recursos_TP2/shell_verde.png"
	};

	// Crear enemigos en todos los pisos
	for (int piso = 1; piso < 7; ++piso) {
		for (int i = 0; i < 4; ++i) {
			const char* spritePath = shellSprites[(piso + i) % 4];
			float posX = 100.f;// +i * 100; // distribuidos horizontalmente
			enemigos[piso][i] = new Shell(spritePath, 30, 24, posX, groundLevels[piso], "idle", 2, true);
			enemigos[piso][i]->playAnimation("idle");
		}
	}

	while (w->isOpen()) {
		// Tiempo
		// Calcular tiempo restante
		float elapsed = gameClock.getElapsedTime().asSeconds();
		float remaining = totalGameTime - elapsed;

		if (remaining <= 0.f && !gameOver) { // Se intentó, se perdió.
			remaining = 0.f;
			gameOver = true;
			//backgroundTicTac.pause();
		}

		// Mostrar el tiempo en pantalla
		std::stringstream ss;
		ss << "Tiempo restante: " << static_cast<int>(remaining);
		timerText.setString(ss.str());


		Event e;
		while (w->pollEvent(e)) {

			// Reiniciar el juego con la bara espaciadora
			if (gameOver) {
				if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
					// Reiniciar variables
					currentLevel = 0;
					mario.setPosition(200.f, groundLevels[currentLevel]);
					gameClock.restart();
					gameOver = false;

					// reubicar la puerta
					puertaX = static_cast<float>(100 + rand() % 600);
					puerta.setPosition(puertaX, groundLevels[6]);

					gameOverText.setString("GAME OVER"); // Reset texto porque es el mismo que usé para poner GANASTE
				}
				else {
					if (currentLevel + 1 < totalNiveles) {
						currentLevel++;
						mario.flipAndJump(false, groundLevels[currentLevel]);
					}
				}
			}

			if (currentLevel == 6 && mario.isCollidingWith(puerta)) {
				gameOver = true;
				mario.playWinSound();
				gameOverText.setString("¡GANASTE!");
			}

			if (!gameOver)
			{
				if (e.type == Event::Closed) { w->close(); }

				// Mario:
				// Detecto el salto solo UNA VEZ por tecla presionada
				if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
					if (currentLevel + 1 < totalNiveles) { // Sin esto nos vamos del array. Todo explota.
						currentLevel++;
						mario.flipAndJump(false, groundLevels[currentLevel]);
					}
				}

				// Movimiento horizontal continuo
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					mario.flipAndMoveX(false, -8);
				}
				if (Keyboard::isKeyPressed(Keyboard::D)) {
					mario.flipAndMoveX(true, 8);
				}
			}
		}

		w->clear(Color(255, 255, 255, 255));
		w->draw(background);
		w->draw(puerta);

		mario.playAnimation("idle");
		mario.update();
		mario.draw(w);

		// Enemigos:
		if (!gameOver) {
			static bool movingRight[7][4]; // Dirección individual por enemigo

			for (int piso = 1; piso < 7; ++piso) {
				int turno = turnoEnemigo[piso];
				Shell* enemigo = enemigos[piso][turno];

				if (enemigo != nullptr) {
					float x = enemigo->getX();

					// Movimiento del enemigo actual
					if (movingRight[piso][turno]) {
						enemigo->flipAndMoveX(true, velocidad);
						if (x >= 700) movingRight[piso][turno] = false;
					}
					else {
						enemigo->flipAndMoveX(false, -velocidad);
						if (x <= 100) movingRight[piso][turno] = true;
					}

					// Si llegó al borde, rotar
					if (x <= 100 || x >= 700) {
						Shell* terminado = enemigo;
						bool dir = movingRight[piso][turno];

						if (usaCola[piso]) {
							// FIFO (cola)
							for (int i = 0; i < 3; ++i) {
								enemigos[piso][i] = enemigos[piso][i + 1];
								movingRight[piso][i] = movingRight[piso][i + 1];
							}
							enemigos[piso][3] = terminado;
							movingRight[piso][3] = dir;
						}
						else {
							// LIFO (pila)
							for (int i = 3; i > 0; --i) {
								enemigos[piso][i] = enemigos[piso][i - 1];
								movingRight[piso][i] = movingRight[piso][i - 1];
							}
							enemigos[piso][0] = terminado;
							movingRight[piso][0] = dir;
						}

						turnoEnemigo[piso] = 0;
					}
				}
			}

			// Verificar colisión entre Mario y el enemigo activo en su piso actual
			if (currentLevel >= 1 && currentLevel < 7) {
				Shell* enemigoActual = enemigos[currentLevel][turnoEnemigo[currentLevel]];
				if (enemigoActual != nullptr) {
					if (mario.isCollidingWith(enemigoActual->GetCharacterAnim())) {
						// Resetear al piso 0
						currentLevel = 0;
						mario.flipAndJump(false, groundLevels[0]);
					}
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

			w->draw(timerText);
		}
		if (gameOver) {
			w->draw(gameOverText);
			w->draw(restartText);
		}

		w->draw(instructionsText);
		w->display();

	}

	return 0;
}
