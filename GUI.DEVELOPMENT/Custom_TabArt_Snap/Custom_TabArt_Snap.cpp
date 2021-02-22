

/*

Copyright ©  2021,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/


#include "Custom_TabArt_Snap.h"


 Custom_TabArt_Snap::Custom_TabArt_Snap() : wxAuiDefaultTabArt()
 {
    wxString snap_dir = wxT("");

    char * path =  getenv ("SNAP");

    size_t path_size = strlen(path);

    for(size_t i=0;i<path_size;i++){

        snap_dir.append(1,path[i]);
    }

    wxString icons_dir = snap_dir + wxT("/usr/share/icons/");

    wxString icon_path = icons_dir + wxT("close_tab.png");


    wxMessageOutput::Get()->Printf("icon_path, %s",icon_path);


    this->page_close_icon = new wxBitmap(icon_path,

                             wxBITMAP_TYPE_ANY);

    this->m_tabCtrlHeight = 46;
 }

 wxAuiTabArt * Custom_TabArt_Snap::Clone() {

       Custom_TabArt_Snap * TabArt_Pointer = new Custom_TabArt_Snap();

       return TabArt_Pointer;
 }

 Custom_TabArt_Snap::~Custom_TabArt_Snap(){

      this->page_close_icon->~wxBitmap();
 }

 void Custom_TabArt_Snap::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect & rect) {

      dc.SetBrush(wxColour(240,240,240));

      dc.DrawRectangle(rect.GetX()-1, rect.GetY()-1,rect.GetWidth()+2,rect.GetHeight()+2);
 }

 void Custom_TabArt_Snap::DrawTab(wxDC & dc, wxWindow *wnd, const wxAuiNotebookPage &page,

                 const wxRect & in_rect, int close_button_state,

                 wxRect *out_tab_rect, wxRect * out_button_rect, int * x_extent)
 {

        wxCoord normal_textx, normal_texty;

        wxCoord selected_textx, selected_texty;

        wxCoord texty;

        wxString caption = page.caption;

        wxFont tab_font(12,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,

                             wxFONTWEIGHT_NORMAL,false,"Liberation Sans");

        dc.SetFont(tab_font);

        dc.GetTextExtent(caption, &selected_textx, &selected_texty);

        dc.SetFont(tab_font);

        dc.GetTextExtent(caption, &normal_textx, &normal_texty);

        // figure out the size of the tab
        wxSize tab_size =  GetTabSize(dc,wnd,page.caption,page.bitmap,

                                     page.active,close_button_state,x_extent);


        wxString draw_text = page.caption;

        wxSize Text_Extend = dc.GetTextExtent(draw_text);


        wxCoord tab_height = 0 ;

        wxCoord tab_width = 0;

        wxCoord tab_x = 0;

        wxCoord tab_y = 0;

        if (page.active){

             tab_height = tab_size.y+10;

             tab_width  = tab_size.x-1;

             tab_x = in_rect.x+1;

             tab_y = in_rect.y+10;

             if(tab_width < Text_Extend.x + 10){

                tab_width = Text_Extend.x + 10;
             }
        }
        else{

              tab_height = tab_size.y+10;

              tab_width  = tab_size.x-1;

              tab_x = in_rect.x+1;

              tab_y = in_rect.y+10;

              if(tab_width < Text_Extend.x + 10){

                 tab_width = Text_Extend.x + 10;
              }
        }


        if (page.active)
        {
            dc.SetFont(tab_font);

            texty = selected_texty;
        }
        else
        {
               dc.SetFont(tab_font);

               texty = normal_texty;
        }


        wxPoint border_points[6];

        if (page.active)
        {
             // draw active tab

             // draw base background color

            wxRect r(tab_x+2, tab_y, tab_width,tab_height);

            dc.SetPen(wxPen(wxColour(200,100,100)));

            dc.SetBrush(wxBrush(wxColour(200,100,100)));

            // DrawRectangle member function: The first two parameters indicate the coordinates
            // of the top left corner of the rectangle

            dc.DrawRectangle(r.x, r.y, r.width, r.height);



            border_points[0] = wxPoint(r.x,tab_y+tab_height+18); // left bottom corner

            border_points[1] = wxPoint(r.x,tab_y+10);

            border_points[2] = wxPoint(r.x,tab_y); // left top corner

            border_points[3] = wxPoint(r.x+r.width-1,tab_y); // Right top corner

            border_points[4] = wxPoint(r.x+r.width-1,tab_y+10);

            border_points[5] = wxPoint(r.x+r.width-1,tab_y+tab_height+18); // Right bottom corner


            dc.SetPen(wxPen(wxColour(200,110,110)));

            dc.SetBrush(wxColour(200,100,100));

            dc.DrawPolygon(WXSIZEOF(border_points), border_points);
       }
       else{

              // draw inactive tab

              wxRect r(tab_x+2,tab_y,tab_width, tab_height);

              dc.SetPen(wxPen(wxColour(200,200,200)));

              dc.SetBrush(wxBrush(wxColour(200,200,200)));

              // DrawRectangle member function: The first two parameters indicate the coordinates
              // of the top left corner of the rectangle

              dc.DrawRectangle(r.x, r.y, r.width, r.height);


              border_points[0] = wxPoint(r.x,tab_y+tab_height+20); // left bottom corner

              border_points[1] = wxPoint(r.x,tab_y+10);

              border_points[2] = wxPoint(r.x,tab_y);  // left top corner

              border_points[3] = wxPoint(r.x+r.width-1,tab_y); // right top corner

              border_points[4] = wxPoint(r.x+r.width-1,tab_y+10);

              border_points[5] = wxPoint(r.x+r.width-1,tab_y+tab_height+20); // right bottom corner

              dc.SetPen(wxPen(wxColour(180,180,180)));

              dc.SetBrush(wxColour(200,200,200));

              dc.DrawPolygon(WXSIZEOF(border_points), border_points);
       }

       // draw close button if necessary
       if (close_button_state != wxAUI_BUTTON_STATE_HIDDEN)
       {
           wxBitmap bmp;
           if (page.active)

               bmp = *this->page_close_icon;

           else
               bmp = m_disabledCloseBmp;

           wxRect rect(tab_x + tab_width - bmp.GetScaledWidth()-4,
                       tab_y + (tab_height/2) - (bmp.GetScaledHeight()/2) - 3,
                       bmp.GetScaledWidth(),
                       tab_height - 1);
           DrawButtons(dc,wxSize(1, 1), rect, bmp, *wxWHITE, close_button_state);

           *out_button_rect = rect;
       }


       //wxSize Text_Extend = dc.GetTextExtent(draw_text);


       int text_offset = 0;

       if(page.active){

           text_offset = tab_x + (tab_width - Text_Extend.x)/2 - 8;
       }
       else{

           text_offset = tab_x + (tab_width - Text_Extend.x)/2+2;

       }

       // set minimum text offset

       if(page.active){

           dc.SetTextForeground(wxColour(240,240,240));
       }
       else{

             dc.SetTextForeground(wxColour(70,70,70));
       }


       dc.DrawText(draw_text,
             text_offset,
             (tab_y + tab_height)/2 - (texty/2) + 7);

       *out_tab_rect = wxRect(tab_x, tab_y, tab_width,tab_height+14);
 }



 void Custom_TabArt_Snap::DrawButtons(wxDC& dc, const wxSize& offset,const wxRect& _rect,

                            const wxBitmap& bmp, const wxColour& bkcolour, int button_state)
  {
        wxRect rect = _rect;

        if (button_state == wxAUI_BUTTON_STATE_PRESSED)
        {
            rect.x += offset.x;
            rect.y += offset.y;
        }

        if (button_state == wxAUI_BUTTON_STATE_HOVER ||
            button_state == wxAUI_BUTTON_STATE_PRESSED)
        {
            dc.SetBrush(wxBrush(bkcolour.ChangeLightness(120)));
            dc.SetPen(wxPen(bkcolour.ChangeLightness(75)));

            // draw the background behind the button
            dc.DrawRectangle(rect.x, rect.y+7, bmp.GetScaledWidth()-offset.x-2,

                 bmp.GetScaledHeight()-offset.y);
        }

        // draw the button itself
        dc.DrawBitmap(bmp, rect.x, rect.y+6, true);
 }



 void Custom_TabArt_Snap::DrawButton(wxDC& dc,wxWindow* wnd,const wxRect& in_rect,

                    int bitmap_id,int button_state,int orientation, wxRect* out_rect)
 {

      wxBitmap bmp;
      wxRect rect;

      switch (bitmap_id)
      {
          case wxAUI_BUTTON_CLOSE:
              if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                  bmp = m_disabledCloseBmp;
              else
                  bmp = m_activeCloseBmp;
              break;

          case wxAUI_BUTTON_LEFT:
              if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                  bmp = m_disabledLeftBmp;
              else
                  bmp = m_activeLeftBmp;
              break;

          case wxAUI_BUTTON_RIGHT:
              if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                  bmp = m_disabledRightBmp;
              else
                  bmp = m_activeRightBmp;
              break;

          case wxAUI_BUTTON_WINDOWLIST:
              if (button_state & wxAUI_BUTTON_STATE_DISABLED)
                  bmp = m_disabledWindowListBmp;
              else
                  bmp = m_activeWindowListBmp;
              break;
      }

      if (!bmp.IsOk())
          return;

      rect = in_rect;

      if (orientation == wxLEFT)
      {
          rect.SetX(in_rect.x);
          rect.SetY(((in_rect.y + in_rect.height)/2) - (bmp.GetScaledHeight()/2)-2);
          rect.SetWidth(bmp.GetScaledWidth());
          rect.SetHeight(bmp.GetScaledHeight());
      }
      else
      {
          rect = wxRect(in_rect.x + in_rect.width - bmp.GetScaledWidth(),
                      ((in_rect.y + in_rect.height)/2) - (bmp.GetScaledHeight()/2)-2,
                      bmp.GetScaledWidth(), bmp.GetScaledHeight());
      }


      this->DrawButtons(dc,wxSize(1,1), rect, bmp, *wxWHITE, button_state);

      *out_rect = rect;
 };
