#pragma once
#include <SFML/Audio.hpp>
#include <string>

// Clase que encapsula el manejo de efectos de sonido.
// Permite cargar, reproducir, detener y configurar sonidos fácilmente.

class Audio {
private:
    sf::SoundBuffer buffer;  // Almacena los datos de audio cargados desde archivo
    sf::Sound sound;         // Se encarga de reproducir el sonido en tiempo de ejecución

public:
    Audio() = default;

    // Carga un archivo de sonido desde la ruta especificada
    void Load(const std::string& rutaArchivo) {
        buffer.loadFromFile(rutaArchivo);
        sound.setBuffer(buffer);
    }

    // Reproduce el sonido cargado desde el principio
    void Play() {
        sound.play();
    }

    // Detiene la reproducción del sonido si está en curso
    void Stop() {
        sound.stop();
    }

    // Devuelve true si el sonido está actualmente reproduciéndose
    bool Playing() const {
        return sound.getStatus() == sf::Sound::Playing;
    }

    // Configura si el sonido debe repetirse automáticamente al finalizar
    void SetLoop(bool loop) {
        sound.setLoop(loop);
    }

    // Ajusta el tono (pitch) del sonido
    void SetTone(float pitch) {
        sound.setPitch(pitch);
    }

    // Define el volumen de reproducción del sonido
    void SetVolume(float volumen) {
        sound.setVolume(volumen);
    }
};
