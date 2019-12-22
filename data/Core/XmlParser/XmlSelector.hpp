#ifndef XMLSELECTOR_HPP_INCLUDED
#define XMLSELECTOR_HPP_INCLUDED

using namespace std;

class XmlSelector {
public:
    string baseSelector;
    string beginSelector;
    string endSelector;

    XmlSelector(string baseSelector) {
        this->baseSelector = baseSelector;
        beginSelector = "<" + baseSelector + ">";
        endSelector = "</" + baseSelector + ">";
    }
};

#endif // XMLSELECTOR_HPP_INCLUDED
