#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include <wx/treectrl.h>
#include "../../Core/Component/controlComponent.hpp"
#include <algorithm>
#include "../../Util/wxStringToString.hpp"
#include "../../Core/XmlFileManager/XmlFileManager.hpp"
#include "../../Core/Component/dataComponent.hpp"
#include "../../XMLModels/TreeItemBase.xml.hpp"
class Tree: public ControlComponent<wxTreeCtrl>, public DataComponent {
public:
    map<string, TreeItemBaseXml *> items;
    map<string, TreeItemBaseXml *> visibleItems;
    Tree(wxWindow * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxTreeCtrl(ownerWindow, elementID, wxDefaultPosition, wxSize(200,200), wxTR_DEFAULT_STYLE, wxDefaultValidator, componentID);
        elementRef->AddRoot(label);
        elementRef->Bind(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, &sendItemClick, this);
    }
    void beforeRender() {
        items.clear();
    }
    void renderControl(XmlParserResult * result) {
        if(result->selector == "treeItem") {
            TreeItemBaseXml * temp = buildItem(result);
            addItem(temp);
        }
    }
    void addItem(TreeItemBaseXml * newItem) {
        if(items.find(newItem->id) != items.end()) {
            return;
        }
        items[newItem->id] = newItem;
        elementRef->AppendItem(elementRef->GetRootItem(), newItem->label);
        elementRef->Expand(elementRef->GetRootItem());
    }
    virtual TreeItemBaseXml * buildItem(XmlParserResult * result) {
        return new TreeItemBaseXml(result);
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
        map<string, TreeItemBaseXml *>::iterator it;
        for(it = items.begin(); it != items.end(); it++) {
            if(it->second->label.find(key)!= std::string::npos) {
                visibleItems[it->first] = items[it->first];
            }
        }
        showFilteredItems();
    }
    void showFilteredItems() {
        map<string, TreeItemBaseXml *>::iterator it;
        for(it = visibleItems.begin(); it != visibleItems.end(); it++) {
            elementRef->AppendItem(elementRef->GetRootItem(), it->second->label);
        }
    }
    void showAllItems() {
        map<string, TreeItemBaseXml *>::iterator it;
        for(it = items.begin(); it != items.end(); it++) {
            elementRef->AppendItem(elementRef->GetRootItem(), it->second->label);
        }
    }
    string getSelectedItemID() {
        wxString wxStringId = elementRef->GetItemText(elementRef->GetFocusedItem());
        return wxStringToString(wxStringId);
    }
    void handleEvent(Event * event) {
        ControlComponent::handleEvent(event);
    }
    virtual string prepareElement(TreeItemBaseXml * item) {
        string data = "";
        data += "<label>";
        data += item->label;
        data += "</label>";
        data += "<id>";
        data += item->id;
        data += "</id>";
        data += "<link>";
        data += item->link;
        data += "</link>";
        return data;
    }
    vector<XmlParserResult *> prepareDataToSave() {
        vector<XmlParserResult *> result;
        map<string,TreeItemBaseXml *>::iterator it;
        for(it = items.begin(); it != items.end(); it++) {
            string data = prepareElement(it->second);
            XmlParserResult * temp = new XmlParserResult("treeItem", data);
            result.push_back(temp);
        }
        return result;
    }
};

#endif // TREE_HPP_INCLUDED
