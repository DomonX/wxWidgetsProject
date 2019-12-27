#ifndef XMLPARSERRESULT_HPP_INCLUDED
#define XMLPARSERRESULT_HPP_INCLUDED

class XmlParserResult
{
public:
    string selector;
    string data;
    XmlParserResult(string selector, string data) {
        this->selector = selector;
        this->data = data;
    }
};

#endif // XMLPARSERRESULT_HPP_INCLUDED
