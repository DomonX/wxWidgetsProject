#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

#include <wx/statbmp.h>
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Core/Component/controlComponent.hpp"
#include "../../Core/Event/event.hpp"
class Image : public ControlComponent<wxStaticBitmap> {
public:
    Image(wxWindow * parent, string componentID, string path): ControlComponent(parent, componentID) {
        elementRef = new wxStaticBitmap(ownerWindow, elementID, wxBitmap(wxImage(path)), wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER, componentID);
    }
    void handleEvent(Event * event) {
        ControlComponent::handleEvent(event);
    }
};

#endif // IMAGE_HPP_INCLUDED
