#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include "Stage.h"

using namespace sf;
using namespace std;

class Stage;

class Engine {
	RenderWindow window;
	Stage* currentScene;
	Stage* nextScene = nullptr;

public:
	Engine();
	~Engine();

	void Run();
	void Update();
	void Render();
	void HandleEvents();
	void SwitchScene(Stage* newScene);
	void Reset();
};
