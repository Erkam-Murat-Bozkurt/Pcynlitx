/*

Copyright ©  2019,  Erkam Murat Bozkurt

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

#include "ToolBar_Initializer.h"

ToolBar_Initializer::ToolBar_Initializer(){

}

ToolBar_Initializer::~ToolBar_Initializer(){

    delete this->toolBar;
}

void ToolBar_Initializer::Initialize_ToolBar(wxFrame * Frame_Pointer, wxAuiDockArt * Dock_Art_Pointer, wxAuiManager * Interface_Manager){

     wxBitmap close(wxT("/usr/share/Pcynlitx/icons/close.png"), wxBITMAP_TYPE_ANY);

     wxBitmap build_library(wxT("/usr/share/Pcynlitx/icons/archive.png"),wxBITMAP_TYPE_ANY);

     wxBitmap build_executable(wxT("/usr/share/Pcynlitx/icons/build_executable.png"),wxBITMAP_TYPE_ANY);

     wxBitmap Select_Project_File(wxT("/usr/share/Pcynlitx/icons/select_project_file.png"),wxBITMAP_TYPE_ANY);

     wxBitmap Empty_Project_File(wxT("/usr/share/Pcynlitx/icons/empty_project_file.png"),wxBITMAP_TYPE_ANY);

     wxBitmap Show_Help_Document(wxT("/usr/share/Pcynlitx/icons/help_documents.png"),wxBITMAP_TYPE_ANY);

     wxBitmap open_terminal(wxT("/usr/share/Pcynlitx/icons/open_terminal.png"),wxBITMAP_TYPE_ANY);

     wxBitmap file_save(wxT("/usr/share/Pcynlitx/icons/file_save.png"),wxBITMAP_TYPE_ANY);

     wxBitmap open_tree_view(wxT("/usr/share/Pcynlitx/icons/open_tree_view.png"),wxBITMAP_TYPE_ANY);

     wxBitmap print_descriptions(wxT("/usr/share/Pcynlitx/icons/print_descriptions.png"),wxBITMAP_TYPE_ANY);

     this->toolBar = new wxAuiToolBar(Frame_Pointer,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxAUI_TB_PLAIN_BACKGROUND);

     wxAuiToolBarArt * Art_Pointer = new MyAuiTBArt();

     this->toolBar->SetArtProvider(Art_Pointer);

     wxAuiPaneInfo ToolBar_Widget_Shape;

     ToolBar_Widget_Shape.CloseButton(false);

     ToolBar_Widget_Shape.LeftDockable(true);

     ToolBar_Widget_Shape.RightDockable(false);

     ToolBar_Widget_Shape.BottomDockable(false);

     ToolBar_Widget_Shape.TopDockable(false);

     ToolBar_Widget_Shape.Movable(false);

     ToolBar_Widget_Shape.Floatable(false);

     ToolBar_Widget_Shape.Left();

     ToolBar_Widget_Shape.Dock();

     ToolBar_Widget_Shape.PaneBorder(true);

     ToolBar_Widget_Shape.DockFixed(true);

     ToolBar_Widget_Shape.Show(true);

     wxWindowDC WinDc(this->toolBar);

     Art_Pointer->DrawPlainBackground(WinDc,this->toolBar,this->toolBar->GetRect());

     this->toolBar->AddTool(wxID_EXIT, wxT(""),close,wxT(""));

     this->toolBar->AddTool(ID_OPEN_TUTORIAL,wxT(""),Show_Help_Document,wxT(""));

     this->toolBar->AddTool(ID_OPEN_TREE_WIEW,wxT(""),open_tree_view,wxT(""));

     this->toolBar->AddTool(ID_RUN_EXECUTABLE,wxT(""),build_library,wxT(""));

     this->toolBar->AddTool(ID_RUN_EXECUTABLE_BINARY_BUILDER,wxT(""),build_executable,wxT(""));

     this->toolBar->AddTool(ID_SELECT_PROJECT_FILE,wxT(""),Select_Project_File,wxT(""));

     this->toolBar->AddTool(ID_OPEN_EMPTY_PROJECT_FILE,wxT(""),Empty_Project_File,wxT(""));

     this->toolBar->AddTool(ID_OPEN_TERMINAL,wxT(""),open_terminal,wxT(""));

     this->toolBar->AddTool(ID_FILE_SAVE,wxT(""),file_save,wxT(""));

     this->toolBar->AddTool(ID_SHOW_DESCRIPTIONS,wxT(""),print_descriptions,wxT(""));

     this->toolBar->SetMargins(-1,-1,3,3);

     this->toolBar->SetOverflowVisible(false);

     this->toolBar->SetBackgroundStyle(wxBG_STYLE_CUSTOM);

     this->toolBar->SetThemeEnabled(false);

     this->toolBar->RefreshRect(this->toolBar->GetRect(),true);

     this->toolBar->SetBackgroundColour(wxColor(80,80,80));

     this->toolBar->ClearBackground();

     this->toolBar->Realize();

     Interface_Manager->AddPane(this->toolBar,ToolBar_Widget_Shape);
}

wxAuiToolBar * ToolBar_Initializer::Get_ToolBar_Pointer(){

     return this->toolBar;
}
