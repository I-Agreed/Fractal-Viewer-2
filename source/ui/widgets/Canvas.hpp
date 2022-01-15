#pragma once

#include "../IAUI.hpp"

namespace IA {
    struct Canvas: public UIWidget {
        
        sf::Color bgColour;
        sf::RenderTexture texture;

        Canvas(int x, int y, int w, int h, sf::Color _bgColour=sf::Color::White): 
        UIWidget(x, y, w, h) {
            bgColour = _bgColour;
            texture.create(w, h);
            texture.clear(bgColour);
        }

        // Draws the Canvas
        void render(sf::RenderWindow *win) {
            sf::Sprite sprite(texture.getTexture());
            sprite.move(box.p1);

            win->draw(sprite);
        }

        // Clears the Canvas's texture with its background colour
        void clear() {
            texture.clear(bgColour);
        }

        // Handles Events
        void handleEvent(UIEvent event) {
            UIWidget::handleEvent(event);

            switch (event.type) {
                case UIEventType::focusGained: {
                    bgColour = sf::Color::Blue;
                    clear();
                    break;
                } case UIEventType::focusLost: {
                    bgColour = sf::Color::White;
                    clear();
                    break;
                }
            }
        }
    };
}