#pragma once

#include <vector>
#include <string>
#include <functional>

namespace view {

    struct MenuItem {
        std::string label;
        std::function<void()> action;
    };

    class Menu {
    public:
        Menu() = default;;
        ~Menu() = default;;

        void addItem(const std::string& label, std::function<void()> action) {};
        void render() {};
        bool handleClick(float x, float y) { return false; };

    private:
        std::vector<MenuItem> m_items;
        float m_x = 10;
        float m_y = 10;
        float m_spacing = 50;
    };

} 