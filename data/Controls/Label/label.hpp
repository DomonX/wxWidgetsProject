#ifndef LABEL_HPP_INCLUDED
#define LABEL_HPP_INCLUDED

#include <wx/stattext.h>
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Core/Component/controlComponent.hpp"
class Label : public ControlComponent<wxStaticText> {
public:
    Label(wxWindow * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxStaticText(ownerWindow, elementID, _(label), wxDefaultPosition, wxDefaultSize, 0, componentID);
    }
    void handleEvent(Event * event) {
        ControlComponent::handleEvent(event);
    }
};

#endif // LABEL_HPP_INCLUDED
