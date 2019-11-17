#ifndef NOTEBOOK_HPP_INCLUDED
#define NOTEBOOK_HPP_INCLUDED
#include "../../Core/Component/panelComponent.hpp"
#include "wx/aui/aui.h"
class Notebook : public ControlComponent<wxAuiNotebook> {
public:
    Notebook(VisualComponent * parent, string componentID, int width, int height): ControlComponent(parent, componentID) {
        elementRef = new wxAuiNotebook(ownerWindow, elementID, wxDefaultPosition, wxSize(width,height), wxAUI_NB_DEFAULT_STYLE);
    }
    void serveEvent(Event * event) {
        ControlComponent::serveEvent(event);
    }
    void addPage(PanelComponent * newPanel, string label) {
        addChildren(newPanel);
        elementRef->AddPage(newPanel->elementRef, label);
    }
};

#endif // NOTEBOOK_HPP_INCLUDED
