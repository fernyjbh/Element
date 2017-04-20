
#ifndef EL_CONTROLLER_H
#define EL_CONTROLLER_H

#include "ElementApp.h"

namespace Element {
    class Controller
    {
    public:
        Controller() : parent (nullptr) { }
        virtual ~Controller()
        {
            parent = nullptr;
        }
        
        inline Controller* getParent() const { return parent; }
        inline Controller* getRoot() const
        {
            Controller* c = const_cast<Controller*> (this);
            while (c != nullptr) {
                if (nullptr == c->getParent())
                    break;
                c = c->getParent();
            }
            return c;
        }
        
        template<class T> inline T* findParent() const
        {
            Controller* ctl = const_cast<Controller*> (this);
            while (nullptr != ctl)
            {
                if (auto* parent = dynamic_cast<T*> (ctl->parent))
                    return parent;
                ctl = ctl->parent;
            }
            return nullptr;
        }
        
        template<class T> inline T* findChild() const
        {
            for (auto const* c : children)
                if (T* t = const_cast<T*> (dynamic_cast<const T*> (c)))
                    return t;
            return nullptr;
        }
        
        inline void addChild (Controller* c)
        {
            if (auto* added = children.add (c))
                added->parent = this;
        }

        
        virtual void activate() {
            for (auto* child : children) {
                child->activate();
            }
        }
        
        virtual void deactivate() {
            for (auto* child : children) {
                child->deactivate();
            }
        }
        
    private:
        OwnedArray<Controller> children;
        Controller* parent;
    };
}

#endif  // EL_CONTROLLER_H
