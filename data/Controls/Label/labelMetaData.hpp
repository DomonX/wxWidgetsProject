#ifndef LABELMETADATA_HPP_INCLUDED
#define LABELMETADATA_HPP_INCLUDED

class LabelMetaData {
public:
    LabelMetaData() {
        parent = NULL;
        componentID = "";
        label = "";
        width = -1;
        height = -1;
    }
    wxWindow * parent;
    string componentID;
    string label;
    int width;
    int height;
};

#endif // LABELMETADATA_HPP_INCLUDED
