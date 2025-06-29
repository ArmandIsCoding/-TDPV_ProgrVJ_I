#pragma once
#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>
#include <iostream>

class SoundManager {
private:
    std::unordered_map<std::string, sf::SoundBuffer> buffers;
    std::unordered_map<std::string, sf::Sound> sounds;

public:
    // Carga un sonido desde un archivo y lo registra con un nombre
    void loadSound(const std::string& name, const std::string& path) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(path)) {
            std::cerr << "Error al cargar el sonido: " << path << std::endl;
            return;
        }

        buffers[name] = buffer;

        sf::Sound sound;
        sound.setBuffer(buffers[name]);
        sound.setVolume(100); // volumen por defecto
        sounds[name] = sound;
    }

    // Reproduce un sonido por su nombre
    void play(const std::string& name, bool loop = false) {
        auto it = sounds.find(name);
        if (it != sounds.end()) {
            it->second.setLoop(loop);
            it->second.play();
        }
        else {
            std::cerr << "Sonido no encontrado: " << name << std::endl;
        }
    }

    // Permite cambiar el volumen individualmente
    void setVolume(const std::string& name, float volume) {
        if (sounds.count(name)) {
            sounds[name].setVolume(volume);
        }
    }
};
