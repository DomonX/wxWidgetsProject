#ifndef TREEGAME_HPP_INCLUDED
#define TREEGAME_HPP_INCLUDED

class TreeGame: public Tree {
protected:
    TreeItemBaseXml * buildItem(XmlParserResult * result) {
        return new TreeItemGameXml(result);
    }
    XmlParserResult * prepareElement(TreeItemBaseXml * item) {
        XmlParserResult * treeElement = Tree::prepareElement(item);
        TreeItemGameXml * gameItem = dynamic_cast<TreeItemGameXml *>(item);
        if(!item) {
            return treeElement;
        }
        treeElement->data += "<type>";
        treeElement->data += gameItem->type;
        treeElement->data += "</type>";
        XmlParserResult * type = new XmlParserResult("type", gameItem->type);
        treeElement->children.push_back(type);
        return treeElement;
    }
    virtual bool checkFilter(string key, TreeItemBaseXml * item) {
        TreeItemGameXml * gameItem = dynamic_cast<TreeItemGameXml *>(item);
        if(!gameItem) {
            return false;
        }
        return gameItem->type == key;
    }
public:
    TreeGame(wxWindow * parent, string componentID, string label): Tree(parent, componentID, label) {}
};

#endif // TREEGAME_HPP_INCLUDED
