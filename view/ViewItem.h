#pragma once
#include "model/ItemData.h"
#include <memory>

namespace view {

    class ViewItem {
    public:
        explicit ViewItem(std::shared_ptr<model::ItemData> data)
            : m_data(data) {
        }

        virtual ~ViewItem() = default;

        virtual void draw() const = 0;
        virtual bool containsPoint(float x, float y) const = 0;
        virtual void update() {}

        std::shared_ptr<model::ItemData> getData() const { return m_data; }
        uint32_t getId() const { return m_data->getId(); }

    protected:
        std::shared_ptr<model::ItemData> m_data;
    };

    // Concrete implementations
    class RectangleViewItem : public ViewItem {
    public:
        explicit RectangleViewItem(std::shared_ptr<model::ItemData> data);
        void draw() const override;
        bool containsPoint(float x, float y) const override;
    };

    class CircleViewItem : public ViewItem {
    public:
        explicit CircleViewItem(std::shared_ptr<model::ItemData> data);
        void draw() const override;
        bool containsPoint(float x, float y) const override;
    };

} // namespace view