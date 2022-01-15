/* 
UNIT EXPLANATION TO NOT CONFUSE MYSELF LATER:

NUMBER UNITS: because a fractal is drawn on the complex plane, this is the units used there.
1 number unit is equal to the distance from 0 to 1 on the plane.

PIXELS: actual pixels drawn on screen, units used by the canvas and sfml.
*/

#pragma once;

#include "../ui/IAUI.hpp"

struct FractalDisplay: public IA::Canvas {
    double zoom; // amount of "number units" per pixel TODO: Replace with MPF type
    IA::Vector2<double> cameraPos; // Camera pos in Pixels TODO: Replace with MPF type Vecctor2

    FractalDisplay(int x, int y, int w, int h): 
        Canvas(x, y, w, h) {
        }

    void apply_zoom(float factor, IA::Vector2) {
        zoom *= factor;
        IA::Vector2f pos(e.mouseWheelScroll.x, e.mouseWheelScroll.y);
        cameraPos -= pos;
        cameraPos *= factor;
        cameraPos += pos;
    }
};