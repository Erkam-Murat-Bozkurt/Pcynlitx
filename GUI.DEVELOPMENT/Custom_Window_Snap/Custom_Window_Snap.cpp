
#include "Custom_Window_Snap.h"

Custom_Window_Snap::Custom_Window_Snap(wxPanel * parent, wxPoint position, wxSize window_size) :

     wxWindow(parent, wxID_ANY,position,window_size)
{
    this->Memory_Delete_Condition = false;

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->SetExtraStyle(wxFULL_REPAINT_ON_RESIZE);

    this->SetDoubleBuffered(true);

    this->SetSize(window_size);

    this->SetMinSize(window_size);

    this->page_close_icon = new wxBitmap(wxT("$SNAP/usr/share/Pcynlitx/icons/pane_close_icon.png"),

                      wxBITMAP_TYPE_ANY);

    this->Position = position;

    this->tab_ctrl_hight = 0;

    this->SetBackgroundColour(wxColour(240,240,240));

    this->SetPosition(this->Position);

    this->paintNow();
}

Custom_Window_Snap::~Custom_Window_Snap()
{
     if(!this->Memory_Delete_Condition)
     {
         this->Memory_Delete_Condition = true;

         this->page_close_icon->~wxBitmap();
     }
}

void Custom_Window_Snap::paintEvent(wxPaintEvent & event)
{
     event.Skip(true);

     wxPaintDC dc(this);

     this->render(dc);
}

void Custom_Window_Snap::paintNow()
{
    wxClientDC dc(this);

    this->render(dc);
}

void Custom_Window_Snap::render(wxDC & dc)
{
    wxRect rect(this->GetSize());

    dc.SetBrush(wxColour(240,240,240));

    dc.DrawRectangle(rect.GetX()-1, rect.GetY()-1, rect.GetWidth()+5,rect.GetHeight()+15);
}

void Custom_Window_Snap::Receive_Button_ID(int button_id){

     this->Button_ID = button_id;
}

void Custom_Window_Snap::Receive_Tab_ctrl_Hight(int hight){

     this->tab_ctrl_hight = hight;
}
