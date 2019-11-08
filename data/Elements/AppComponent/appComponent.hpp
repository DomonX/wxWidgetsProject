#ifndef APPCOMPONENT_HPP_INCLUDED
#define APPCOMPONENT_HPP_INCLUDED
#include "../../Core/Component/component.hpp"
#include "../../Core/Component/visualComponent.hpp"
#include "../../Controls/Button/button.hpp"
#include "../../Controls/Label/label.hpp"
#include "../../Core/Event/event.hpp"
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

        Button * btn1 = new Button(cmp1, "test1", "test1");
        btn1->connectControl(cmp1);

        Button * btn2 = new Button(cmp1, "test2", "test2");
        btn2->connectControl(cmp1);

        Button * btn3 = new Button(cmp2, "test3", "test3");
        btn3->connectControl(cmp2);

        Button * btn4 = new Button(cmp2, "test4", "test4");
        btn4->connectControl(cmp2);

        Label * lb1 = new Label(cmp2, "lb1", "jakis tekst");
        lb1->connectControl(cmp2);
    }

    void serveEvent(Event * event) {
        if(event->eventType == "onClick") {
            vector<string>::iterator it;
            string label = "";
            for(it = event->path.begin(); it != event->path.end(); it++) {
                label.append((*it));
                label.append(".");
            }
            dynamic_cast<Label *>(children["cmp2"]->children["lb1"])->elementRef->SetLabelText(label);
            handleEvent(event);
        }
        VisualComponent::serveEvent(event);
    }
};

#endif // APPCOMPONENT_HPP_INCLUDED
