#ifndef TREEITEMGAME_XML_HPP_INCLUDED
#define TREEITEMGAME_XML_HPP_INCLUDED

class TreeItemGameXml: public TreeItemBaseXml {
public:
    string type;
    TreeItemGameXml(XmlParserResult * source) : TreeItemBaseXml(source) {
        XmlParserResult * type = source->lookFor("type");
        if(type) {
            this->type = type->data;
        }
    }
    TreeItemGameXml(): TreeItemBaseXml() {
        type = "";
    }
};

#endif // TREEITEMGAME_XML_HPP_INCLUDED
