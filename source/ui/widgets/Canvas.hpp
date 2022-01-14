#pragma once

#include "../IAUI.hpp"

namespace IA {
    class Canvas: public UIWidget {
        
        sf::Color bgColour;

        Canvas(int x, int y, int w, int h, sf::Color _bgColour=sf::Color::White): 
        UIWidget(x, y, w, h) {
            bgColour = _bgColour;
        }

        // Draws the Canvas
        void render(UIWindow *win) {
            sf::RectangleShape bg(box.p2 - box.p1);
            bg.move(box.p1);
            bg.setFillColor(bgColour);

            win->draw(bg);
        }
    };
}