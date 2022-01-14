#pragma once

#include <SFML/System.hpp>
#include "IAUI.hpp"

namespace IA {

    enum UIEventType {
        focusGained,
        focusLost,
        mousePressed,
        mouseReleased,
        keyPressed,
        keyReleased,
        render
    };

    struct UIEvent {
        UIEventType type; // type of event from enum UIEventType
        sf::Event SFMLEvent; // SFML event that triggered this event
        int widget; // ID of Widget that triggered the event
    };
}