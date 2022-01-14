#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "IAUI.hpp"

namespace IA {
    struct UIWindow: public sf::RenderWindow {

        std::vector<UIWidget> Widgets;
        int focus = -1; // ID of Widget that has focus, -1 for none. Focus is gained by clicking on a widget

        // Constructor (the same params as sfml window constructor)
        UIWindow(sf::VideoMode mode, const sf::String &title, sf::Uint32 style=sf::Style::Default, 
                 const sf::ContextSettings &settings = sf::ContextSettings()):
                 sf::RenderWindow(mode, title, style, settings) {

        }

        // Adds a widget to the window, returns the widget's ID
        int add_widget(UIWidget w) {
            Widgets.push_back(w);
            return Widgets.size() - 1;
        }

        void render() {
            for (UIWidget w:Widgets) {
                w.render(this);
            }
        }
    };
}