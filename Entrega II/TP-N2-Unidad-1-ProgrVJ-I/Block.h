#pragma once
#include "Afichmation.h"
#include <SFML/Graphics.hpp>
#include "GameText.h"
#include "GameObject.h"

using namespace sf;

class Block : public GameObject {
private:
    GameText numero;  // Representa el n�mero que se muestra dentro del Block

    // Variables para la animaci�n de rebote del Block
    bool isCorrect = false;          // Indica si se seleccion� el n�mero correcto
    bool wasCorrect = false;         // Verifica si ya fue seleccionado previamente
    float animTime = 0.f;            // Tiempo transcurrido desde el inicio de la animaci�n
    float animDuration = 0.4f;       // Tiempo total que dura la animaci�n
    float bounceHeight = -10.f;      // Altura m�xima del rebote
    Vector2f originalPosition;       // Posici�n de referencia original

public:
    Block(Vector2f pos, int num);

    void Render(RenderWindow& w) override;
    void Animate(float deltaTime) override;
    void SetPosition(Vector2f pos) override;
    void SetAsCorrect();
    bool WasAlreadyCorrect();
    int GetNumber();
};
