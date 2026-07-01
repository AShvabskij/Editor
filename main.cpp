#include "mvc/Controller.h"
#include "model/EditorModel.h"
#include "view/Menu.h"
#include "view/EditorView.h"

#include <memory>
#include <iostream>
#include <cstdlib>

using namespace std;

class Application : public mvc::IController{
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

	// Command handlers (overrides from mvc::Controller)
	void onCreateNewDocument() override {
		std::cout << "Creating new document..." << std::endl;
		m_model->createNewDocument();
		m_view->update();
	}

	void onImportDocument(const std::string& filename) override {
		std::cout << "Importing document from file: " << filename << std::endl;
		m_model->importDocument(filename);
		m_view->update();
	}

	void onExportDocument(const std::string& filename) override {
		std::cout << "Exporting document to file: " << filename << std::endl;
		m_model->exportDocument(filename);
	}

	void onCreateItem(const std::string& type, float x, float y) override {
		std::cout << "Creating " << type << " at (" << x << ", " << y << ")" << std::endl;

		if (type == "rectangle") {
			m_model->createItem(model::ItemType::Rectangle, model::Point(x, y), model::Size(100, 80));
		}
		else if (type == "circule") {
			m_model->createItem(model::ItemType::Circule, model::Point(x, y), model::Size(50, 50));
		}
		else {
			std::cout << "Unknown item type: " << type << std::endl;
			return;
		}
	}

	void onDeleteItem(uint32_t itemId) override {
		std::cout << "Deleting item with ID: " << itemId << std::endl;
		m_model->deleteItem(itemId);
	}

	// Additional handlers
	void onItemSelect(float x, float y) {
		m_view->selectItem(x, y);
	}

private:
	// Helper methods
	void setupMenu() {
		m_menu->addItem("New", [this]() { this->onCreateNewDocument(); });
		m_menu->addItem("Import", [this]() { this->onImportDocument("document.json"); });
		m_menu->addItem("Export", [this]() { this->onExportDocument("document_export.json"); });
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
		while (m_view->getWindow().poolEvent(event)) {
			if (event.getType() == gui::EventType::Closed) {
				shutdown();
			}
			else if (event.getType() == gui::EventType::MouseButtonPressed) {
				float x = event.getMousePosition().x;
				float y = event.getMousePosition().y;

				// Check menu clicks first
				if (!m_menu->handleClick(x, y)) {
					// Canvas clicks - select item
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
