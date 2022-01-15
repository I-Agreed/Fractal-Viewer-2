/* 
UNIT EXPLANATION TO NOT CONFUSE MYSELF LATER:

NUMBER UNITS: because a fractal is drawn on the complex plane, this is the units used there.
1 number unit is equal to the distance from 0 to 1 on the plane.

PIXELS: actual pixels drawn on screen, units used by the canvas and sfml.

Graphics are drawn in PIXELS and the backend logic is done in NUMBER UNITS, so:
    when drawing graphics convert from numbers to pixels.
    when getting mouse and other input convert from pixels to numbers.
*/

#pragma once

#include "../ui/IAUI.hpp"
#include <algorithm>

struct FractalDisplay: public IA::Canvas {
    double zoom; // amount of number units per pixel TODO: Replace with MPF type
    IA::Vector2<double> cameraPos; // Camera pos in pixels (position of (0, 0) in number units)

    FractalDisplay(int x, int y, int w, int h):Canvas(x, y, w, h) {
            zoom = 1;
            cameraPos = IA::Vector2<double>(w/2, h/2);
        }

    void apply_zoom(float factor, IA::Vector2<int> centre) {
        zoom *= factor;
        cameraPos -= centre;
        cameraPos /= factor;
        cameraPos += centre;
    }

    void handle_event(IA::UIEvent event) {
        UIWidget::handle_event(event);

        switch (event.type) {
            case IA::UIEventType::mouseScrolled: {
                apply_zoom(std::pow(2, event.SFMLEvent.mouseWheelScroll.delta * -0.3), event.mousePos);
            }
        }
    }

    // Converts from pixel units to number units TODO: Replace double with MPF type Vecctor2
    IA::Vector2<double> pixel_pos_to_number_pos(IA::Vector2<int> pixel) {
	    return (pixel - cameraPos) * zoom;
    }

    // Converts from pixel units to number units TODO: Replace double with MPF type
    double pixels_to_number_units(int pixels) {
	    return pixels * zoom;
    }

    // Converts from number units to pixel units TODO: Replace double with MPF type Vecctor2
    IA::Vector2<int> number_pos_to_pixel_pos(IA::Vector2<double> number) {
	    return number/zoom + cameraPos;
    }

    // Converts from pixel units to number units TODO: Replace double with MPF type
    int number_units_to_pixels(double number) {
	    return number/zoom;
    }
};