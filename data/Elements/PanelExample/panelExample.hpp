#ifndef PANELEXAMPLE_HPP_INCLUDED
#define PANELEXAMPLE_HPP_INCLUDED

class PanelExample : public PanelComponent {
public:
    PanelExample(wxWindow * parent, string componentID) : PanelComponent(parent, componentID) {
        prepareChildren();
    }
    void prepareChildren() {
        Button * btn6 = new Button(this->elementRef, "test6", "Destroy Button 5");
        btn6->connect(this);
    }
};

#endif // PANELEXAMPLE_HPP_INCLUDED
