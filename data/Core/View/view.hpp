#ifndef VIEW_HPP_INCLUDED
#define VIEW_HPP_INCLUDED

#include <wx/sizer.h>
#include <wx/window.h>

class View {
    public:
    wxFlexGridSizer * grid;
    wxWindow * parentWindow;
    View(wxWindow * parentWindow, int width) {
        this->parentWindow = parentWindow;
        grid = new wxFlexGridSizer(0, width, 0, 0);
    }
};

#endif // VIEW_HPP_INCLUDED
