// The main fractal rendering function

#pragma once

#include "Fractals.hpp"
#include "../ui/IAUI.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <sstream>

sf::Shader mandelbrotShader;

void load_shaders() {
    std::ifstream mandelbrotFile("../source/fractals/shaders/mandelbrot.frag");
    std::stringstream mandelbrotBuffer;
    mandelbrotBuffer << mandelbrotFile.rdbuf();
    mandelbrotShader.loadFromMemory(mandelbrotBuffer.str(), sf::Shader::Fragment);
}

//TODO: Change doubles to MPF types
// texture: RenderTexture to draw to, p1: top left point in number units, p2: bottom right point in number units
void generate_fractal(sf::RenderTexture *texture, IA::Vector2<float> cameraPos, float zoom, Fractals fractal) {

    sf::Vector2u textureSize = texture->getSize();
    sf::Sprite sprite(texture->getTexture());
    
    mandelbrotShader.setUniform("u_resolution", sf::Vector2f(textureSize.x, textureSize.y));
    mandelbrotShader.setUniform("cameraPos", (sf::Vector2f)cameraPos);
    mandelbrotShader.setUniform("zoom", zoom);
    texture->draw(sprite, &mandelbrotShader);
}