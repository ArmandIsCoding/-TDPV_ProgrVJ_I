#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class GameText {
private:
    Text text;
    Font font;

public:
    GameText() = default;

    void Init(int size) {
        font.loadFromFile("assets/fonts/StalinistOne-Regular.ttf");
        text.setFont(font);
        text.setCharacterSize(size);
        text.setFillColor(Color(26, 25, 50));
    }

    void SetCharSize(int size) {
        text.setCharacterSize(size);
    }

    void SetGameText(const string& str) {
        text.setString(str);
        FloatRect bounds = text.getGlobalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);
    }

    void SetPosition(float x, float y) {
        text.setPosition(x, y);
    }

    void SetFillColor(Color color) {
        text.setFillColor(color);
    }

    Vector2f GetPosition() const {
        return text.getPosition();
    }

    Text& GetGameText() {
        return text;
    }

    string GetString() const {
        return text.getString().toAnsiString();
    }

    void Draw(RenderWindow& window) {
        window.draw(text);
    }
};
