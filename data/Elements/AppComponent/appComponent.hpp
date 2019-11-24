#ifndef APPCOMPONENT_HPP_INCLUDED
#define APPCOMPONENT_HPP_INCLUDED
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Controls/Button/button.hpp"
#include "../../Controls/Label/label.hpp"
#include "../../Core/Event/event.hpp"
#include "../../Controls/TextInput/textInput.hpp"
#include "../FormExample/form.hpp"
#include "../../Controls/Notebook/notebook.hpp"
#include "../PanelExample/panelExample.hpp"
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/aui/aui.h>
#include <memory>
using namespace std;
class appComponent : public VisualComponent {
public:
    appComponent(wxWindow * parentWindow, string componentID, int viewWidth) : VisualComponent(parentWindow, componentID, viewWidth) {
        prepareChildren();
        ownerWindow->SetSizer(view->grid);
        view->grid->Fit(ownerWindow);
        view->grid->SetSizeHints(ownerWindow);
    }

    void prepareChildren() {
        /*
        VisualComponent * leftMainComponent = new VisualComponent(this->ownerWindow, "leftMainComponent", 1);
        leftMainComponent->connectView(this);
        Notebook * leftNotebook = new Notebook(this->ownerWindow, "leftMenuNotebook", 200, 900);
        leftNotebook->connectControl(leftMainComponent);
        PanelComponent * testPanel1 = new PanelComponent(leftNotebook->elementRef, "testPanel");
        leftNotebook->addPage(testPanel1, "panel 1");
        PanelExample * testPanel2 = new PanelExample(leftNotebook->elementRef, "testPanel2");
        leftNotebook->addPage(testPanel2, "panel 2");
        Button * btn1 = new Button(testPanel1->elementRef, "btn1", "Button 1");
        btn1->connectControl(testPanel1);
        */

        Notebook * nt = new Notebook(this->ownerWindow, "nt", 500, 500);
        nt->connectControl(this);

        VisualComponent * cmp1 = new VisualComponent(this->ownerWindow, "cmp1", 1);
        cmp1->connectView(this);

        VisualComponent * cmp2 = new VisualComponent(this->ownerWindow, "cmp2", 1);
        cmp2->connectView(this);

        VisualComponent * cmp3 = new VisualComponent(this->ownerWindow, "cmp3", 1);
        cmp3->connectView(this);


        Button * btn1 = new Button(cmp1->ownerWindow, "test1", "Dynamically load form");
        btn1->connectControl(cmp1);

        Button * btn2 = new Button(cmp1->ownerWindow, "test2", "Change Text From Input");
        btn2->connectControl(cmp1);

        Button * btn3 = new Button(cmp2->ownerWindow, "test3", "Dynamically load page");
        btn3->connectControl(cmp2);

        Button * btn4 = new Button(cmp2->ownerWindow, "test4", "Add Button Dynamically");
        btn4->connectControl(cmp2);

        Button * btn6 = new Button(cmp2->ownerWindow, "test6", "Destroy Button 5");
        btn6->connectControl(cmp3);

        Label * lb1 = new Label(cmp2->ownerWindow, "lb1", "jakis tekst");
        lb1->connectControl(cmp2);

        TextInput * txt1 = new TextInput(cmp3->ownerWindow, "txt1", "test");
        txt1->connectControl(cmp3);

        Form * fm = new Form(this->ownerWindow, "fm1", 1);
        fm->connectView(this);

        Form * fm2 = new Form(this->ownerWindow, "fm2", 1);
        fm2->connectView(this);

    }
    /*
    void handleEvent(Event * event) {
        if(event->eventType == "onClick") {
            if(event->path.at(0) == "btn1") {
                Component * temp = getChildren("leftMainComponent.leftMenuNotebook");
                Notebook * leftNotebook = dynamic_cast<Notebook *>(temp);
                if(leftNotebook->children["testPanel3"] != NULL) return;
                PanelExample * testPanel3 = new PanelExample(leftNotebook->elementRef, "testPanel3");
                leftNotebook->addPage(testPanel3, "panel 3");
            }
        }
        if(event->eventType == "onNotebookPageClose") {
            serveNotebookPageClose(event);
        }
        VisualComponent::handleEvent(event);
    }
    */

