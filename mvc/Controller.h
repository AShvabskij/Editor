#pragma once
#include <memory>
#include <string>

namespace mvc {

    class IController {
    public:
        IController() = default;
        virtual ~IController() = default;

        // Command handlers
        virtual void onCreateNewDocument() = 0;
        virtual void onImportDocument(const std::string& filename) = 0;
        virtual void onExportDocument(const std::string& filename) = 0;
        virtual void onCreateItem(const std::string& type, float x, float y) = 0;
        virtual void onDeleteItem( uint32_t index) = 0;

    };

} // namespace mvc