#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include <wx/button.h>
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Core/Component/controlComponent.hpp"
#include "../../Core/Event/event.hpp"
class Button : public ControlComponent<wxButton> {
public:
    Button(VisualComponent * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxButton(ownerWindow, elementID, _(label), wxPoint(0,0), wxDefaultSize, 0, wxDefaultValidator, _T( "TODO" ));
        elementRef->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &sendClick, this);
    }
    void serveEvent(Event * event) {
        ControlComponent::serveEvent(event);
    }
    void sendClick(wxCommandEvent& event) {
        Event * ev = new Event();
        ev->eventType = "onClick";
        serveEvent(ev);
    }
};

#endif // BUTTON_HPP_INCLUDED