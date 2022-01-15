#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include "IAUI.hpp"

namespace IA {
    struct UIWindow: public sf::RenderWindow {

        std::vector<UIWidget*> widgets;
        int focus = -1; // ID of Widget that has focus, -1 for none. Focus is gained by clicking on a widget
        std::queue<UIEvent> events;
        Vector2<int> lastMousePos; // Mouse Position from last MouseMoveEvent

        // Constructor (the same params as sfml window constructor)
        UIWindow(sf::VideoMode mode, const sf::String &title, sf::Uint32 style=sf::Style::Default, 
                 const sf::ContextSettings &settings = sf::ContextSettings()):
                 sf::RenderWindow(mode, title, style, settings) {
            lastMousePos = sf::Mouse::getPosition(*this);
        }

        // Adds a widget to the window, returns the widget's ID
        int add_widget(UIWidget *w) {
            widgets.push_back(w);
            return widgets.size() - 1;
        }

        void render() {
            clear();
            for (int i = 0; i < widgets.size(); i++) {
                widgets[i]->render(this);
            }
            display();
        }

        // Returns ID of top widget that has the pos in its bounding box. Returns -1 if no widget is found.
        int get_widget_at_pos(Vector2<int> pos) {
            for (int i = widgets.size() - 1; i >= 0; i--) {
                if (widgets[i]->box.contains(pos)) {
                    return i;
                }
            }
            return -1;
        }

        // Changes the focused widget. Returns true if successful (widget was different).
        bool change_focus(int newFocus, sf::Event event=sf::Event()) {
            if (newFocus != focus && newFocus != -1) {
                raise_event(UIEvent(UIEventType::focusLost, event, focus));
                raise_event(UIEvent(UIEventType::focusGained, event, newFocus));
                focus = newFocus;
                return true;
            } else if (newFocus == -1) {
                raise_event(UIEvent(UIEventType::focusLost, event, focus));
                focus = newFocus;
                return true;
            } else {
                return false;
            }
        }

        void raise_event(UIEvent event) {
            events.push(event);
        }

        void handle_events() {
            UIEvent event;
            sf::Event sfmlEvent;
            while (RenderWindow::pollEvent(sfmlEvent)) {
                event = UIEvent();
                switch (sfmlEvent.type) {
                    case sf::Event::EventType::KeyPressed: {
                        event.type = UIEventType::keyPressed;
                        event.widget = focus;
                        break;
                    } case sf::Event::EventType::KeyReleased: {
                        event.type = UIEventType::keyReleased;
                        event.widget = focus;
                        break;
                    } case sf::Event::EventType::MouseButtonPressed: { // Raises event and changes focus
                        Vector2<int> pos = Vector2<int>(sfmlEvent.mouseButton.x, sfmlEvent.mouseButton.y);
                        int newFocus = get_widget_at_pos(pos);
                        change_focus(newFocus, sfmlEvent);
                        event.type = UIEventType::mousePressed;
                        event.widget = focus;

                        if (focus != -1) event.mousePos = pos - widgets[focus]->box.p1;
                        else event.mousePos = pos;
                        
                        break;
                    } case sf::Event::EventType::MouseButtonReleased: {
                        Vector2<int> pos = Vector2<int>(sfmlEvent.mouseButton.x, sfmlEvent.mouseButton.y);
                        event.type = UIEventType::mouseReleased;
                        event.widget = focus;

                        if (focus != -1) event.mousePos = pos - widgets[focus]->box.p1;
                        else event.mousePos = pos;
                        
                        break;
                    } case sf::Event::EventType::MouseWheelScrolled: {
                        Vector2<int> pos = Vector2<int>(sfmlEvent.mouseWheelScroll.x, sfmlEvent.mouseWheelScroll.y);
                        event.type = UIEventType::mouseScrolled;
                        event.widget = get_widget_at_pos(pos);

                        if (focus != -1) event.mousePos = pos - widgets[focus]->box.p1;
                        else event.mousePos = pos;
                        
                        break;
                    } case sf::Event::EventType::MouseMoved: {
                        Vector2<int> pos = Vector2<int>(sfmlEvent.mouseMove.x, sfmlEvent.mouseMove.y);
                        event.type = UIEventType::mouseMoved;
                        event.widget = focus;

                        if (focus != -1) event.mousePos = pos - widgets[focus]->box.p1;
                        else event.mousePos = pos;

                        event.mouseDelta = pos - lastMousePos;
                        lastMousePos = pos;
                        break;
                    } default: {
                        event.type = UIEventType::NonUI;
                        break;
                    }
                }
                event.SFMLEvent = sfmlEvent;
                raise_event(event);
            }
        }

        // Polls event and calls Widget's own handle method if applicable
        bool poll_UIEvent(UIEvent& event) {
            handle_events();
            if (events.size() > 0) {
                event = events.front();
                events.pop();
                if (event.widget != -1) {
                    widgets[event.widget]->handle_event(event);
                }
                return true;
            } else {
                return false;
            }
        }
    };
}