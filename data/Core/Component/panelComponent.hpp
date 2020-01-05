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
        elementRef = new wxScrolledWindow(this->ownerWindow, elementID, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL || wxDEFAULT_FRAME_STYLE, componentID);
        view = new View(this->elementRef,1);
        prepareChildren();
        this->elementRef->SetScrollRate(5, 5);
        refreshPanel();
    }
    void prepareChildren() {}
    void refreshPanel() {
        elementRef->SetSizer(view->sizer);
        this->view->sizer->FitInside(elementRef);
        elementRef->Layout();
    }
};

#endif // PANELCOMPONENT_HPP_INCLUDED
