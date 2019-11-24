#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include "../Event/event.hpp"

#include <map>
#include <vector>

using namespace std;


class Component {
private:
    Component * parent;
    string componentID;
public:
    map<string, Component *> children;
    Component(string componentID) {
        parent = NULL;
        this->componentID = componentID;
    }
    virtual void deleteEvent(Event * event) {
        free(event);
    }
    virtual void handleEvent(Event * event) {
        if(parent == NULL) {
            deleteEvent(event);
            return;
        }
        processEvent(event);
    }
    virtual ~Component(){}
    virtual void deleteComponent() {}
    void processEvent(Event * event) {
        event->path.push_back(componentID);
        parent->handleEvent(event);
    }
    void addChildren(Component * newComponent) {
        newComponent->parent = this;
        children[newComponent->componentID] = newComponent;
    }
    Component * getChildren(string path) {
        bool isEnd = false;
        int index = path.find(".");
        string current;
        if(index == - 1) {
            current = path.substr(0, path.size());
            isEnd = true;
        } else {
            current = path.substr(0, index);
        }
        if(isEnd || children[current] == NULL) {
            return children[current];
        }
        string rest = path.substr(index + 1, path.size());
        return children[current]->getChildren(rest);
    }
};

#endif // COMPONENT_HPP_INCLUDED
