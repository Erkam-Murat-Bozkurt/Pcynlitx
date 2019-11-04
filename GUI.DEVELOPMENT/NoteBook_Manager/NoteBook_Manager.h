
#ifndef NOTEBOOK_MANAGER_H
#define NOTEBOOK_MANAGER_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibook.h>
#include <wx/aui/framemanager.h>
#include <wx/textctrl.h>
#include <wx/stc/stc.h>
#include <wx/font.h>
#include <wx/arrstr.h>
#include <wx/bitmap.h>
#include <wx/imaglist.h>
#include "Style_Loader.h"
#include "Event_ID_Numbers.h"

class Custom_TabArt : public wxAuiDefaultTabArt
{
public:
  Custom_TabArt(){

  }

  wxAuiTabArt * Clone() {

      return new Custom_TabArt(*this);
  }

  virtual ~Custom_TabArt(){

  }

  virtual void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& _rect) {

    wxRect rect = _rect;

    rect.height++;

    dc.SetBrush(wxColour(230,230,230));

    dc.DrawRectangle(rect.GetX()-1, rect.GetY()-1, rect.GetWidth()+2, rect.GetHeight()+2);
  }
};

static int  Current_Page_Record_Index;
static bool Style_Change_Operation;
static wxAuiNotebook * Aui_Notebook;

struct Text_Ctrl_Data
{
  wxStyledTextCtrl * Text_Ctrl;
  int  Window_ID;
  bool Document_Change_Condition;
  bool Is_Pointer_Free;
  bool Document_Change_In_File_Open;
  wxString File_Path;
};

static Text_Ctrl_Data NoteBook_Page_Data[20];

class NoteBook_Manager
{
public:
  NoteBook_Manager(wxFrame * Frame, wxAuiManager * Interface_Manager, wxFont Default_Font);
  virtual ~NoteBook_Manager();
  void Change_Cursor_Type();
  void Load_Default_Cursor();
  void Set_Caret_Line_InVisible();
  void Set_Caret_Line_Visible();
  void Add_New_Empty_File(wxString File_Path);
  void Use_Default_Caret();
  void Use_Block_Caret();
  void Add_New_File(wxString File_Path);
  void Open_File(wxString File_Path);
  void Load_Project_Directory(wxString Folder);
  void Set_Font(wxFont Default_Font);
  void Set_Lexer_Style(wxFont Default_Font);
  void Set_Style_Font(wxFont Font);
  void OnClose();
  void Clear_Dynamic_Memory();
  void Clear_Style();
  void Reload_Style();
  void Use_Bold_Styling();
  void Select_File(wxString File_Path);
  static void File_Save();
  void NonStatic_File_Save();
  void Set_Selection(size_t page);
  void Detach_From_Aui_Manager();
  static void Selection_Changing(wxAuiNotebookEvent & event);
  static void NoteBook_Page_Closed(wxAuiNotebookEvent & event);
  static void Document_Change(wxStyledTextEvent & event);
  static void Determine_Current_Page(wxAuiNotebookEvent & event);
  bool Is_File_Open(wxString File_Path);
  wxString Get_Selected_Text_Ctrl_File_Path();
  int Get_Selection();
  wxStyledTextCtrl * Get_Selected_Text_Ctrl();
  wxAuiNotebook * Get_NoteBook_Pointer();
  wxWindow * NoteBook_Window;
private:
  void Determine_File_Short_Name(wxString File_Long_Name);
  int Get_Empty_Pointer_Index_Number();
  wxWindowDC * WinDc_Pointer;
  wxAuiTabArt * Custom_TabArt_Pointer;
  wxAuiTabContainer Tab_Info_Container;
  wxAuiManager * Interface_Manager_Pointer;
  wxFont Default_Font;
  wxFont * Intro_File_Font;
  wxPanel * text_panel;
  wxImageList Image_List;
  wxString File_Short_Name;
  Style_Loader Text_Style_Loader;
  int Selection;
  int Empty_Pointer_Index_Number;
  int Empty_Data_Record_Point;
  int Introduction_Page_Id;
  bool Memory_Delete_Condition;
  bool File_Open_Status;
};

#endif /* NOTEBOOK_MANAGER_H */
