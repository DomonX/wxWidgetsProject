#ifndef COMPONENT_HPP_INCLUDED
#define COMPONENT_HPP_INCLUDED

#include "../Event/event.hpp"

#include <map>
#include <vector>

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
    Component * getChildren(const char * path) {
        bool isEnd = false;
        string pathS = string(path);
        int index = pathS.find(".");
        string current;
        if(index == - 1) {
            current = pathS.substr(0, pathS.size());
            isEnd = true;
        } else {
            current = pathS.substr(0, index);
        }
        if(isEnd || children[current] == NULL) {
            return children[current];
        }
        string rest = pathS.substr(index + 1, pathS.size());
        return children[current]->getChildren(rest.c_str());
    }
};

#endif // COMPONENT_HPP_INCLUDED
