#include <SFML/Graphics.hpp>
#include "ui/UIWindow.hpp"
#include <math.h>
#include <stdio.h>
#include <iostream>

int main() {
	sf::RenderWindow window(sf::VideoMode(100, 100), "Fractal Viewer");
    while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
        }
    }
}