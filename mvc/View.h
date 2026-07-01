#pragma once
#include "Model.h"
#include <memory>

namespace mvc {

    class View : public std::enable_shared_from_this<View>, public IModelObserver {
    public:
        virtual ~View() = default;
        virtual void render() = 0;
        virtual void update() = 0;
        virtual void onModelChanged() = 0;
        virtual void close() = 0;

        void setModel(std::shared_ptr<Model> model) {
            m_model = model;
            if (m_model) {
                m_model->attach(shared_from_this());
            }
        }

    protected:
        std::shared_ptr<Model> m_model;
    };

}