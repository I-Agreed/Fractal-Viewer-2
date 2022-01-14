/*
A header file to include all of the widget headers

Base Widget class:

#pragma once

#include "../UIWidget.hpp"
#include <SFML/Graphics.hpp>

namespace IA {
    class Name: public UIWidget {

        Name(int x, int y, int w, int h): 
        UIWidget(x, y, w, h) {
        }

        // Renders this Widget
        void render(UIWindow *win) {

        }
    };
}

*/

#pragma once

#include "Canvas.hpp"