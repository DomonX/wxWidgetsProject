#ifndef APPCOMPONENT_HPP_INCLUDED
#define APPCOMPONENT_HPP_INCLUDED
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Controls/Button/button.hpp"
#include "../../Controls/Label/label.hpp"
#include "../../Core/Event/event.hpp"
#include "../../Controls/TextInput/textInput.hpp"
#include "../../Controls/Notebook/notebook.hpp"
#include "../GamePanel/gamePanel.hpp"
#include "../PanelExample/panelExample.hpp"
#include "../../Controls/Tree/Tree.hpp"
#include "../Treetest/treeTest.hpp"
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/aui/aui.h>
#include <memory>
using namespace std;
class appComponent : public VisualComponent {
public:

    treeTest * t1;
    Notebook * nt;

    appComponent(wxWindow * parentWindow, string componentID, int viewWidth) : VisualComponent(parentWindow, componentID, viewWidth) {
        prepareChildren();
        connectWxWindowToSizer();
    }

    void prepareChildren() {
        t1 = new treeTest(this->ownerWindow, "treetest", 1);
        t1->connect(this);

        nt = new Notebook(this->ownerWindow, "nt", 1000, 800);
        nt->connect(this);
    }

    bool handleEvent(Event * event) {
        if(event->eventType == "onTreeItemClick") {
            handleOnTreeItemClick(event);
            return true;
        }
        if(event->eventType == "onNotebookPageClose") {
            handleNotebookPageClose(event);
            return true;
        }
        return false;
    }

    void handleOnTreeItemClick(Event * event) {
        string pageID = t1->treeElement->treeElement->getSelectedItemID();
        TreeItemBaseXml * treeItem = t1->treeElement->treeElement->items[pageID];
        if(!treeItem) {
            return;
        }
        TreeItemGameXml * treeItemGame = dynamic_cast<TreeItemGameXml *>(treeItem);
        if(!treeItemGame) {
            return;
        }
        string link = treeItemGame->link;
        if(nt->pageAlreadyExists(pageID)) {
            return;
        }
        GamePanel * newPanel = new GamePanel(nt->elementRef, pageID);
        newPanel->connectData(link);
        newPanel->loadData();
        nt->addPage(newPanel, pageID);
    }

    void handleNotebookPageClose(Event * event) {
        wxAuiNotebookEvent * caller = dynamic_cast<wxAuiNotebookEvent *>(event->caller);
        int num = caller->GetSelection();
        nt->removePage(num);
        view->sizer->Fit(ownerWindow);
    }
};

#endif // APPCOMPONENT_HPP_INCLUDED
