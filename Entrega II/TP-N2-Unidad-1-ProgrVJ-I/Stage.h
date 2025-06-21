#pragma once
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
using namespace sf;
class Engine;

// Clase abstracta base que representa una "Stage" del Game.
class Stage {
public:
	Stage() {};
	virtual void ProcessEvents(Engine& j, Event& event) {}
	virtual void Update(Engine& j) = 0;
	virtual void Draw(RenderWindow& w) = 0;
};
