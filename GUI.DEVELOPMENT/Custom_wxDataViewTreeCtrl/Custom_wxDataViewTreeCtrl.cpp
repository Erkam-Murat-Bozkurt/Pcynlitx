
#include "Custom_wxDataViewTreeCtrl.h"

Custom_wxDataViewTreeCtrl::Custom_wxDataViewTreeCtrl(wxWindow *parent, wxWindowID id,

  const wxPoint & pos,

  const wxSize & size, long style) : wxDataViewTreeCtrl(parent,id,pos,size,style)
  {
     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->Parent_Window_Pointer = parent;

     this->SetThemeEnabled(false);

     this->SetBackgroundColour(wxColour(250,250,250));

     this->SetEventHandler(this);

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxCLIP_CHILDREN);

     this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

     this->ClearBackground();

     this->SetMinSize(this->Parent_Window_Pointer->GetClientSize());

     this->SetSize(this->Parent_Window_Pointer->GetClientSize());

     this->Fit();

     this->Layout();

     this->CentreOnParent(wxBOTH);

     this->Update();
 }

 Custom_wxDataViewTreeCtrl::~Custom_wxDataViewTreeCtrl()
 {

 }

 void Custom_wxDataViewTreeCtrl::PaintNow(){

       wxClientDC dc(this);

       wxRect rect(this->GetSize());

       this->DrawBackground(dc,this,rect);
 }

void Custom_wxDataViewTreeCtrl::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect){

     dc.SetBrush(wxColour(230,230,230));

     dc.DrawRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(),rect.GetHeight());
}

void Custom_wxDataViewTreeCtrl::Receive_Position(wxPoint control_position){

     this->Position = control_position;
}
