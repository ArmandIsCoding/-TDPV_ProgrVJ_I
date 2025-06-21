#include <SFML/Graphics.hpp>
#include "Afichmation.h"

using namespace sf;

int main(int argc, char* argv[]) {
	RenderWindow* w = new RenderWindow(VideoMode(800, 600), "Unidad 1 - Plan de Trabajo 2");
	w->setFramerateLimit(60);

	float groundLevels[] = { 495, 420, 345, 270, 195, 120, 40 };
	const int totalNiveles = sizeof(groundLevels) / sizeof(float);
	int nivelActual = 0;

	// Cargar la imagen de fondo
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("../recursos_TP2/fondo_plataformas.png")) {
		return -1;
	}

	Sprite background(backgroundTexture);

	Afichmation characterAnim("../recursos_TP2/jumper.png", false, 46, 60);
	characterAnim.Add("idle", { 0 }, 1, false);
	characterAnim.setPosition(200.f, groundLevels[nivelActual]);

	while (w->isOpen()) {
		Event e;
		while (w->pollEvent(e)) {
			if (e.type == Event::Closed)
				w->close();

			// Aquí detectás el salto solo UNA VEZ por tecla presionada
			if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space) {
				if (nivelActual + 1 < totalNiveles) {
					nivelActual++;
					characterAnim.setPosition(characterAnim.getPosition().x, groundLevels[nivelActual]);
				}
			}
		}

		// Movimiento horizontal continuo
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			characterAnim.FlipX(false);
			characterAnim.move(-8, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			characterAnim.FlipX(true);
			characterAnim.move(8, 0);
		}

		w->clear(Color(255, 255, 255, 255));
		characterAnim.Play("idle");
		characterAnim.Update();
		w->draw(background);
		w->draw(characterAnim);
		w->display();
	}

	return 0;
}
