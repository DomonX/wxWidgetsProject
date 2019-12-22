/***************************************************************
 * Name:      EncyklopediaGierMain.h
 * Purpose:   Defines Application Frame
 * Author:    Nortof B¹ñk ()
 * Created:   2019-11-07
 * Copyright: Nortof B¹ñk ()
 * License:
 **************************************************************/

#ifndef ENCYKLOPEDIAGIERMAIN_H
#define ENCYKLOPEDIAGIERMAIN_H

//(*Headers(EncyklopediaGierFrame)
#include <wx/frame.h>
//*)
#include "data/Elements/AppComponent/appComponent.hpp"


class EncyklopediaGierFrame: public wxFrame
{
    public:

        EncyklopediaGierFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~EncyklopediaGierFrame();
        appComponent * main;

    private:

        //(*Handlers(EncyklopediaGierFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTreeCtrl1BeginDrag(wxTreeEvent& event);
        void OnTreeCtrl1ItemActivated(wxTreeEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        //*)

        //(*Identifiers(EncyklopediaGierFrame)
        //*)

        //(*Declarations(EncyklopediaGierFrame)
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // ENCYKLOPEDIAGIERMAIN_H
