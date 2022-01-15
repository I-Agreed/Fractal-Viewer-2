// The main fractal rendering function

#pragma once

#include "Fractals.hpp"
#include "../ui/IAUI.hpp"
#include <SFML/Graphics.hpp>

//TODO: Change doubles to MPF types
// texture: RenderTexture to draw to, p1: top left point in number units, p2: bottom right point in number units
void generate_fractal(sf::RenderTexture *texture, IA::Vector2<double> p1, IA::Vector2<double> p2, Fractals fractal) {
    
}