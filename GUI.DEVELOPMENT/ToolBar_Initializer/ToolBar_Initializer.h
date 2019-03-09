
#ifndef TOOLBAR_INITIALIZER_H
#define TOOLBAR_INITIALIZER_H

#include "Event_ID_Numbers.h"
#include <wx/aui/framemanager.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/aui/dockart.h>
#include <wx/bitmap.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include <iostream>
#include "Custom_DockArt.h"

class MyAuiTBArt : public wxAuiDefaultToolBarArt
{
public:
    MyAuiTBArt() {}
    virtual ~MyAuiTBArt() {}

    // This one is important, without it, it wont work
    wxAuiToolBarArt * Clone() {

        return new MyAuiTBArt(*this);
    }

    virtual void DrawPlainBackground(wxDC& dc, wxWindow *  WXUNUSED(wnd), const wxRect& _rect) {

      wxRect rect = _rect;

      rect.height++;

      dc.SetBrush(wxColor(130,130,130));

      dc.DrawRectangle(rect.GetX() - 1, rect.GetY() - 1, rect.GetWidth() + 2, rect.GetHeight() + 1);
    }
};

class ToolBar_Initializer
{
public:
  ToolBar_Initializer();
  virtual ~ ToolBar_Initializer();
  void Initialize_ToolBar(wxFrame * Frame_Pointer, wxAuiDockArt * Dock_Art_Pointer, wxAuiManager * Interface_Manager);
  wxAuiToolBar * Get_ToolBar_Pointer();
  wxAuiToolBar * toolBar;
};

#endif /* TOOLBAR_INITIALIZER_H */
