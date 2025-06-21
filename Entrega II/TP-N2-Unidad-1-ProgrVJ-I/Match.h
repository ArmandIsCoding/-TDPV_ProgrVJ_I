#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Avatar.h"
#include "Block.h"
#include "HumanInterface.h"
#include "GameClock.h"
#include "Stage.h"

using namespace sf;
using namespace std;

// Clase principal de la escena de juego: se encarga de gestionar la l�gica general del nivel
class Match : public Stage {
	Texture backgroundTexture;				// Textura usada para mostrar el fondo del escenario
	Sprite backgroundSprite;				// Sprite que renderiza la textura del fondo

	GameClock clock;							// Cron�metro interno para medir el tiempo de juego
	Audio Colission;						// Sonido que se reproduce al chocar contra un bloque

	HumanInterface HumanInterface;			// Interfaz que muestra HUD, mensajes, etc.

	Avatar* CurrentAvatar = nullptr;		// Puntero al Player controlado por el jugador
	float GravityValue = 650.0f;			// Valor de gravedad que se aplica sobre el jugador

	Block* Blocks[10];						// Arreglo con los bloques interactuables en el escenario
	bool blockCollision = false;			// Marca si el jugador est� en contacto con alg�n bloque
	bool existCollision = false;			// Indica si se detect� alguna colisi�n en esta iteraci�n

	int Values[10];							// Arreglo con los valores num�ricos de cada bloque
	int Aux = 0;							// Variable auxiliar usada para ordenar los valores
	int TargetIndex = 0;					// �ndice del bloque correcto que el jugador debe tocar

public:
	Match();								// Constructor: inicializa todos los elementos necesarios
	~Match();								// Destructor: limpia la memoria reservada para los bloques y el jugador

	// Se ejecuta cada frame, actualiza f�sica, l�gica y estado del juego
	void Update(Engine& j) override;

	// Renderiza en pantalla todos los elementos visibles de la escena
	void Draw(RenderWindow& w) override;

	// Procesa los eventos de entrada del jugador (teclado, mouse, etc.)
	void ProcessEvents(Engine& j, Event& event) override;

	// Detecta y gestiona todas las colisiones entre el jugador y los bloques
	void PlayerBlockInteractHandler();

	// Se llama cuando el jugador golpea un bloque desde abajo
	void PlayerBlockHitHandler(Block* Block);

	// Ordena los bloques por valor para establecer cu�l es el correcto
	void SortBlocks();
};
