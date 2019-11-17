#ifndef PANELCOMPONENT_HPP_INCLUDED
#define PANELCOMPONENT_HPP_INCLUDED
#include <wx/panel.h>
class PanelComponent : public VisualComponent {
public:
    wxPanel * elementRef;
    long elementID;
    PanelComponent(string componentID, wxWindow * ownerWindow) : VisualComponent(componentID) {
        this->ownerWindow = ownerWindow;
        view = new View(this->ownerWindow,1);
        elementID = wxNewId();
        elementRef = new wxPanel(this->ownerWindow, elementID, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
        elementRef->SetSizer(view->grid);
        view->grid->Fit(elementRef);
        view->grid->SetSizeHints(elementRef);
    }
    void serveEvent(Event * event) {
        VisualComponent::serveEvent(event);
    }
};

#endif // PANELCOMPONENT_HPP_INCLUDED
