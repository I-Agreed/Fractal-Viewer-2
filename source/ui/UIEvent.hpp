#pragma once

#include <SFML/System.hpp>

namespace IA {

    enum UIEventType {
        focusGained,
        focusLost,
        keyPressed,
        keyReleased,
        mousePressed,
        mouseReleased,
        mouseScrolled,
        mouseMoved,
        NonUI
    };

    struct UIEvent {
        UIEventType type; // type of event from enum UIEventType
        sf::Event SFMLEvent; // SFML event that triggered this event
        int widget = -1; // ID of Widget that triggered the event
        Vector2<int> mousePos; // Position of mouse relative to widget, only applicable on mouse events.
        Vector2<int> mouseDelta; // Change in mouse position, only for mouseMoved events.

        UIEvent() {};

        UIEvent(UIEventType _type, sf::Event _SFMLEvent, int _widget, Vector2<int> _mousePos = Vector2<int>(), Vector2<int> _mouseDelta = Vector2<int>()) {
            type = _type;
            SFMLEvent = _SFMLEvent;
            widget = _widget;
            mousePos = mousePos;
        }
    };
}