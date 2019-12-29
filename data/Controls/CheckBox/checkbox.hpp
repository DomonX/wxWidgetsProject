#ifndef CHECKBOX_HPP_INCLUDED
#define CHECKBOX_HPP_INCLUDED

#include <wx/checkbox.h>

class Checkbox : public ControlComponent<wxCheckBox> {
protected:
    void handleEvent(Event * event) {
        ControlComponent::handleEvent(event);
    }
public:
    Checkbox(wxWindow * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxCheckBox(ownerWindow, elementID, _(label), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, componentID);
    }
    bool getValue() {
        return elementRef->GetValue();
    }
};

#endif // CHECKBOX_HPP_INCLUDED
