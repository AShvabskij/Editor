#pragma once
#include "ViewItem.h"
#include "../model/ItemData.h"

#include <vector>
#include <memory>

namespace view {

    class Canvas {
    public:
        Canvas(int width, int height) {};
        ~Canvas() = default;

        void render() {
            for (const auto& item : m_items) {
                item->draw();
            }
        }

        void addItem(std::shared_ptr<model::ItemData> data) {
            auto viewItem = createViewItem(data);
            if (viewItem) {
                m_items.push_back(std::move(viewItem));
                m_needsUpdate = true;
            }
        }

        void selectItem(float x, float y) { 
            selectedItemInd = findItemAt(x, y);
        }

        bool removeItem(size_t id) { return true;  };
        std::shared_ptr<ViewItem> selectItemAt(float x, float y) { return nullptr; };
        uint32_t getSelectedItemId() { return m_items[selectedItemInd]->getId(); };

        const auto& getItems() const {
            return m_items;
        }

        void clear() { 
            m_items.clear(); 
            m_needsUpdate = true;
        };

    private:
        uint32_t findItemAt(float x, float y) {
            return 0;
        }

        std::unique_ptr<ViewItem> createViewItem(std::shared_ptr<model::ItemData> data) {
            if (!data) return nullptr;

            switch (data->getType()) {
            case model::ItemType::Rectangle:
                return std::make_unique<RectangleViewItem>(data);
            case model::ItemType::Circule:
                return std::make_unique<CircleViewItem>(data);
            case model::ItemType::Triangle:
                // return std::make_unique<TriangleViewItem>(data);
            case model::ItemType::Line:
                // return std::make_unique<LineViewItem>(data);
            default:
                return nullptr;
            }
        }

        std::vector<std::unique_ptr<ViewItem>> m_items;
        uint32_t selectedItemInd = 0;
        bool m_needsUpdate;
    };

} 