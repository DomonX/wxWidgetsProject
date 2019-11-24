#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include "wx/treectrl.h"
#include "../../Core/Component/controlComponent.hpp"

class Tree: public ControlComponent<wxTreeCtrl> {
    Tree(wxWindow * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxTreeCtrl(ownerWindow, elementID, _(label), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("TODO"));
    }

    void handleEvent(Event * event) {
        ControlComponent::handleEvent(event);
    }
};

#endif // TREE_HPP_INCLUDED
