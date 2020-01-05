#ifndef TEXTINPUT_HPP_INCLUDED
#define TEXTINPUT_HPP_INCLUDED

#include <wx/textctrl.h>
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Core/Component/controlComponent.hpp"
#include "../../Core/Event/event.hpp"
#include "../../Util/wxStringToString.hpp"
class TextInput : public ControlComponent<wxTextCtrl> {
protected:
    void sendChange(wxCommandEvent& event) {
        Event * ev = new Event("onChange", &event);
        processEvent(ev);
    }
public:
    TextInput(wxWindow * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxTextCtrl(ownerWindow, elementID, _(label), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, componentID);
        elementRef->Bind(wxEVT_COMMAND_TEXT_UPDATED, &sendChange, this);
    }
    string getText() {
        return wxStringToString(elementRef->GetLineText(0));
    }
};

#endif // TEXTINPUT_HPP_INCLUDED
