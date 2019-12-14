#include "wxStringToString.hpp"
string wxStringToString(wxString src) {
    const char * constCharVal = src.mb_str();
    return string(constCharVal);
}
