#ifndef TREEPAGEADDER_HPP_INCLUDED
#define TREEPAGEADDER_HPP_INCLUDED

class treePageAdder : public VisualComponent {
public:
    treePageAdder(wxWindow * parent, string componentID, int viewWidth) : VisualComponent(parent, componentID, viewWidth) {
        prepareChildren();
    }
    TextInput * textElement;
    Button * buttonElement;
    void prepareChildren() {
        textElement = new TextInput(this->ownerWindow, "Page Title", "");
        textElement->connect(this);
        buttonElement = new Button(this->ownerWindow, "Submit", "Add Page");
        buttonElement->connect(this);
    }
    void handleEvent(Event * event) {
        if(event->eventType == "onClick" && event->path.at(0) == "Submit") {
            sendAddPage(event);
            deleteEvent(event);
            return;
        }
        VisualComponent::handleEvent(event);
    }
    void sendAddPage(Event * event) {
        Event * ev = new Event("onAddPage", event->caller);
        handleEvent(ev);
    }

};

#endif // TREEPAGEADDER_HPP_INCLUDED
