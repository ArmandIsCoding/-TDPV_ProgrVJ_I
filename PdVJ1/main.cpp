#include <SFML/Graphics.hpp>
#include "Afichmation.h"

using namespace sf;

int main(int argc, char* argv[]) {
    RenderWindow* w = new RenderWindow(VideoMode(640, 480), "Unidad 1 - Plan de Trabajo 2");
    w->setFramerateLimit(60);
    float groundLevel = 340.f;

    // Cargar la imagen de fondo
    Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        return -1; // Manejo de error si la imagen no se carga
    }
    Sprite background(backgroundTexture);

    Afichmation anim("assets/spritesheet.png", true, 26, 30);
    anim.Add("idle", { 0, 1, 2, 1, 0 }, 8, false);
    anim.Add("run", { 3, 4, 5, 4 }, 8, true);
    anim.Add("jump", { 6 }, 8, false);

    // Empieza en idle
    anim.Play("idle");

    // Un poquito mas grande
    anim.setScale(Vector2f(3.f, 3.f));

    // Posición inicial en el "piso" del escenario
    anim.setPosition(200.f, groundLevel);

    float velocityY = 0.f;
    bool isJumping = false;
    const float gravity = 0.5f;
    const float jumpStrength = -10.f;
    const float groundY = groundLevel;

    while (w->isOpen()) {
        Event e;
        while (w->pollEvent(e)) {
            if (e.type == Event::Closed)
                w->close();

            if (e.type == Event::KeyPressed) {
                if (e.key.code == Keyboard::A) {
                    anim.Play("run");
                    anim.FlipX(true);
                    anim.move(-8, 0);
                }
                if (e.key.code == Keyboard::D) {
                    anim.Play("run");
                    anim.FlipX(false);
                    anim.move(8, 0);
                }

                // Se salta con espacio, si le saco && !isJumping se pueden combinar los saltos
                if (e.key.code == Keyboard::Space && !isJumping) { 
                    anim.Play("jump");
                    velocityY = jumpStrength;
                    isJumping = true;
                }
            }

            if (e.type == Event::KeyReleased) {
                if (e.key.code == Keyboard::A || e.key.code == Keyboard::D) { // Si se solto la barra espaciadora lo ignoro
                    anim.Play("idle");
                }
            }
        }

        // Aplicar gravedad
        if (isJumping) {
            velocityY += gravity; // Aumenta la velocidad en Y con la gravedad. Sube para abajo el valor.
            anim.move(0, velocityY);

            // Si el personaje vuelve al suelo, listo
            if (anim.getPosition().y >= groundY) {
                anim.setPosition(anim.getPosition().x, groundY);
                isJumping = false;
                velocityY = 0.f;
                anim.Play("idle");
            }
        }

        anim.Update();
        w->clear(Color(255, 255, 255, 255));
        w->draw(background);
        w->draw(anim);
        w->display();
    }

    return 0;
}