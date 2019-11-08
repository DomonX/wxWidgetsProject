/***************************************************************
 * Name:      EncyklopediaGierApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Nortof Bąńk ()
 * Created:   2019-11-07
 * Copyright: Nortof Bąńk ()
 * License:
 **************************************************************/

#include "EncyklopediaGierApp.h"

//(*AppHeaders
#include "EncyklopediaGierMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(EncyklopediaGierApp);

bool EncyklopediaGierApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	EncyklopediaGierFrame* Frame = new EncyklopediaGierFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
