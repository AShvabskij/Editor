#pragma once
#include "mvc/Model.h"
#include "Document.h"
#include "ItemData.h"
#include <memory>
#include <string>
#include <fstream>

namespace model {

    class EditorModel : public mvc::Model {
    public:
        EditorModel() : m_document(std::make_shared<model::Document>()) {}

        // Document operations
        void createNewDocument(const std::string& name = "Untitled") {
            m_document = std::make_shared<model::Document>(name);
            notifyObservers();
        }

        bool importDocument(const std::string& filename) {
            std::ifstream file(filename);
            if (!file.is_open()) return false;

            std::string content((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
            file.close();

            m_document = model::Document::deserialize(content);
            if (m_document) {
                notifyObservers();
                return true;
            }
            return false;
        }

        bool exportDocument(const std::string& filename) const {
            if (!m_document) return false;

            std::ofstream file(filename);
            if (!file.is_open()) return false;

            file << m_document->serialize();
            file.close();
            return true;
        }

        void createItem(model::ItemType type, model::Point position, model::Size size) {
            if (!m_document) return;

            auto item = std::make_shared<model::ItemData>(type, position, size);
            m_document->addItem(item);
            notifyObservers();
        }

        bool deleteItem(uint32_t id) {
            if (!m_document) return false;

            bool result = m_document->removeItemById(id);
            if (result) notifyObservers();
            return result;
        }

    private:
        std::shared_ptr<model::Document> m_document;
    };

} // namespace editor