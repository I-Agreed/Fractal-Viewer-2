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

        // Returns ID of top widget that has the pos in its bounding box
        int getWidgetFromPos(Vector2<int> pos) {
            for (int i = widgets.size() - 1; i >= 0; i--) {
                if (widgets[i]->box.contains(pos)) {
                    return i;
                }
            }
        }

        // Changes the focused widget. Returns true if successful (widget was different).
        bool changeFocus(int newFocus, sf::Event event=sf::Event()) {
            if (newFocus != focus) {
                raiseEvent(UIEvent(UIEventType::focusLost, event, focus));
                raiseEvent(UIEvent(UIEventType::focusGained, event, newFocus));
                focus = newFocus;
                return true;
            } else {
                return false;
            }
        }

        void raiseEvent(UIEvent event) {
            events.push(event);
        }

        void handleEvents() {
            UIEvent event;
            sf::Event sfmlEvent;
            while (RenderWindow::pollEvent(sfmlEvent)) {
                event = UIEvent();
                switch (event.SFMLEvent.type) {
                    case sf::Event::EventType::KeyPressed:
                        event.type = UIEventType::keyPressed;
                        event.widget = focus;
                        break;
                    case sf::Event::EventType::KeyReleased:
                        event.type = UIEventType::keyReleased;
                        event.widget = focus;
                        break;
                    case sf::Event::EventType::MouseButtonPressed: // Raises event and changes focus
                        Vector2<int> pos = Vector2<int>(sfmlEvent.mouseButton.x, sfmlEvent.mouseButton.y);
                        int newFocus = getWidgetFromPos(pos);
                        changeFocus(newFocus, sfmlEvent);
                        event.type = UIEventType::mousePressed;
                        event.widget = focus;
                        event.mousePos = pos - widgets[focus]->box.p1;
                        break;
                    case sf::Event::EventType::MouseButtonReleased:
                        Vector2<int> pos = Vector2<int>(sfmlEvent.mouseButton.x, sfmlEvent.mouseButton.y);
                        event.type = UIEventType::mouseReleased;
                        event.widget = focus;
                        event.mousePos = pos - widgets[focus]->box.p1;
                        break;
                    case sf::Event::EventType::MouseWheelScrolled:
                        Vector2<int> pos = Vector2<int>(sfmlEvent.mouseWheelScroll.x, sfmlEvent.mouseWheelScroll.y);
                        event.type = UIEventType::mouseScrolled;
                        event.widget = focus;
                        event.mousePos = pos - widgets[focus]->box.p1;
                        break;
                    case sf::Event::EventType::MouseMoved:
                        
                    default:
                        event.type = UIEventType::NonUI;
                        break;
                }
                event.SFMLEvent = sfmlEvent;
                raiseEvent(event);
            }
        }

        bool pollUIEvent(UIEvent& event) {
            handleEvents();
            if (events.size() > 0) {
                event = events.front();
                events.pop();
                return true;
            
            } else {
                return false;
            }
        }
    };
}