#include "Engine.h"
#include "Match.h"

// Constructor: crea ventana principal y establece escena inicial
Engine::Engine() :
    window(VideoMode(800, 600), "Programación de Videojuegos I - TDPV_ProgrVJ_I", Style::Titlebar | Style::Close),
    currentScene(nullptr),
    nextScene(nullptr)
{
    window.setFramerateLimit(60);  // Limita FPS a 60
    currentScene = new Match();    // Escena inicial por defecto: Match
}

// Destructor: libera memoria de la escena actual
Engine::~Engine() {
    delete currentScene;
}

// Bucle principal del motor, ejecuta hasta que se cierre la ventana
void Engine::Run() {
    while (window.isOpen()) {
        HandleEvents();    // Procesa eventos del sistema y entrada de usuario
        window.clear();    // Limpia la pantalla para nuevo frame

        Update();          // Actualiza la lógica del juego y escenas
        Render();          // Dibuja el frame actual en pantalla

        window.display();  // Muestra el contenido dibujado en la ventana

        // Si hay una escena nueva solicitada, la cambia y elimina la vieja
        if (nextScene) {
            delete currentScene;
            currentScene = nextScene;
            nextScene = nullptr;
        }
    }
}

// Actualiza la escena actual pasando el motor para posibles interacciones
void Engine::Update() {
    if (currentScene) {
        currentScene->Update(*this);
    }
}

// Llama al método de dibujo de la escena actual pasándole la ventana
void Engine::Render() {
    if (currentScene) {
        currentScene->Draw(window);
    }
}

// Lee y procesa todos los eventos pendientes de la ventana
void Engine::HandleEvents() {
    Event event;
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close(); // Cierra ventana si se solicitó salir
        }
        else if (currentScene) {
            // Pasa los eventos a la escena para que los maneje
            currentScene->ProcessEvents(*this, event);
        }
    }
}

// Cambia la escena actual por una nueva, se aplicará en el siguiente frame
void Engine::SwitchScene(Stage* newScene) { nextScene = newScene; }

// Reinicia el motor con una nueva instancia de la escena Match
void Engine::Reset() {
    SwitchScene(new Match());
}
