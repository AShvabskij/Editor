#include "mvc/Controller.h"
#include "model/EditorModel.h"
#include "view/Menu.h"
#include "view/EditorView.h"
#include "commands.h"

#include <memory>
#include <iostream>
#include <cstdlib>

using namespace std;

class Application : public mvc::IController {
public:
    Application()
        : m_model(std::make_shared<model::EditorModel>())
        , m_view(std::make_shared<view::EditorView>(800, 600))
        , m_menu(std::make_shared<view::Menu>())
    {
        // Set model for view
        m_view->setModel(m_model);

        // Setup menu
        setupMenu();
    }

    ~Application() {
        shutdown();
    }

    void run() {
        while (m_running && m_view->getWindow().isOpen()) {
            processEvents();
            render();
        }
    }

    void shutdown() {
        m_running = false;
        if (m_view) {
            m_view->close();
        }
    }

    void onCreateNewDocument() override {
        std::cout << "Creating new document..." << std::endl;
        NewDocumentCommand command(m_model);
        command.execute();
        m_view->update();
    }

    void onImportDocument(const std::string& filename) override {
        ImportDocumentCommand command(m_model, filename);
        command.execute();
        m_view->update();
    }

    void onExportDocument(const std::string& filename) override {
        std::cout << "Exporting document to file: " << filename << std::endl;
        ExportDocumentCommand command(m_model, filename);
        command.execute();
    }

    void onCreateItem(const std::string& type, float x, float y) override {
        std::cout << "Creating " << type << " at (" << x << ", " << y << ")" << std::endl;

        model::ItemType itemType;
        model::Size size;

        if (type == "rectangle") {
            itemType = model::ItemType::Rectangle;
            size = model::Size(100, 80);
        }
        else if (type == "circle") {
            itemType = model::ItemType::Circule;
            size = model::Size(50, 50);
        }
        else {
            std::cout << "Unknown item type: " << type << std::endl;
            return;
        }

        CreateItemCommand command(m_model, itemType, model::Point(x, y), size);
        command.execute();
        m_view->update();
    }

    void onDeleteItem(uint32_t itemId) override {
        std::cout << "Deleting item with ID: " << itemId << std::endl;
        DeleteItemCommand command(m_model, itemId);
        command.execute();
        m_view->update();
    }

    // Additional handlers
    void onItemSelect(float x, float y) {
        m_view->selectItem(x, y); // Canvas clicks - select item
    }

private:
    // Helper methods
    void setupMenu() {
        m_menu->addItem("New", [this]() {
            this->onCreateNewDocument();
            });

        m_menu->addItem("Import", [this]() {
            this->onImportDocument("document.json");
            });

        m_menu->addItem("Export", [this]() {
            this->onExportDocument("document_export.json");
            });

        m_menu->addItem("Create Rectangle", [this]() {
            float x = 100 + (rand() % 600);
            float y = 100 + (rand() % 400);
            this->onCreateItem("rectangle", x, y);
            });

        m_menu->addItem("Create Circle", [this]() {
            float x = 100 + (rand() % 600);
            float y = 100 + (rand() % 400);
            this->onCreateItem("circle", x, y);
            });

        m_menu->addItem("Delete", [this]() {
            auto itemId = m_view->getSelectedItemId();
            this->onDeleteItem(itemId);
            });

        m_menu->addItem("Quit", [this]() {
            std::cout << "\n[GUI Handler] Quitting application..." << std::endl;
            this->shutdown();
            });
    }

    void processEvents() {
        gui::Event event;
        while (m_view->getWindow().popEvent(event)) {
            if (event.getType() == gui::EventType::Closed) {
                shutdown();
            }
            else if (event.getType() == gui::EventType::MouseButtonPressed) {
                float x = event.getMousePosition().x;
                float y = event.getMousePosition().y;

                // Check menu clicks first
                if (!m_menu->handleClick(x, y)) {
                    onItemSelect(x, y);
                }
            }
            else if (event.getType() == gui::EventType::KeyPressed) {
                if (event.getKeyCode() == gui::KeyCode::Delete) {
                    auto itemId = m_view->getSelectedItemId();
                    onDeleteItem(itemId);
                }
            }
        }
    }

    void render() {
        m_view->render();
        m_menu->render();
    }

    // Application state
    std::shared_ptr<model::EditorModel> m_model;
    std::shared_ptr<view::EditorView> m_view;
    std::shared_ptr<view::Menu> m_menu;

    bool m_running = true;
};

// Main application loop
int main() {
    Application app;
    app.run();
    return 0;
}
