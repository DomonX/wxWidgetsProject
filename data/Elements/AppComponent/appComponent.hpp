#ifndef APPCOMPONENT_HPP_INCLUDED
#define APPCOMPONENT_HPP_INCLUDED
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Controls/Button/button.hpp"
#include "../../Controls/Label/label.hpp"
#include "../../Core/Event/event.hpp"
#include "../../Controls/TextInput/textInput.hpp"
#include "../FormExample/form.hpp"
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <memory>
using namespace std;
class appComponent : public VisualComponent {
public:
    appComponent(wxWindow * parentWindow, string componentID, int viewWidth) : VisualComponent(parentWindow, componentID, viewWidth) {
        view->grid = new wxFlexGridSizer(0, 3, 0, 0);

        prepareChildren();
        ownerWindow->SetSizer(view->grid);
        view->grid->Fit(ownerWindow);
        view->grid->SetSizeHints(ownerWindow);
    }

    void prepareChildren() {

        VisualComponent * cmp1 = new VisualComponent(this, "cmp1", 1);
        cmp1->connectView(this);

        VisualComponent * cmp2 = new VisualComponent(this, "cmp2", 1);
        cmp2->connectView(this);

        VisualComponent * cmp3 = new VisualComponent(this, "cmp3", 1);
        cmp3->connectView(this);


        Button * btn1 = new Button(cmp1, "test1", "Do Nothing");
        btn1->connectControl(cmp1);

        Button * btn2 = new Button(cmp1, "test2", "Change Text From Input");
        btn2->connectControl(cmp1);

        Button * btn3 = new Button(cmp2, "test3", "Do Nothing");
        btn3->connectControl(cmp2);

        Button * btn4 = new Button(cmp2, "test4", "Add Button Dynamically");
        btn4->connectControl(cmp2);

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
           free(event);
           return;
        }
        VisualComponent::serveEvent(event);
    }

    void serveClick(Event * event) {
        if(event->path.at(0) == "test2") {
            serveClickBtn2(event);
        }
        if(event->path.at(0) == "test4") {
            serveClickBtn4(event);
        }
        if(event->path.at(0) == "test5") {
            serveClickBtn5(event);
        }
    }

    void serveClickBtn2(Event * event) {
        wxString label = dynamic_cast<TextInput *>(children["cmp3"]->children["txt1"])->elementRef->GetLineText(0);
        dynamic_cast<Label *>(children["cmp2"]->children["lb1"])->elementRef->SetLabelText(label);
    }

    void serveClickBtn4(Event * event) {
        VisualComponent * cmp1 = dynamic_cast<VisualComponent *>(children["cmp1"]);
        if(cmp1->children["test5"] != NULL) {
            handleEvent(event);
            return;
        }
        Button * b = new Button(cmp1, "test5", "Set Label equals to event Path");
        b->connectControl(cmp1);
        view->grid->Fit(ownerWindow);
        handleEvent(event);
    }

    void serveClickBtn5(Event * event) {
        vector<string>::iterator it;
        string label = "";
        for(it = event->path.begin(); it != event->path.end(); it++) {
            label.append((*it));
            label.append(".");
        }
        if(children["cmp2"]->children["lb1"] == NULL) {
            handleEvent(event);
            return;
        }
        dynamic_cast<Label *>(children["cmp2"]->children["lb1"])->elementRef->SetLabelText(label);
        view->grid->Fit(ownerWindow);
        handleEvent(event);
    }
};

#endif // APPCOMPONENT_HPP_INCLUDED
