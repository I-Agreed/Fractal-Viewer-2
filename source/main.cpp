#include <SFML/Graphics.hpp>
#include "ui/IAUI.hpp"
#include "fractals/Fractals.hpp"
#include <math.h>
#include <iostream>

int main() {
	IA::UIWindow window(sf::VideoMode(200, 200), "Fractal Viewer");
	FractalDisplay* canvas = new FractalDisplay(0, 0, 200, 200);
	int cID = window.add_widget(canvas);
    while (window.isOpen()) {
		IA::UIEvent event;
		while (window.poll_UIEvent(event)) {
			if (event.SFMLEvent.type == sf::Event::Closed) window.close();
        }
		canvas->clear();
		sf::CircleShape circle = sf::CircleShape(canvas->number_units_to_pixels(5));
		circle.move(canvas->number_pos_to_pixel_pos(IA::Vector2<int>(0, 0)));
		circle.setFillColor(sf::Color::Red);
		canvas->texture.draw(circle);
		canvas->texture.display();
		window.render();
		sf::sleep(sf::milliseconds(10));
    }

	return 0;
}