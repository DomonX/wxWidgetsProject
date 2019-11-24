/***************************************************************
 * Name:      EncyklopediaGierMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Nortof B¹ñk ()
 * Created:   2019-11-07
 * Copyright: Nortof B¹ñk ()
 * License:
 **************************************************************/

#include "EncyklopediaGierMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(EncyklopediaGierFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(EncyklopediaGierFrame)
//*)

BEGIN_EVENT_TABLE(EncyklopediaGierFrame,wxFrame)
    //(*EventTable(EncyklopediaGierFrame)
    //*)
END_EVENT_TABLE()

EncyklopediaGierFrame::EncyklopediaGierFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(EncyklopediaGierFrame)
    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(216,210));
    //*)
    this->main = new appComponent(this, "AppComponent", 3);
}

EncyklopediaGierFrame::~EncyklopediaGierFrame()
{
    //(*Destroy(EncyklopediaGierFrame)
    //*)
}

void EncyklopediaGierFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void EncyklopediaGierFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}
