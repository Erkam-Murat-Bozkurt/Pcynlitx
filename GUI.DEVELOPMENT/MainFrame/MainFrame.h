
#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/aui/auibook.h>
#include <wx/aui/dockart.h>
#include <wx/event.h>
#include <wx/fontdata.h>
#include <wx/fontdlg.h>
#include <wx/filedlg.h>
#include <wx/font.h>
#include <wx/process.h>
#include <wx/utils.h>
#include <wx/dialog.h>
#include <wx/dir.h>
#include <wx/toolbar.h>
#include <wx/richmsgdlg.h>
#include <wx/stc/stc.h>
#include <wx/textdlg.h>
#include <wx/colour.h>
#include <wx/string.h>
#include "wx_Description_Record_Tools.h"
#include "Project_File_Selection_Dialog.h"
#include "Menu_Bar_Options.h"
#include "NoteBook_Manager.h"
#include "keyboard_event_controler.h"
#include "Directory_List_Manager.h"
#include "Event_ID_Numbers.h"
#include "ToolBar_Initializer.h"
#include "Process_Execution_Controller.h"
#include "Custom_DockArt.h"

class MainFrame : public wxFrame
{
public:
  MainFrame();
  virtual ~MainFrame();
  void OnQuit(wxCommandEvent & event);
  void OnOpen(wxCommandEvent & event);
  void SelectProjectFile(wxCommandEvent & event);
  void OnOpenFontDialog(wxCommandEvent & event);
  void DirectoryOpen(wxCommandEvent & event);
  void RunLibraryBuilder(wxCommandEvent & event);
  void RunExeBuilder(wxCommandEvent & event);
  void OpenTerminal(wxCommandEvent & event);
  void FileSelect(wxDataViewEvent & event);
  void ShowProjectFile(wxCommandEvent & event);
  void ShowLicense(wxCommandEvent & event);
  void Show_Therms_of_use(wxCommandEvent & event);
  void ShowHelp(wxCommandEvent & event);
  void ShowAuthor(wxCommandEvent & event);
  void ShowProjectFileLocation(wxCommandEvent & event);
  void ShowProjectDirectoryLocation(wxCommandEvent & event);
  void Open_Tutorial(wxCommandEvent & event);
  void Show_Descriptions(wxCommandEvent & event);
private:
  void FileNameEdit(wxDataViewEvent & event);
  void Process_End(wxProcessEvent & event);
  void File_Save(wxCommandEvent & event);
  void OpenEmptyProjectFile(wxCommandEvent & event);
  void Increase_Font_Size(wxCommandEvent & event);
  void Decrease_Font_Size(wxCommandEvent & event);
  void Use_Default_Font(wxCommandEvent & event);
  void Undo_Changes(wxCommandEvent & event);
  void Redo_Changes(wxCommandEvent & event);
  void Re_Open_Project_Directory(wxCommandEvent & event);
  void Enter_Header_File_Location(wxCommandEvent & event);
  void Enter_Source_File_Location(wxCommandEvent & event);
  void Enter_Library_Location(wxCommandEvent & event);
  void Enter_Header_File(wxCommandEvent & event);
  void Enter_Source_File(wxCommandEvent & event);
  void Enter_Library_Name(wxCommandEvent & event);
  void Enter_Namespace(wxCommandEvent & event);
  void Enter_Construction_Point(wxCommandEvent & event);
  void Enter_Thread_Function_Name(wxCommandEvent & event);
  void Enter_Thread_Number(wxCommandEvent & event);
  void Enter_Exe_File_Name(wxCommandEvent & event);
  void Enter_ITC_Class_Header_File_Name(wxCommandEvent & event);
  void Enter_IT_Data_Type_Header_File_Name(wxCommandEvent & event);
  void Enter_IT_Data_Type_Name(wxCommandEvent & event);
  void Launch_Pdf_Reader(wxString Command);
  void Clear_Style(wxCommandEvent & event);
  void Reload_Default_Style(wxCommandEvent & event);
  void Save_File_As(wxCommandEvent & event);
  void Set_Caret_Line_Visible(wxCommandEvent & event);
  void Set_Caret_Line_InVisible(wxCommandEvent & event);
  void Use_Block_Caret(wxCommandEvent & event);
  void Use_Default_Caret(wxCommandEvent & event);
  void Clear_Text(wxCommandEvent & event);
  void Load_Default_Cursor(wxCommandEvent & event);
  void Change_Cursor_Type(wxCommandEvent & event);
  void New_File(wxCommandEvent & event);
  void Use_Bold_Styling(wxCommandEvent & event);
  void Size_Changed(wxSizeEvent & event);
  void Close_Directory_Pane(wxAuiManagerEvent & event);
  void Description_Record_Data_Lose_Protection();
  void Auto_Indentation(wxStyledTextEvent & event);
  void KeyboardEvent(wxKeyEvent & event);
  bool Memory_Delete_Condition;
  bool is_bold_style_selected;
  bool is_project_file_selected;
  bool is_descriptor_file_ready_to_record;
  long Sub_Process_ID;
  wxProcess * Process_Pointer;
  wxString Descriptor_File_Path;
  wxString Run_Command;
  wxString Construction_Point;
  wxAuiManager Interface_Manager;
  wxAuiDockArt * Dock_Art_Pointer;
  Menu_Bar_Options * MB_Options;
  NoteBook_Manager * Book_Manager;
  Directory_List_Manager * Dir_List_Manager;
  ToolBar_Initializer ToolBar_Widget;
  Project_File_Selection_Dialog * Pr_File_Select_Dialog;
  wx_Description_Record_Tools Description_Recorder;
  keyboard_event_controler key_events_ctrl;
  Process_Execution_Controller Process_Controller;
  wxDir    * dir_control;
  wxFont   * Default_Font;
  wxFontDialog * Font_Dialog;
  wxDataViewTreeCtrl * tree_control;
  DECLARE_EVENT_TABLE()
};

#endif /* MAINFRAME_H */
