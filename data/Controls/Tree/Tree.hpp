#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include <wx/treectrl.h>
#include "../../Core/Component/controlComponent.hpp"
#include <algorithm>
#include "../../Util/wxStringToString.hpp"
#include "../../Core/XmlFileLoader/XmlFileLoader.h"
#include "../../Core/Component/dataComponent.hpp"
class Tree: public ControlComponent<wxTreeCtrl>, public DataComponent {
public:
    map<string, string> items;
    map<string, string> visibleItems;
    Tree(wxWindow * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxTreeCtrl(ownerWindow, elementID, wxDefaultPosition, wxSize(200,200), wxTR_DEFAULT_STYLE, wxDefaultValidator, componentID);
        elementRef->AddRoot(label);
        elementRef->Bind(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, &sendItemClick, this);
    }
    void connectSelectors() {
        dataLoader->addSelector("treeItem");
    }
    void beforeRender() {
        items.clear();
    }
    void renderControl(XmlParserResult * result) {
        if(result->selector == "treeItem") {
            addItem(result->data, result->data);
        }
    }
    void addItem(string id, string label) {
        if(items.find(id) != items.end()) {
            return;
        }
        items[id] = label;
        elementRef->AppendItem(elementRef->GetRootItem(), label);
        elementRef->Expand(elementRef->GetRootItem());
    }
    void sendItemClick(wxTreeEvent& event) {
        Event * ev = new Event("onTreeItemClick", &event);
        handleEvent(ev);
    }
    void filter(string key) {
        visibleItems.clear();
        elementRef->DeleteChildren(elementRef->GetRootItem());
        if(key.length() == 0) {
            showAllItems();
            return;
        }
        map<string, string>::iterator it;
        for(it = items.begin(); it != items.end(); it++) {
            if(it->second.find(key)!= std::string::npos) {
                visibleItems[it->first] = items[it->first];
            }
        }
        showFilteredItems();
    }
    void showFilteredItems() {
        map<string, string>::iterator it;
        for(it = visibleItems.begin(); it != visibleItems.end(); it++) {
            elementRef->AppendItem(elementRef->GetRootItem(), it->second);
        }
    }
    void showAllItems() {
        map<string, string>::iterator it;
        for(it = items.begin(); it != items.end(); it++) {
            elementRef->AppendItem(elementRef->GetRootItem(), it->second);
        }
    }
    string getSelectedItemID() {
        wxString wxStringId = elementRef->GetItemText(elementRef->GetFocusedItem());
        return wxStringToString(wxStringId);
    }
    void handleEvent(Event * event) {
        ControlComponent::handleEvent(event);
    }
};

#endif // TREE_HPP_INCLUDED
