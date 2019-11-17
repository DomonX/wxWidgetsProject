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

        Notebook * nt = new Notebook(this, "nt", 500, 500);
        nt->connectControl(this);

        PanelComponent * pn = new PanelComponent("pn", nt->elementRef);
        nt->addPage(pn, "test");

        PanelComponent * pn2 = new PanelComponent("pn2", nt->elementRef);
        nt->addPage(pn2, "test2");

        VisualComponent * cmp1 = new VisualComponent(this, "cmp1", 1);
        cmp1->connectView(this);

        VisualComponent * cmp2 = new VisualComponent(this, "cmp2", 1);
        cmp2->connectView(this);

        VisualComponent * cmp3 = new VisualComponent(this, "cmp3", 1);
        cmp3->connectView(this);


        Button * btn1 = new Button(cmp1, "test1", "Dynamically load form");
        btn1->connectControl(cmp1);

        Button * btn2 = new Button(cmp1, "test2", "Change Text From Input");
        btn2->connectControl(cmp1);

        Button * btn3 = new Button(cmp2, "test3", "Dynamically load page");
        btn3->connectControl(cmp2);

        Button * btn4 = new Button(cmp2, "test4", "Add Button Dynamically");
        btn4->connectControl(cmp2);

        Button * btn6 = new Button(cmp2, "test6", "Destroy Button 5");
        btn6->connectControl(cmp3);

        Label * lb1 = new Label(cmp2, "lb1", "jakis tekst");
        lb1->connectControl(cmp2);

        TextInput * txt1 = new TextInput(cmp3, "txt1", "test");
        txt1->connectControl(cmp3);

        Form * fm = new Form(this, "fm1", 1);
        fm->connectView(this);

        Form * fm2 = new Form(this, "fm2", 1);
        fm2->connectView(this);
    }

    void serveEvent(Event * event) {
        if(event->eventType == "onClick") {
           serveClick(event);
           return;
        }
        if(event->eventType == "onNotebookPageClose") {
           serveNotebookPageClose(event);
           return;
        }
        VisualComponent::serveEvent(event);
    }
    void serveNotebookPageClose(Event * event) {
        // Przerzucic czesc funkcjonalnosci do Notebooka
        Notebook * nt = dynamic_cast<Notebook *>(getChildren(event->stringifyPath().c_str()));
        wxAuiNotebookEvent * caller = dynamic_cast<wxAuiNotebookEvent *>(event->caller);
        int num = caller->GetSelection();
        nt->removePage(num);
        dynamic_cast<Label *>(children["cmp2"]->children["lb1"])->elementRef->SetLabelText("Usunieto strone");
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
        handleEvent(event);
    }

    void serveClickBtn1(Event * event) {
        if(children["fm3"] != NULL) {
            return;
        }
        Form * f3 = new Form(this, "fm3", 2);
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
        PanelComponent * pn3 = new PanelComponent("pn3", nt->elementRef);
        nt->addPage(pn3, "Dynamically Loaded page");
    }

    void serveClickBtn4(Event * event) {
        VisualComponent * cmp1 = dynamic_cast<VisualComponent *>(children["cmp1"]);
        if(cmp1->children["test5"] != NULL) {
            return;
        }
        Button * b = new Button(cmp1, "test5", "Set Label equals to event Path");
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
