#pragma once
#include <string>
#include <memory>

namespace model {

    enum class ItemType {
        Rectangle,
        Circule,
        Triangle,
        Line
    };

    struct Point {
        float x;
        float y;

        Point(float x = 0, float y = 0) : x(x), y(y) {}
    };

    struct Size {
        float width;
        float height;

        Size(float w = 0, float h = 0) : width(w), height(h) {}
    };

    class ItemData {
    public:
        ItemData(ItemType type, Point position, Size size, std::string color = "#000000")
            : m_type(type)
            , m_position(position)
            , m_size(size)
            , m_color(color)
            , m_id(s_nextId++) {
        }

        virtual ~ItemData() = default;

        // Getters
        ItemType getType() const { return m_type; }
        Point getPosition() const { return m_position; }
        Size getSize() const { return m_size; }
        std::string getColor() const { return m_color; }
        uint32_t getId() const { return m_id; }

        // Setters
        void setPosition(Point pos) { m_position = pos; }
        void setSize(Size size) { m_size = size; }
        void setColor(const std::string& color) { m_color = color; }

    private:
        static inline uint32_t s_nextId = 0;

        ItemType m_type;
        Point m_position;
        Size m_size;
        std::string m_color;
        uint32_t m_id;
    };

} // namespace model