    void handleEvent(Event * event) {
        if(event->eventType == "onClick") {
           serveClick(event);
           return;
        }
        if(event->eventType == "onNotebookPageClose") {
           serveNotebookPageClose(event);
           return;
        }
        VisualComponent::handleEvent(event);
    }
    void serveNotebookPageClose(Event * event) {
        Component * cmp = getChildren(event->stringifyPath());
        if(cmp == NULL) {
            return;
        }
        Notebook * nt = dynamic_cast<Notebook *>(cmp);
        if(!nt) {
            return;
        }
        wxAuiNotebookEvent * caller = dynamic_cast<wxAuiNotebookEvent *>(event->caller);
        int num = caller->GetSelection();
        nt->removePage(num);
        view->grid->Fit(ownerWindow);
    }
    void serveClick(Event * event) {
        if(event->path.at(0) == "test1") {
            serveClickBtn1(event);
        }
        if(event->path.at(0) == "test2") {
            serveClickBtn2(event);
        }
        if(event->path.at(0) == "test3") {
            serveClickBtn3(event);
        }
        if(event->path.at(0) == "test4") {
            serveClickBtn4(event);
        }
        if(event->path.at(0) == "test5") {
            serveClickBtn5(event);
        }
        if(event->path.at(0) == "test6") {
            serveClickBtn6(event);
        }
        deleteEvent(event);
    }

    void serveClickBtn1(Event * event) {
        if(children["fm3"] != NULL) {
            return;
        }
        Form * f3 = new Form(this->ownerWindow, "fm3", 2);
        f3->connectView(this);
        view->grid->Fit(ownerWindow);
    }

    void serveClickBtn2(Event * event) {
        wxString label = dynamic_cast<TextInput *>(children["cmp3"]->children["txt1"])->elementRef->GetLineText(0);
        dynamic_cast<Label *>(children["cmp2"]->children["lb1"])->elementRef->SetLabelText(label);
    }

    void serveClickBtn3(Event * event) {
        if(children["nt"] == NULL) {
            return;
        }
        if(getChildren("nt.pn3") != NULL) {
            return;
        }
        Notebook * nt = dynamic_cast<Notebook *>(children["nt"]);
        PanelExample * pn3 = new PanelExample(nt->elementRef, "pn3");
        nt->addPage(pn3, "Dynamically Loaded page");
        pn3->refreshPanel();
    }

    void serveClickBtn4(Event * event) {
        VisualComponent * cmp1 = dynamic_cast<VisualComponent *>(children["cmp1"]);
        if(cmp1->children["test5"] != NULL) {
            return;
        }
        Button * b = new Button(cmp1->ownerWindow, "test5", "Set Label equals to event Path");
        b->connectControl(cmp1);
        view->grid->Fit(ownerWindow);
    }

    void serveClickBtn5(Event * event) {
        string label = "";
        if(children["cmp2"]->children["lb1"] == NULL) {
            return;
        }
        label = event->stringifyPath();
        dynamic_cast<Label *>(children["cmp2"]->children["lb1"])->elementRef->SetLabelText(label);
        view->grid->Fit(ownerWindow);
    }
    void serveClickBtn6(Event * event) {
        VisualComponent * cmp1 = dynamic_cast<VisualComponent *>(children["cmp1"]);
        if(cmp1->children["test5"] == NULL) {
            return;
        }
        Component * label = getChildren("cmp2.lb1");
        dynamic_cast<Label *>(label)->elementRef->SetLabelText("Deleted Button");
        Button * btn5 = dynamic_cast<Button *>(cmp1->children["test5"]);
        btn5->deleteComponent();
        cmp1->children["test5"] = NULL;
    }
};

#endif // APPCOMPONENT_HPP_INCLUDED
