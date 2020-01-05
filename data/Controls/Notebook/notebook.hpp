#ifndef NOTEBOOK_HPP_INCLUDED
#define NOTEBOOK_HPP_INCLUDED
#include "../../Core/Component/panelComponent.hpp"
#include "wx/aui/aui.h"
class Notebook : public ControlComponent<wxAuiNotebook> {
protected:
    void sendPageClose(wxAuiNotebookEvent& event) {
        Event * ev = new Event("onNotebookPageClose", &event);
        processEvent(ev);
    }
public:
    Notebook(wxWindow * parent, string componentID, int width, int height): ControlComponent(parent, componentID) {
        elementRef = new wxAuiNotebook(ownerWindow, elementID, wxDefaultPosition, wxSize(width,height), wxAUI_NB_DEFAULT_STYLE);
        elementRef->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE, &sendPageClose, this);
    }
    bool pageAlreadyExists(string componentID) {
        if(getChildren(componentID) != NULL) {
            return true;
        }
        return false;
    }
    void addPage(PanelComponent * newPanel, string label) {
        addChildren(newPanel);
        elementRef->AddPage(newPanel->elementRef, label);
        newPanel->refreshPanel();
    }
    string getPageComponentID(int id) {
        wxString label = elementRef->GetPage(id)->GetLabel();
        const char * labelS = label.mb_str();
        return string(labelS);
    }
    void removePage(int id) {
        string componentID = getPageComponentID(id);
        delete(children[componentID]);
        children[componentID] = NULL;
    }
};

#endif // NOTEBOOK_HPP_INCLUDED
