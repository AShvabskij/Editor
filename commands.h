#pragma once
#include "model/EditorModel.h"
#include "model/ItemData.h"

#include <string>
#include <cstdint>
#include <functional>

class ICommand {
public:
    virtual void execute() = 0;
    virtual ~ICommand() = default;
};

class Command : public ICommand {
protected:
    std::shared_ptr<model::EditorModel> m_model;

    Command(std::shared_ptr<model::EditorModel> model)
        : m_model(model) {
    }

public:
    virtual ~Command() = default;
};

class NewDocumentCommand : public Command {
public:
    NewDocumentCommand(std::shared_ptr<model::EditorModel> model)
        : Command(model) {
    }

    void execute() override {
        m_model->createNewDocument();
    }
};

#pragma once

class ImportDocumentCommand : public Command {
private:
    std::string m_filename;

public:
    ImportDocumentCommand(std::shared_ptr<model::EditorModel> model, const std::string& filename)
        : Command(model)
        , m_filename(filename) {
    }

    void execute() override {
        m_model->importDocument(m_filename);
    }
};

class ExportDocumentCommand : public Command {
private:
    std::string m_filename;

public:
    ExportDocumentCommand(std::shared_ptr<model::EditorModel> model, const std::string& filename)
        : Command(model)
        , m_filename(filename) {
    }

    void execute() override {
        m_model->exportDocument(m_filename);
    }
};

class CreateItemCommand : public Command {
private:
    model::ItemType m_type;
    model::Point m_position;
    model::Size m_size;

public:
    CreateItemCommand(std::shared_ptr<model::EditorModel> model,
        model::ItemType type,
        const model::Point& position,
        const model::Size& size)
        : Command(model)
        , m_type(type)
        , m_position(position)
        , m_size(size) {
    }

    void execute() override {
        m_model->createItem(m_type, m_position, m_size);
    }
};

class DeleteItemCommand : public Command {
private:
    uint32_t m_itemId;

public:
    DeleteItemCommand(std::shared_ptr<model::EditorModel> model, uint32_t itemId)
        : Command(model)
        , m_itemId(itemId) {
    }

    void execute() override {
        m_model->deleteItem(m_itemId);
    }
};
