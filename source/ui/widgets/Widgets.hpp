/*
A header file to include all of the widget headers and define all the structs

Base Widget class:

#pragma once

#include "../UIWidget.hpp"
#include <SFML/Graphics.hpp>

namespace IA {
    struct Name: public UIWidget {

        Name(int x, int y, int w, int h): 
        UIWidget(x, y, w, h) {
        }

        // Renders this Widget
        void render(UIWindow *win) {

        }

        // Handles Events
        void handle_event(UIEvent event) {
            UIWidget::handle_event(event);

            switch (event.type) {
            }
        }
    };
}

*/

#pragma once

namespace IA {
    struct Canvas;
}

#include "Canvas.hpp"