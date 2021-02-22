


#ifndef CUSTOM_TABART_SNAP_H
#define CUSTOM_TABART_SNAP_H

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/dockart.h>
#include <wx/event.h>
#include <wx/font.h>
#include <wx/fontdata.h>
#include <wx/fontdlg.h>
#include <wx/msgout.h>
#include <stdlib.h>


// Custom TabArt decleration .........

class Custom_TabArt_Snap : public wxAuiDefaultTabArt
{
public:

  Custom_TabArt_Snap();

  wxAuiTabArt * Clone();

  virtual ~Custom_TabArt_Snap();

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect & _rect);

  void DrawTab(wxDC & dc, wxWindow *wnd, const wxAuiNotebookPage & page,

               const wxRect & in_rect, int close_button_state,

               wxRect *out_tab_rect, wxRect * out_button_rect,

               int * x_extent);

  static void DrawButtons(wxDC& dc,const wxSize & offset,const wxRect & _rect,

                          const wxBitmap & bmp,const wxColour & bkcolour, int button_state);

  void DrawButton(wxDC & dc,wxWindow* wnd,const wxRect & in_rect,

                    int bitmap_id,int button_state,int orientation, wxRect* out_rect);

  wxBitmap * page_close_icon;
};

#endif /* CUSTOM_TABART_SNAP_H */
