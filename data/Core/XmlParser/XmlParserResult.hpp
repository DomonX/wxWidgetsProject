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
};

#endif // XMLPARSERRESULT_HPP_INCLUDED
