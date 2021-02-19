
#ifndef TOOLBAR_INITIALIZER_SNAP_H
#define TOOLBAR_INITIALIZER_SNAP_H

#include <wx/wx.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/aui/dockart.h>
#include <wx/bitmap.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include <iostream>
#include <stdlib.h>
#include "Event_ID_Numbers.h"
#include "Custom_DockArt.h"

class MyAuiTBArt : public wxAuiDefaultToolBarArt
{
public:
    MyAuiTBArt() {}
    virtual ~MyAuiTBArt(){

    }

    // This one is important, without it, it wont work
    wxAuiToolBarArt * Clone() {

        return new MyAuiTBArt(*this);
    }

    virtual void DrawPlainBackground(wxDC& dc, wxWindow * wnd, const wxRect& _rect) {

      wxRect rect = _rect;

      rect.height++;

      dc.SetBrush(wxColour(185,185,185));

      dc.DrawRectangle(rect.GetX() - 1, rect.GetY() - 1,

            rect.GetWidth() + 2, rect.GetHeight() + 1);
    }
};

class ToolBar_Initializer_Snap
{
public:
  ToolBar_Initializer_Snap();
  virtual ~ ToolBar_Initializer_Snap();
  void Initialize_ToolBar(wxFrame * Frame_Pointer,
       wxAuiDockArt * Dock_Art_Pointer,
       wxAuiManager * Interface_Manager);
  wxAuiToolBar * Get_ToolBar_Pointer();
  void Determine_Snap_Dir();
  wxAuiToolBar * toolBar;
  wxAuiToolBarArt * Art_Pointer;
  wxWindowDC * WinDc;
  wxBitmap * close;
  wxBitmap * build_library;
  wxBitmap * build_executable;
  wxBitmap * Select_Project_File;
  wxBitmap * Empty_Project_File;
  wxBitmap * Show_Help_Document;
  wxBitmap * open_terminal;
  wxBitmap * file_save;
  wxBitmap * open_tree_view;
  wxBitmap * print_descriptions;
  wxString snap_dir;
};

#endif /* TOOLBAR_INITIALIZER_SNAP_H */
