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
protected:
    void beforeRender() {
        items.clear();
    }
    void renderVisible() {
        map<string, TreeItemBaseXml *>::iterator it;
        for(it = visibleItems.begin(); it != visibleItems.end(); it++) {
            elementRef->AppendItem(elementRef->GetRootItem(), it->second->label);
        }
    }
    void showAllItems() {
        map<string, TreeItemBaseXml *>::iterator it;
        for(it = items.begin(); it != items.end(); it++) {
            visibleItems[it->first] = items[it->first];
        }
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
    void sendItemClick(wxTreeEvent& event) {
        Event * ev = new Event("onTreeItemClick", &event);
        processEvent(ev);
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
    virtual TreeItemBaseXml * buildItem(XmlParserResult * result) {
        return new TreeItemBaseXml(result);
    }
    void renderControl(XmlParserResult * result) {
        if(result->selector == "treeItem") {
            TreeItemBaseXml * temp = buildItem(result);
            addItem(temp);
        }
    }
public:
    map<string, TreeItemBaseXml *> visibleItems;
    map<string, TreeItemBaseXml *> items;
    vector<string> filterKeys;
    string searchKey;


    Tree(wxWindow * parent, string componentID, string label): ControlComponent(parent, componentID) {
        elementRef = new wxTreeCtrl(ownerWindow, elementID, wxDefaultPosition, wxSize(200,200), wxTR_DEFAULT_STYLE, wxDefaultValidator, componentID);
        elementRef->AddRoot(label);
        elementRef->Bind(wxEVT_COMMAND_TREE_ITEM_ACTIVATED, &sendItemClick, this);
    }

    void addItem(TreeItemBaseXml * newItem) {
        if(items.find(newItem->id) != items.end()) {
            return;
        }
        items[newItem->id] = newItem;
        elementRef->AppendItem(elementRef->GetRootItem(), newItem->label);
        elementRef->Expand(elementRef->GetRootItem());
    }

    void applyFilter() {
        if(filterKeys.size() == 0) {
            return;
        }
        map<string, TreeItemBaseXml *>::iterator it;
        map<string, TreeItemBaseXml *> filteredItems;
        for(it = visibleItems.begin(); it != visibleItems.end(); it++) {
            vector<string>::iterator it2;
            for(it2 = filterKeys.begin(); it2 != filterKeys.end(); it2++) {
                if(!checkFilter((*it2), it->second )) {
                    continue;
                }
                filteredItems[it->first] = it->second;
            }
        }
        visibleItems = filteredItems;
    }

    virtual bool checkFilter(string key, TreeItemBaseXml * item) {
        return true;
    }

    void filter(vector<string> filterKeys) {
        this->filterKeys = filterKeys;
        reloadTree();
    }

    void clearTree() {
        visibleItems.clear();
        elementRef->DeleteChildren(elementRef->GetRootItem());
    }

    void applySearch() {
        if(searchKey.length() == 0) {
            showAllItems();
            return;
        }
        map<string, TreeItemBaseXml *>::iterator it;
        for(it = items.begin(); it != items.end(); it++) {
            if(it->second->label.find(searchKey)!= std::string::npos) {
                visibleItems[it->first] = items[it->first];
            }
        }
    }

    void reloadTree() {
        clearTree();
        applySearch();
        applyFilter();
        renderVisible();
    }

    void search(string key) {
        this->searchKey = key;
        reloadTree();
    }

    string getSelectedItemID() {
        wxString wxStringId = elementRef->GetItemText(elementRef->GetFocusedItem());
        return wxStringToString(wxStringId);
    }
};

#endif // TREE_HPP_INCLUDED
