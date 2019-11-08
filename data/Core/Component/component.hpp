#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include "../Event/event.hpp"

#include <map>

using namespace std;


class Component {
public:
    Component * parent;
    string componentID;
    map<string, Component *> children;
    Component(string componentID) {
        parent = NULL;
        this->componentID = componentID;
    }
    virtual void handleEvent(Event * event) {
        free(event);
    }
    virtual void serveEvent(Event * event) {
        if(parent == NULL) {
            free(event);
            return;
        }
        processEvent(event);
    }
    void processEvent(Event * event) {
        event->path.push_back(componentID);
        parent->serveEvent(event);
    }
    void addChildren(Component * newComponent) {
        newComponent->parent = this;
        children[newComponent->componentID] = newComponent;
    }
};

#endif // COMPONENT_HPP_INCLUDED
