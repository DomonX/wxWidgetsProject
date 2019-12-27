#ifndef TREEITEMBASE_XML_HPP_INCLUDED
#define TREEITEMBASE_XML_HPP_INCLUDED

class TreeItemBaseXml {
public:
    virtual ~TreeItemBaseXml() = default;
    string label;
    string id;
    string link;
    TreeItemBaseXml(XmlParserResult * source) {
        XmlParserResult * label = source->lookFor("label");
        if(label) {
            this->label = label->data;
        }
        XmlParserResult * link = source->lookFor("link");
        if(link) {
            this->link = link->data;
        }
        XmlParserResult * id = source->lookFor("id");
        if(id) {
            this->id = id->data;
        }
    }
    TreeItemBaseXml() {
        label = "";
        link = "";
        id = "";
    }
};

#endif // TREEITEMBASE_XML_HPP_INCLUDED
