#ifndef CONTROLCOMPONENT_HPP_INCLUDED
#define CONTROLCOMPONENT_HPP_INCLUDED
#include "panelComponent.hpp"
template<class T> class ControlComponent : public VisualComponent{
public:
    T * elementRef;
    long elementID;
    ControlComponent(wxWindow * parent, string componentID): VisualComponent(parent, componentID, 1) {
        elementID = wxNewId();
    }
    void handleEvent(Event * event) {
        VisualComponent::handleEvent(event);
    }
    void connectControl(VisualComponent * parentComponent) {
        parentComponent->addChildren(this);
        view->grid->Add(elementRef, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
        parentComponent->view->grid->Add(view->grid, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    }
    void deleteComponent() {
        VisualComponent::deleteComponent();
        elementRef->Destroy();
        delete(this);
    }
};

#endif // CONTROLCOMPONENT_HPP_INCLUDED
