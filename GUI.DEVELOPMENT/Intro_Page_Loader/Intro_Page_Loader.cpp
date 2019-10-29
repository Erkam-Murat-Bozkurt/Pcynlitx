
#include "Intro_Page_Loader.h"

Intro_Page_Loader::Intro_Page_Loader(){

      this->Memory_Delete_Condition = false;

      this->intro_page_close_condition = false;

      this->intro_page_bitmap  = new wxBitmap(wxT("/usr/share/Pcynlitx/Intro_File.png"), wxBITMAP_TYPE_PNG);

      this->intro_page_frame = new wxFrame(NULL,-1,wxT("Introduction"),wxDefaultPosition,wxSize(580,420),wxSTAY_ON_TOP | wxFIXED_MINSIZE);

      this->bitmap_panel = new wxPanel(this->intro_page_frame,-1,wxDefaultPosition,wxSize(580,380));

      this->bitmap_panel->Centre();

      this->bitmap_control = new wxStaticBitmap(this->bitmap_panel,-1,*this->intro_page_bitmap,wxDefaultPosition,wxSize(580,370));

      this->bitmap_control->Centre();

      this->close_button = new wxButton(this->intro_page_frame,wxID_CANCEL,wxT("Close"),wxDefaultPosition, wxSize(75,30));

      this->close_button_id = this->close_button->GetId();

      wxCommandEvent Page_Close(wxEVT_BUTTON,this->intro_page_frame->GetId());

      this->intro_page_frame->Bind(wxEVT_BUTTON, &Intro_Page_Loader::Close_Intro_Page,this,this->close_button->GetId());


      this->frame_sizer  = new wxBoxSizer(wxVERTICAL);

      this->panel_sizer = new wxBoxSizer(wxVERTICAL);

      this->button_sizer = new wxBoxSizer(wxHORIZONTAL);

      this->button_sizer->Add(this->close_button,0,wxALIGN_RIGHT | wxALL,10);

      this->panel_sizer->Add(this->bitmap_control,0, wxFIXED_MINSIZE | wxALIGN_TOP | wxALL,10);

      this->panel_sizer->Layout();

      this->bitmap_panel->SetSizer(this->panel_sizer);

      this->panel_sizer->SetSizeHints(this->bitmap_panel);

      this->frame_sizer->Add(this->panel_sizer,0,wxFIXED_MINSIZE | wxALIGN_CENTER | wxALL,20);

      this->frame_sizer->Add(this->button_sizer,0,wxALIGN_RIGHT | wxFIXED_MINSIZE | wxALL,10);

      this->intro_page_frame->SetSizer(this->frame_sizer);

      this->frame_sizer->SetSizeHints(this->intro_page_frame);

      this->intro_page_frame->SetAutoLayout(true);

      this->intro_page_frame->Centre(wxBOTH);

      this->intro_page_frame->CentreOnScreen(wxBOTH);

      this->intro_page_frame->CentreOnParent(wxBOTH);

      this->intro_page_frame->Show(true);
}


Intro_Page_Loader::Intro_Page_Loader(const Intro_Page_Loader & orig){

}


Intro_Page_Loader::~Intro_Page_Loader(){

     if(!this->Memory_Delete_Condition){

         this->Clear_Dynamic_Memory();
     }
}

void Intro_Page_Loader::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->button_sizer->Detach(this->close_button);

         this->panel_sizer->Detach(this->bitmap_panel);

         this->frame_sizer->Detach(this->panel_sizer);

         this->frame_sizer->Detach(this->button_sizer);

         this->frame_sizer->Detach(this->intro_page_frame);

         wxSizerItem * frame_sizer_item = this->frame_sizer->GetItem(this->intro_page_frame);

         wxSizerItem * frame_sizer_sub_panel_item = this->frame_sizer->GetItem(this->bitmap_panel);

         if(frame_sizer_sub_panel_item != NULL){

             this->frame_sizer->Remove(frame_sizer_sub_panel_item->GetSizer());
         }

         wxSizerItem * frame_sizer_sub_button_item = this->frame_sizer->GetItem(this->close_button);

         if(frame_sizer_sub_button_item != NULL){

             this->frame_sizer->Remove(frame_sizer_sub_button_item->GetSizer());
         }

         this->button_sizer->Clear(true);

         this->panel_sizer->Clear(true);

         this->frame_sizer->Clear(true);

         this->close_button->Destroy();

         delete this->intro_page_bitmap;

         this->bitmap_control->DestroyChildren();

         this->bitmap_panel->DestroyChildren();

         this->intro_page_frame->Destroy();

         this->intro_page_frame->Close(true);
     }
}

void Intro_Page_Loader::Close_Intro_Page(wxCommandEvent & event){

     int event_id = event.GetId();

     if(!this->intro_page_close_condition){

         if(event_id == this->close_button_id){

            this->Clear_Dynamic_Memory();

            this->intro_page_frame->Unbind(wxEVT_BUTTON, &Intro_Page_Loader::Close_Intro_Page,this,this->close_button->GetId());

            this->intro_page_close_condition = true;
         }
     }
}

void Intro_Page_Loader::Close_Intro_Page_From_MainFrame(){

     if(!this->intro_page_close_condition){

         this->Clear_Dynamic_Memory();

         this->intro_page_frame->Unbind(wxEVT_BUTTON, &Intro_Page_Loader::Close_Intro_Page,this,this->close_button->GetId());

         this->intro_page_close_condition = true;
     }
}

bool Intro_Page_Loader::Get_Intro_Page_Close_Condition(){

     return this->intro_page_close_condition;
}
