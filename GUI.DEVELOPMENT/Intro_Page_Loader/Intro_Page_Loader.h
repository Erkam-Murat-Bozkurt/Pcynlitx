
#ifndef INTRO_PAGE_LOADER
#define INTRO_PAGE_LOADER

#include <wx/wx.h>
#include <wx/event.h>
#include <wx/panel.h>
#include <wx/stc/stc.h>
#include <wx/arrstr.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/frame.h>
#include "Event_ID_Numbers.h"


class Intro_Page_Loader
{
public:
  Intro_Page_Loader();
  Intro_Page_Loader(const Intro_Page_Loader & orig);
  virtual ~Intro_Page_Loader();
  void Close_Intro_Page(wxCommandEvent & event);
  void Clear_Dynamic_Memory();
  bool Get_Intro_Page_Close_Condition();
  void Close_Intro_Page_From_MainFrame();
private:
  bool Memory_Delete_Condition;
  wxBitmap * intro_page_bitmap;
  wxFrame * intro_page_frame;
  wxPanel * bitmap_panel;
  wxStaticBitmap * bitmap_control;
  wxButton * close_button;
  wxBoxSizer * frame_sizer;
  wxBoxSizer * panel_sizer;
  wxBoxSizer * button_sizer;
  int close_button_id;
  bool intro_page_close_condition;
};

#endif /* INTRO_PAGE_LOADER */
