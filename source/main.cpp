#include <SFML/Graphics.hpp>
#include "ui/IAUI.hpp"
#include <math.h>
#include <iostream>

int main() {
	IA::UIWindow window(sf::VideoMode(200, 200), "Fractal Viewer");
	IA::Canvas* canvas = new IA::Canvas(20, 20, 100, 100, sf::Color::Red);
	int cID = window.add_widget(canvas);
    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
        }
		canvas->texture.draw(sf::CircleShape(5));
		canvas->texture.display();
		window.render();
		sf::sleep(sf::milliseconds(10));
    }
}