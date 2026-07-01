#pragma once
#include "ItemData.h"
#include <vector>
#include <memory>
#include <string>

namespace model {

    class Document {
    public:
        Document() : m_modified(false), m_name("Untitled") {}
        explicit Document(const std::string& name) : m_modified(false), m_name(name) {}

        // Document operations
        void addItem(std::shared_ptr<ItemData> item) {
            m_items.push_back(item);
            m_modified = true;
        }

        bool removeItem(size_t index) {
            if (index < m_items.size()) {
                m_items.erase(m_items.begin() + index);
                m_modified = true;
                return true;
            }
            return false;
        }

        bool removeItemById(size_t id) {
            auto it = std::find_if(m_items.begin(), m_items.end(),
                [id](const auto& item) { return item->getId() == id; });
            if (it != m_items.end()) {
                m_items.erase(it);
                m_modified = true;
                return true;
            }
            return false;
        }

        // Getters
        const std::vector<std::shared_ptr<ItemData>>& getItems() const { return m_items; }
        bool isModified() const { return m_modified; }
        const std::string& getName() const { return m_name; }
        size_t getItemCount() const { return m_items.size(); }

        // Setters
        void setModified(bool modified) { m_modified = modified; }
        void setName(const std::string& name) { m_name = name; }

        // Serialization
        std::string serialize() const { return std::string(""); }
        static std::shared_ptr<Document> deserialize(const std::string& data) {
            auto doc = std::make_shared<Document>("ImportedDocument");

            // Создаем тестовые элементы
            for (int i = 0; i < 3; ++i) {
                auto item = std::make_shared<ItemData>(
                    ItemType::Rectangle,
                    Point(100 + i * 50, 100 + i * 50),
                    Size(50, 50)
                );
                doc->addItem(item);
            }

            return doc;
        }

    private:
        std::vector<std::shared_ptr<ItemData>> m_items;
        bool m_modified;
        std::string m_name;
    };

} // namespace model