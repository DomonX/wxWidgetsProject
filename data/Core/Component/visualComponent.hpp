#ifndef VISUALCOMPONENT_HPP_INCLUDED
#define VISUALCOMPONENT_HPP_INCLUDED

#include "component.hpp"
#include "../View/view.hpp"

class VisualComponent : public Component {
public:
    View * view;
    wxWindow * ownerWindow;
    VisualComponent(wxWindow * parentWindow, string componentID, int viewWidth) : Component(componentID) {
        setOwnerWindow(parentWindow);
        createView(viewWidth);
    }
    VisualComponent(string componentID) : Component(componentID) {}
    void setOwnerWindow(wxWindow * parentWindow) {
        this->ownerWindow = parentWindow;
    }
    void createView(int viewWidth) {
        view = new View(ownerWindow, viewWidth);
    }
    void connectView(VisualComponent * parentComponent) {
        parentComponent->addChildren(this);
        parentComponent->view->grid->Add(view->grid, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    }
    void handleEvent(Event * event) {
        Component::handleEvent(event);
    }
    void deleteComponent() {
        view->grid->Detach(ownerWindow);
        delete(view);
        delete(this);
    }
};

#endif // VISUALCOMPONENT_HPP_INCLUDED
