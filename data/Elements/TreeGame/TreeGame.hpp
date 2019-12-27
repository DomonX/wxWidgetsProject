#ifndef TREEGAME_HPP_INCLUDED
#define TREEGAME_HPP_INCLUDED

class TreeGame: public Tree {
public:
    TreeGame(wxWindow * parent, string componentID, string label): Tree(parent, componentID, label) {}
    void handleEvent(Event * event) {
        Tree::handleEvent(event);
    }
    TreeItemBaseXml * buildItem(XmlParserResult * result) {
        return new TreeItemGameXml(result);
    }
    string prepareElement(TreeItemBaseXml * item) {
        string data = Tree::prepareElement(item);
        TreeItemGameXml * gameItem = dynamic_cast<TreeItemGameXml *>(item);
        if(!item) {
            return data;
        }
        data += "<type>";
        data += gameItem->type;
        data += "</type>";
        return data;
    }
};

#endif // TREEGAME_HPP_INCLUDED
