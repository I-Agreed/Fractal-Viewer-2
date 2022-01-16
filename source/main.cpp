#include <SFML/Graphics.hpp>
#include "ui/IAUI.hpp"
#include "fractals/Fractals.hpp"
#include <math.h>
#include <iostream>

int main() {
	load_shaders();

	IA::UIWindow window(sf::VideoMode(400, 300), "Fractal Viewer");
	FractalDisplay* canvas = new FractalDisplay(00, 00, 400, 300);
	int cID = window.add_widget(canvas);
    while (window.isOpen()) {
		IA::UIEvent event;
		while (window.poll_UIEvent(event)) {
			if (event.SFMLEvent.type == sf::Event::Closed) window.close();
        }
		canvas->clear();
		generate_fractal(&(canvas->texture), canvas->cameraPos, canvas->zoom, Fractals::Mandelbrot);
		canvas->texture.display();
		window.render();
		sf::sleep(sf::milliseconds(10));
    }

	return 0;
}