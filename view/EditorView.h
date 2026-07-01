#pragma once
#include "../mvc/View.h"
#include "../model/EditorModel.h"
#include "gui.h"
#include "Menu.h"
#include "Canvas.h"

namespace view {
    class EditorView : public mvc::View {
    public:
        EditorView(int width, int height) : m_window(std::make_unique<gui::Window>(width, height)),
                                            m_canvas(std::make_unique <view::Canvas>(width, height))
        {
            m_canvas->clear();
        }

        virtual ~EditorView() = default;
        void render() override { 
            m_canvas->render(); 
        };
        void update() override { 
            updateFromModel();
            m_canvas->render(); 
        };
        void onModelChanged() override { update(); }

        void handleInput(const gui::Event& event) { m_window->handleInput(event); }
        void selectItem(float x, float y) { m_canvas->selectItem(x, y); }

        gui::Window& getWindow() { return *m_window; }

        uint32_t getSelectedItemId() { return m_canvas->getSelectedItemId(); };

        void close() override {};

    private:
        void updateFromModel() {
            // Обновляем из модели
            if (auto editorModel = std::dynamic_pointer_cast<model::EditorModel>(m_model)) {
                const auto& items = m_canvas->getItems();
                // Здесь можно обновлять существующие элементы
                // или создавать новые
            }
        }

        std::unique_ptr <gui::Window> m_window;
        std::unique_ptr<view::Canvas> m_canvas;
    };
}
