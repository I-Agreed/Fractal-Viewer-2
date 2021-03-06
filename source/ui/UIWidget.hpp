#pragma once

#include <vector>
#include <SFML/Window.hpp>
#include "IAUI.hpp"

//TODO: get rect class and make widget have a bounding box
// make event system for widges
// make focus system
namespace IA {
    struct UIWidget {

        Rect<int> box;
        std::vector<UIEvent> events;

        // Empty Constructor
        UIWidget() { 
            box = Rect<int>(0, 0);
        }

        UIWidget(int x, int y, int w, int h) { 
            box = Rect<int>(x, y, x + w, y + h);
        }

        virtual void render(sf::RenderWindow *win) {} // to get overridden by inherited struct

        virtual void handle_event(UIEvent event) {} // to get overridden by inherited struct
    };
}