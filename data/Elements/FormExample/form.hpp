#ifndef FORM_HPP_INCLUDED
#define FORM_HPP_INCLUDED

class Form : public VisualComponent {
public:
    Form(VisualComponent * parent, string componentID, int viewWidth) : VisualComponent(parent, componentID, viewWidth) {
        prepareChildren();
    }

    void prepareChildren() {
        TextInput * txt1 = new TextInput(this, "txt1", "test");
        txt1->connectControl(this);
        TextInput * txt2 = new TextInput(this, "txt2", "test2");
        txt2->connectControl(this);
        TextInput * txt3 = new TextInput(this, "txt3", "test3");
        txt3->connectControl(this);
        TextInput * txt4 = new TextInput(this, "txt4", "test4");
        txt4->connectControl(this);
    }

};

#endif // FORM_HPP_INCLUDED