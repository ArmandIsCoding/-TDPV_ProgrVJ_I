#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameText.h"
#include "Audio.h"

using namespace sf;
using namespace std;

// Clase encargada de mostrar la interfaz visual del juego (HUD, mensajes, sonidos de estado, etc.)
class HumanInterface {
	// Textura con los controles del juego (WASD, mouse, etc.)
	Texture controlsTexture;
	Sprite controlsSprite; // Sprite que muestra la imagen de controles

	// Textos en pantalla: uno para mostrar el tiempo o estado, otro para mostrar el mensaje de reinicio
	GameText gameText, restartText;

	// Sonidos del sistema: tic-tac del reloj, reinicio parpadeando, victoria y derrota
	Audio clock, restart, win, over;

	// Tiempo que le queda al jugador antes de que termine la Match
	float remainingTime = 60.f;

	// Indica si la Match ya terminó (por tiempo o por haber ganado)
	bool done = false;

	// Indica si el jugador ganó (true) o perdió (false)
	bool won = false;

	// Temporizador interno para manejar el parpadeo del mensaje de reinicio
	float flickrTime = 0.f;

	// Flag para alternar la visibilidad del mensaje de reinicio cada cierto tiempo
	bool showRestart = false;

	// Almacena el último estado de visibilidad para saber si se debe redibujar
	bool showPreviousRestart = true;

	// Cuenta cuánto tiempo pasó desde que terminó la Match (útil para los sonidos o efectos)
	float elapsed = 0.f;

	// Bandera para evitar reproducir múltiples veces los sonidos de fin de Match
	bool conditionSound = false;

public:
	// Constructor: prepara todos los textos, sonidos y sprites necesarios
	HumanInterface();

	// Se llama una vez por frame: actualiza todo lo relacionado a la interfaz (tiempo, sonidos, animaciones)
	void Update(float deltaTime);

	// Dibuja en pantalla los textos y controles
	void Draw(RenderWindow& w);

	// Refresca el contenido del texto principal (por ejemplo, el tiempo restante)
	void UpdateGameText();

	// Resta tiempo cuando el jugador comete un error (penalización)
	void Wrong();

	// Se llama cuando el jugador gana (cambia estados y prepara sonido de victoria)
	void Won();

	// Devuelve true si ya se acabó el tiempo (o la Match terminó por ganar o perder)
	bool Over();
};
