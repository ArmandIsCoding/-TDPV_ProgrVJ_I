#include "HumanInterface.h"

HumanInterface::HumanInterface() {
    // Cargar textura y sprite de controles
    controlsTexture.loadFromFile("assets/controles/teclas.png");
    controlsSprite.setTexture(controlsTexture);
    controlsSprite.setPosition(600, 10);

    // Configurar texto principal del juego
    gameText.Init(20);
    gameText.SetPosition(100, 30);
    gameText.SetFillColor(Color::Black);

    // Configurar texto de reinicio
    restartText.Init(18);
    restartText.SetPosition(700, 300);
    restartText.SetGameText("R para reiniciar");

    // Cargar y configurar sonidos
    clock.Load("assets/sonidos/tic-tac.wav");
    clock.SetTone(0.28f);
    clock.SetVolume(80);

    win.Load("assets/sonidos/win.wav");
    win.SetVolume(60);

    over.Load("assets/sonidos/game-over.wav");
    over.SetVolume(60);

    restart.Load("assets/sonidos/button-R.wav");
    restart.SetVolume(40);

    // Inicializar estados
    done = false;
    won = false;
    conditionSound = false;
    showRestart = true;
    showPreviousRestart = false;
    elapsed = 0.f;
    flickrTime = 0.f;
    remainingTime = 60.f;  // Por ejemplo, tiempo inicial del juego
}

void HumanInterface::Update(float deltaTime) {
    // Si el juego está activo y el reloj no suena, reproducirlo
    if (!clock.Playing() && !done && !won) { clock.Play(); }

    // Si el juego terminó o se ganó, manejar lógica final
    if (done || won) {
        clock.Stop();  // Detener sonido de reloj

        // Reproducir sonido correspondiente sólo una vez
        if (!conditionSound) {
            if (done) over.Play();
            if (won) win.Play();
            conditionSound = true;
        }

        // Controlar parpadeo del texto de reinicio luego de 2 segundos
        elapsed += deltaTime;
        if (elapsed >= 2.f) {
            flickrTime += deltaTime;

            if (flickrTime >= 0.5f) {
                showPreviousRestart = showRestart;
                showRestart = !showRestart;
                flickrTime = 0.f;

                // Reproducir sonido al aparecer el texto
                if (!showPreviousRestart && showRestart) {
                    restart.Play();
                }
            }
        }

        return;  // No hacer más actualizaciones si terminó el juego
    }

    // Reducir tiempo restante mientras el juego sigue activo
    remainingTime -= deltaTime;

    // Verificar si se acabó el tiempo
    if (remainingTime <= 0.f) {
        remainingTime = 0.f;
        done = true;
    }
}

void HumanInterface::Draw(RenderWindow& w) {
    // Mostrar controles solo si el juego no terminó ni se ganó
    if (!done && !won) {
        w.draw(controlsSprite);
    }

    // Dibujar texto principal con el estado actual
    gameText.Draw(w);

    // Mostrar mensaje de reinicio si corresponde y está visible
    if ((done || won) && showRestart) {
        restartText.Draw(w);
    }
}

void HumanInterface::UpdateGameText() {
    // Actualiza el texto principal según estado del juego

    if (won) {
        gameText.SetFillColor(Color(0, 173, 17));  // Verde para victoria
        gameText.SetPosition(400, 200);
        gameText.SetCharSize(60);
        gameText.SetGameText("GANASTE!");
    }
    else if (done) {
        gameText.SetFillColor(Color(170, 0, 20));  // Rojo para derrota
        gameText.SetPosition(400, 200);
        gameText.SetCharSize(60);
        gameText.SetGameText("Ups");
    }
    else {
        // Mostrar tiempo restante mientras se juega
        gameText.SetFillColor(Color::Black);
        gameText.SetPosition(100, 30);
        gameText.SetCharSize(20);
        gameText.SetGameText("Tiempo: " + to_string(static_cast<int>(remainingTime)));
    }
}

void HumanInterface::Wrong() {
    // Penaliza quitando 10 segundos si el juego sigue activo
    if (!done) {
        remainingTime -= 10.f;
        if (remainingTime < 0.f) remainingTime = 0.f;
    }
}

void HumanInterface::Won() {
    // Marca el juego como ganado
    won = true;
}

bool HumanInterface::Over() {
    // Indica si el juego terminó
    return done;
}
