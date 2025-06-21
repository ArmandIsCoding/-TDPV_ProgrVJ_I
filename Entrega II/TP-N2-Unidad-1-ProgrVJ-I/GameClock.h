#pragma once
#include <SFML/System.hpp>

using namespace sf;

// Clase para controlar el tiempo con capacidad de pausar y reanudar
class GameClock {
private:
    Clock clock;               // Reloj interno SFML para medir tiempo transcurrido
    float pausedTime = 0.f;    // Tiempo total acumulado mientras estuvo pausado (en segundos)
    bool paused = false;       // Indica si el reloj está actualmente en pausa
    Time pausedTimeAsTime;     // Momento exacto en que se pausó el reloj

public:
    // Pausa el reloj si no está pausado
    inline void Pause() {
        if (!paused) {
            paused = true;
            pausedTimeAsTime = clock.getElapsedTime();
        }
    }

    // Reanuda el reloj y acumula el tiempo que estuvo pausado
    inline void Resume() {
        if (paused) {
            Time ahora = clock.getElapsedTime();
            pausedTime += (ahora - pausedTimeAsTime).asSeconds();
            paused = false;
        }
    }

    // Devuelve el tiempo transcurrido excluyendo pausas
    inline float ElapsedTime() const {
        if (paused) {
            // Tiempo hasta que se pausó menos el tiempo acumulado de pausa
            return pausedTimeAsTime.asSeconds() - pausedTime;
        }
        else {
            // Tiempo actual menos el tiempo acumulado en pausas
            return clock.getElapsedTime().asSeconds() - pausedTime;
        }
    }

    // Reinicia el reloj y elimina todo registro de pausas previas
    inline void Restart() {
        clock.restart();
        pausedTime = 0.f;
        paused = false;
    }

    // Retorna el tiempo transcurrido excluyendo pausas y reinicia el reloj
    inline float SeeRestart() {
        float time = ElapsedTime();
        clock.restart();
        return time;
    }
};
