#ifndef XMLPARSERRESULT_HPP_INCLUDED
#define XMLPARSERRESULT_HPP_INCLUDED

class XmlParserResult
{
public:
    string selector;
    string data;
    vector<XmlParserResult *> children;
    bool isGroup;
    XmlParserResult(string selector, string data) {
        this->selector = selector;
        this->data = data;
        this->isGroup = false;
    }
    XmlParserResult * lookFor(string selector) {
        vector<XmlParserResult *>::iterator it;
        for(it = children.begin(); it != children.end(); it++) {
            if((*it)->selector == selector) {
                return (*it);
            }
        }
        return NULL;
    }
};

#endif // XMLPARSERRESULT_HPP_INCLUDED
