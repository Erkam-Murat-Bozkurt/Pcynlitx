
#ifndef DIRECTORY_LIST_MANAGER_H
#define DIRECTORY_LIST_MANAGER_H

#include <wx/wx.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>
#include <wx/aui/aui.h>
#include <wx/aui/framemanager.h>
#include <wx/dataview.h>
#include <wx/font.h>
#include <wx/sizer.h>
#include "Project_Folder_Lister.h"
#include "Custom_DockArt.h"

class Directory_List_Manager
{
public:
  Directory_List_Manager(wxFrame * Frame, wxAuiManager * Interface_Manager, wxFont Default_Font);
  virtual ~Directory_List_Manager();
  void Set_Font(wxFont Default_Font);
  void Load_Project_Directory(wxString Folder);
  void Close_Directory_Pane();
  void RemoveProjectDirectory();
  void Clear_Dynamic_Memory();
  wxDataViewTreeCtrl * GetDataViewTreeCtrl();
  wxString GetItemPath(wxDataViewItem item_number);
private:
  bool panel_open_status;
  bool Memory_Delete_Condition;
  wxAuiDockArt * File_List_Dock_Art_Pointer;
  wxAuiPaneInfo File_List_Widget_Shape;
  wxScrolledWindow * Scroll;
  Project_Folder_Lister * Folder_Lister;
  wxDataViewTreeCtrl * tree_control;
  wxAuiManager * Interface_Manager_Pointer;
};

#endif /* DIRECTORY_LIST_MANAGER_H */
