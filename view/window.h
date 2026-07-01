#pragma once
#include <queue>
#include <vector>

#pragma once
#include <string>

namespace gui {

    // Типы событий
    enum class EventType {
        None,
        Closed,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        KeyPressed,
        KeyReleased
    };

    // Кнопки мыши
    enum class MouseButton {
        Left,
        Right,
        Middle
    };

    // Клавиши клавиатуры
    enum class KeyCode {
        None,
        Escape,
        Enter,
        Delete,
        Space,
        Up,
        Down,
        Left,
        Right
    };

    // Структура позиции
    struct Point {
        float x;
        float y;

        Point(float x = 0, float y = 0) : x(x), y(y) {}
    };

    // Событие
    class Event {
    public:
        Event() : m_type(EventType::None) {}

        explicit Event(EventType type) : m_type(type) {}

        EventType getType() const { return m_type; }

        // Для событий мыши
        MouseButton getMouseButton() const { return m_mouseButton; }
        Point getMousePosition() const { return m_mousePosition; }

        // Для событий клавиатуры
        KeyCode getKeyCode() const { return m_keyCode; }

        // Сеттеры для создания событий
        void setType(EventType type) { m_type = type; }
        void setMouseButton(MouseButton button) { m_mouseButton = button; }
        void setMousePosition(float x, float y) { m_mousePosition = Point(x, y); }
        void setKeyCode(KeyCode key) { m_keyCode = key; }

    private:
        EventType m_type;
        MouseButton m_mouseButton = MouseButton::Left;
        Point m_mousePosition;
        KeyCode m_keyCode = KeyCode::None;
    };

    class Window {
    public:
        Window(int width = 800, int height = 600)
            : m_width(width), m_height(height), m_isOpen(true) {
        }

        ~Window() = default;

        bool isOpen() const { return m_isOpen; }
        void close() { m_isOpen = false; }

        // Обработка ввода
        void handleInput(const Event& event) {
            m_eventQueue.push(event);
        }

        // Получение событий
        bool popEvent(Event& event) {
            if (m_eventQueue.empty()) {
                return false;
            }
            event = m_eventQueue.front();
            m_eventQueue.pop();
            return true;
        }

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }

        void display() {
        }

        void clear() {
        }

    private:
        int m_width;
        int m_height;
        bool m_isOpen;
        std::queue<Event> m_eventQueue;
    };

} // namespace gui