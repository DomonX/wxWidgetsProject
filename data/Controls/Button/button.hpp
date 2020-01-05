#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include <wx/button.h>
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Core/Component/controlComponent.hpp"
#include "../../Core/Event/event.hpp"
class Button : public ControlComponent<wxButton> {
public:
    Button(wxWindow * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxButton(ownerWindow, elementID, _(label), wxPoint(0,0), wxDefaultSize, 0, wxDefaultValidator, componentID);
        elementRef->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &sendClick, this);
    }
    void sendClick(wxCommandEvent& event) {
        Event * ev = new Event("onClick", &event);
        processEvent(ev);
    }
};

#endif // BUTTON_HPP_INCLUDED
