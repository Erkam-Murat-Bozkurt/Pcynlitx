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

#include "Directory_List_Manager.h"

Directory_List_Manager::Directory_List_Manager(wxFrame * Frame, wxAuiManager * Interface_Manager, wxFont Default_Font){

   this->Memory_Delete_Condition = false;

   this->panel_open_status = false;

   this->Interface_Manager_Pointer = Interface_Manager;

   this->Scroll = new wxScrolledWindow(Frame,wxID_ANY,wxDefaultPosition,wxSize(2000,5000));

   this->Scroll->SetVirtualSize(2000,5000);

   this->Scroll->EnableScrolling(true,true);

   this->Scroll->AlwaysShowScrollbars(true,true);

   this->Scroll->SetScrollbars(20,20,50,50,0,0,false);

   this->tree_control = new wxDataViewTreeCtrl(this->Scroll,wxID_ANY,wxDefaultPosition,wxSize(2000,5000),wxDV_NO_HEADER);

   this->tree_control->SetVirtualSize(2000,5000);

   this->tree_control->SetFont(Default_Font);

   this->Folder_Lister = new Project_Folder_Lister(this->tree_control);

   this->Scroll->Show(false);

   this->File_List_Widget_Shape.TopDockable(false);

   this->File_List_Widget_Shape.Right();

   this->File_List_Widget_Shape.Resizable(true);

   this->File_List_Widget_Shape.MinSize(250,-1);

   this->File_List_Widget_Shape.MaxSize(2000,2000);

   this->File_List_Widget_Shape.Show(true);

   this->File_List_Widget_Shape.CloseButton(true);

   this->File_List_Widget_Shape.Dock();

   this->File_List_Widget_Shape.dock_proportion = 0.25;
}

Directory_List_Manager::~Directory_List_Manager(){

    if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
    }
}

void Directory_List_Manager::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Folder_Lister != nullptr){

            delete this->Folder_Lister;
         }

         if(this->tree_control != nullptr){

            delete this->tree_control;
         }

         if(this->Scroll != nullptr){

            delete this->Scroll;
         }
     }
}

void Directory_List_Manager::Load_Project_Directory(wxString Folder){

     this->Folder_Lister->RemoveProjectDirectory();

     this->Folder_Lister->Load_Project_Directory(Folder);

     if(!this->panel_open_status){

        this->Interface_Manager_Pointer->AddPane(this->Scroll,this->File_List_Widget_Shape);

        this->panel_open_status = true;
     }

     wxWindow * pane_window = this->Interface_Manager_Pointer->GetPane(this->Scroll).window;

     pane_window->SetVirtualSize(2000,5000);

     this->Scroll->SetTargetWindow(pane_window);

     this->Scroll->Show(true);

     this->Interface_Manager_Pointer->Update();
}

void Directory_List_Manager::Set_Font(wxFont Font){

      this->tree_control->SetFont(Font);
}

wxDataViewTreeCtrl * Directory_List_Manager::GetDataViewTreeCtrl(){

     return this->tree_control;
}

wxString Directory_List_Manager::GetItemPath(wxDataViewItem item_number){

         return this->Folder_Lister->GetItemPath(item_number);
}

void Directory_List_Manager::RemoveProjectDirectory(){

     this->Folder_Lister->RemoveProjectDirectory();
}

void Directory_List_Manager::Close_Directory_Pane(){

     if(this->panel_open_status){

        this->Interface_Manager_Pointer->DetachPane(this->Scroll);

        this->Scroll->Show(false);

        this->Interface_Manager_Pointer->Update();

        this->panel_open_status = false;
    }
}
