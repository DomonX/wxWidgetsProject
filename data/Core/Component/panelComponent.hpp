#ifndef PANELCOMPONENT_HPP_INCLUDED
#define PANELCOMPONENT_HPP_INCLUDED

#include <wx/panel.h>
#include <wx/scrolwin.h>

class PanelComponent : public VisualComponent {
public:
    wxScrolledWindow * elementRef;
    long elementID;
    PanelComponent(wxWindow * ownerWindow, string componentID) : VisualComponent(componentID) {
        this->ownerWindow = ownerWindow;
        elementID = wxNewId();
        elementRef = new wxScrolledWindow(this->ownerWindow, elementID, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, componentID);
        view = new View(this->elementRef,1);
        prepareChildren();
        this->elementRef->SetScrollRate(5, 5);
        refreshPanel();
    }
    void handleEvent(Event * event) {
        VisualComponent::handleEvent(event);
    }
    void prepareChildren() {}
    void refreshPanel() {
        elementRef->SetSizer(view->sizer);
        view->sizer->Fit(elementRef);
        view->sizer->SetSizeHints(elementRef);
    }
};

#endif // PANELCOMPONENT_HPP_INCLUDED
