#include "Block.h"

// Constructor del bloque: carga la textura, setea animaciones y configura el n�mero visible
Block::Block(Vector2f pos, int num)
    : GameObject("assets/mundo/bloque_sheet.png", pos, { 45, 45 }), originalPosition(pos)
{
    // Animaciones del fondo del bloque: "off" (apagado) y "on" (acertado)
    background.Add("off", { 1 }, 8, true);
    background.Add("on", { 0 }, 8, true);
    background.Play("off");

    // Inicializo el n�mero que se muestra encima del bloque
    numero.Init(13);  // tama�o del texto
    numero.SetGameText(std::to_string(num));
    numero.SetFillColor(Color(170, 0, 20));  // color por defecto: rojo oscuro
    numero.SetPosition(background.getPosition().x, background.getPosition().y + 5);
}

// Dibujo del bloque y su n�mero
inline void Block::Render(RenderWindow& w) {
    w.draw(background);
    numero.Draw(w);
}

// Animaci�n del bloque cuando fue marcado como correcto
void Block::Animate(float deltaTime) {
    if (!isCorrect) return;

    // Cambiar color a verde y reproducir animaci�n de "encendido"
    numero.SetFillColor(Color(50, 150, 75));
    background.Play("on");

    animTime += deltaTime;
    float progress = animTime / animDuration;
    float offsetY = 0.f;

    // Efecto de rebote hacia arriba y hacia abajo
    if (progress < 0.5f) {
        offsetY = bounceHeight * (progress / 0.5f);  // sube
    }
    else if (progress < 1.f) {
        offsetY = bounceHeight * (1.f - (progress - 0.5f) / 0.5f);  // baja
    }
    else {
        // Fin de animaci�n
        isCorrect = false;
        animTime = 0.f;
    }

    // Reubico el bloque y el n�mero con la altura animada
    Vector2f newPos = originalPosition + Vector2f(0.f, offsetY);
    background.setPosition(newPos);
    numero.SetPosition(newPos.x, newPos.y + 5);
}

// Marca este bloque como correcto (y lo recordamos para evitar repetir)
void Block::SetAsCorrect() {
    isCorrect = true;
    wasCorrect = true;
}

// Devuelve si este bloque ya fue marcado correctamente antes
bool Block::WasAlreadyCorrect() {
    return wasCorrect;
}

// Devuelve el n�mero que contiene este bloque (como int)
int Block::GetNumber() {
    return std::stoi(numero.GetString());
}

// Reposiciona el bloque y actualiza la posici�n del n�mero
void Block::SetPosition(Vector2f pos) {
    GameObject::SetPosition(pos);
    numero.SetPosition(background.getPosition().x, background.getPosition().y + 5);
}
