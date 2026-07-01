#pragma once
#include <memory>
#include <vector>
#include <functional>

namespace mvc {

    class Model;

    // Observer interface for View
    class IModelObserver {
    public:
        virtual ~IModelObserver() = default;
        virtual void onModelChanged() = 0;
    };

    // Base Model class
    class Model {
    public:
        virtual ~Model() = default;

        void attach(std::weak_ptr<IModelObserver> observer) {
            m_observers.push_back(observer);
        }

        void notifyObservers() {
            for (auto it = m_observers.begin(); it != m_observers.end();) {
                if (auto observer = it->lock()) {
                    observer->onModelChanged();
                    ++it;
                }
                else {
                    it = m_observers.erase(it);
                }
            }
        }

    private:
        std::vector<std::weak_ptr<IModelObserver>> m_observers;
    };

} // namespace mvc