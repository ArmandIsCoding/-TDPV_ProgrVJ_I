#include "Match.h"
#include <cstdlib>  // para std::rand
#include <algorithm> // para std::swap

Match::Match() {
    // Carga la textura y configura el sprite de fondo del escenario
    backgroundTexture.loadFromFile("assets/mundo/mundo_fondo.png");
    backgroundSprite.setTexture(backgroundTexture);

    // Carga el sonido de colisión desde archivo
    Colission.Load("assets/sonidos/punch.wav");

    // Crea el avatar del jugador con posición inicial y gravedad
    CurrentAvatar = new Avatar({ 400, 520 }, GravityValue);

    // Genera 10 bloques con valores aleatorios únicos entre 1 y 999
    for (int i = 0; i < 10; ++i) {
        Values[i] = std::rand() % 999 + 1;
        Vector2f pos(35.f + i * 80.f, 400.f);  // Distribución horizontal fija
        Blocks[i] = new Block(pos, Values[i]);
    }

    // Ordenamiento burbuja para ordenar los valores objetivo de menor a mayor
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9 - i; ++j) {
            if (Values[j] > Values[j + 1]) {
                std::swap(Values[j], Values[j + 1]);
            }
        }
    }
}

Match::~Match() {
    // Liberar memoria de avatar y bloques
    delete CurrentAvatar;
    for (auto& block : Blocks) {
        delete block;
    }
}

void Match::Update(Engine& engine) {
    // Obtiene el delta time desde el reloj interno
    float dt = clock.SeeRestart();

    // Actualiza la interfaz humana y el texto del juego
    HumanInterface.Update(dt);
    HumanInterface.UpdateGameText();

    // Actualiza la lógica solo si el juego no terminó y quedan objetivos
    if (!HumanInterface.Over() && TargetIndex < 10) {
        CurrentAvatar->Update(dt);
        PlayerBlockInteractHandler();
    }

    // Actualiza cada bloque
    for (auto& block : Blocks) {
        block->Update(dt);
    }

    // Si el juego terminó o se alcanzaron todos los objetivos, ordena los bloques visualmente
    if (HumanInterface.Over() || TargetIndex == 10) {
        SortBlocks();
    }
}

void Match::Draw(RenderWindow& window) {
    // Dibuja el fondo, la interfaz, el avatar y los bloques
    window.draw(backgroundSprite);
    HumanInterface.Draw(window);
    CurrentAvatar->Render(window);
    for (auto& block : Blocks) {
        block->Render(window);
    }
}

void Match::ProcessEvents(Engine& engine, Event& event) {
    // Permite que el avatar maneje eventos (input)
    CurrentAvatar->HandleEvents(event);

    // Permite reiniciar el juego presionando la tecla R cuando terminó o ganó
    if (event.type == Event::KeyPressed && event.key.code == Keyboard::R &&
        (HumanInterface.Over() || TargetIndex == 10)) {
        engine.Reset();
    }
}

void Match::PlayerBlockInteractHandler() {
    existCollision = false;

    for (auto& block : Blocks) {
        // Verifica colisión entre avatar y bloque
        if (CurrentAvatar->getBounds().intersects(block->getBounds())) {
            existCollision = true;
            Colission.Play();  // Reproduce sonido de colisión
            PlayerBlockHitHandler(block);

            // Si el bloque ya fue marcado como correcto, no hacer nada más
            if (block->WasAlreadyCorrect()) break;

            // Si no había colisión previa en frame y quedan objetivos
            if (!blockCollision && TargetIndex < 10) {
                if (block->GetNumber() == Values[TargetIndex]) {
                    block->SetAsCorrect();
                    if (++TargetIndex == 10) {
                        HumanInterface.Won();
                        SortBlocks();
                    }
                }
                else {
                    HumanInterface.Wrong();
                }
            }
            break;  // Procesa sólo una colisión por frame
        }
    }

    blockCollision = existCollision;
}

void Match::PlayerBlockHitHandler(Block* block) {
    const FloatRect jugador = CurrentAvatar->getBounds();
    const FloatRect obstaculo = block->getBounds();

    // Detecta si el avatar impacta el bloque desde abajo (salto)
    if (CurrentAvatar->GetVelocityY() < 0 &&
        jugador.top > obstaculo.top + obstaculo.height - 10) {
        // Detiene la velocidad vertical y ajusta la posición del avatar para no atravesar el bloque
        CurrentAvatar->SetVelocityY(0);
        CurrentAvatar->SetPosition({
            CurrentAvatar->getPosition().x,
            obstaculo.top + obstaculo.height + jugador.height / 2
            });
    }
}

void Match::SortBlocks() {
    // Reorganiza visualmente los bloques en pantalla según el orden numérico
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (Blocks[j]->GetNumber() == Values[i]) {
                Blocks[j]->SetPosition({ 35.f + i * 80.f, 400.f });
                break;
            }
        }
    }
}
