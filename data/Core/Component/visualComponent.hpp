#ifndef VISUALCOMPONENT_HPP_INCLUDED
#define VISUALCOMPONENT_HPP_INCLUDED

#include "component.hpp"
#include "../View/view.hpp"

class VisualComponent : public Component {
public:
    View * view;
    wxWindow * ownerWindow;
    VisualComponent(wxWindow * parentWindow, string componentID, int viewWidth) : Component(componentID) {
        this->ownerWindow = parentWindow;
        view = new View(parentWindow, viewWidth);
    }
    VisualComponent(VisualComponent * parentComponent, string componentID, int viewWidth) : Component(componentID) {
        this->ownerWindow = parentComponent->ownerWindow;
        view = new View(parentComponent->ownerWindow, viewWidth);
    }
    void connectView(VisualComponent * parentComponent) {
        parentComponent->addChildren(this);
        parentComponent->view->grid->Add(view->grid, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    }
    void serveEvent(Event * event) {
        Component::serveEvent(event);
    }
};

#endif // VISUALCOMPONENT_HPP_INCLUDED
