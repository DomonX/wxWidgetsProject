#ifndef TEXTINPUT_HPP_INCLUDED
#define TEXTINPUT_HPP_INCLUDED

#include <wx/textctrl.h>
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Core/Component/controlComponent.hpp"
#include "../../Core/Event/event.hpp"
class TextInput : public ControlComponent<wxTextCtrl> {
public:
    TextInput(VisualComponent * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxTextCtrl(ownerWindow, elementID, _(label), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("TODO"));
        //elementRef->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &sendClick, this);
    }
    void serveEvent(Event * event) {
        ControlComponent::serveEvent(event);
    }
    //void sendClick(wxCommandEvent& event) {
    //    Event * ev = new Event();
    //    ev->eventType = "onClick";
    //    serveEvent(ev);
    //}
};

#endif // TEXTINPUT_HPP_INCLUDED
