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

#include "NoteBook_Manager.h"

NoteBook_Manager::NoteBook_Manager(wxFrame * Frame, wxAuiManager * Interface_Manager, wxFont Default_Font){

    this->Memory_Delete_Condition = false;

    Style_Change_Operation = false;

    Current_Page_Record_Index = 0;

    for(int i=0;i<20;i++){

        NoteBook_Page_Data[i].Is_Pointer_Free = true;

        NoteBook_Page_Data[i].File_Path = wxT("");

        NoteBook_Page_Data[i].Document_Change_Condition = false;

        NoteBook_Page_Data[i].Window_ID = 0;

        NoteBook_Page_Data[i].Text_Ctrl = nullptr;

        NoteBook_Page_Data[i].Document_Change_In_File_Open = false;
    }

    this->Interface_Manager_Pointer = Interface_Manager;

    Aui_Notebook = new wxAuiNotebook(Frame,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxAUI_NB_DEFAULT_STYLE);

    Aui_Notebook->InheritAttributes();

    Aui_Notebook->Refresh();

    this->Custom_TabArt_Pointer = new Custom_TabArt();

    Aui_Notebook->SetArtProvider(this->Custom_TabArt_Pointer);

    this->Default_Font = Default_Font;

    // Text panel initialization

    NoteBook_Page_Data[0].Text_Ctrl = new wxStyledTextCtrl(Aui_Notebook,wxID_ANY,wxDefaultPosition,wxSize(650,5000));

    NoteBook_Page_Data[0].Text_Ctrl->SetVirtualSize(2000,5000);

    NoteBook_Page_Data[0].Text_Ctrl->InheritAttributes();

    NoteBook_Page_Data[0].Text_Ctrl->LoadFile(wxT("/usr/share/Pcynlitx/Intro_File"));

    NoteBook_Page_Data[0].Window_ID = NoteBook_Page_Data[0].Text_Ctrl->GetId();

    this->Introduction_Page_Id = NoteBook_Page_Data[0].Window_ID;


    NoteBook_Page_Data[0].Document_Change_In_File_Open = true;

    this->Intro_File_Font = new wxFont(15,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,"Linux Libertine");

    this->Text_Style_Loader.Set_Lexer_Style(*this->Intro_File_Font,NoteBook_Page_Data[0].Text_Ctrl);

    NoteBook_Page_Data[0].Text_Ctrl->SetMarginWidth(MARGIN_LINE_NUMBERS,0);

    NoteBook_Page_Data[0].Text_Ctrl->SetReadOnly(true);

    NoteBook_Page_Data[0].Text_Ctrl->SetCaretStyle(0);

    Aui_Notebook->AddPage(NoteBook_Page_Data[0].Text_Ctrl,wxT(" Introduction  "),true);

    NoteBook_Page_Data[0].File_Path = wxT("/usr/share/Pcynlitx/Intro_File");

    NoteBook_Page_Data[0].Document_Change_Condition = false;

    NoteBook_Page_Data[0].Is_Pointer_Free = false;

    Aui_Notebook->Centre();

    Aui_Notebook->AlwaysShowScrollbars(true,true);



    wxAuiNotebookEvent File_Closed(wxEVT_AUINOTEBOOK_PAGE_CLOSE,Aui_Notebook->GetId());

    Aui_Notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CLOSE,NoteBook_Page_Closed,Aui_Notebook->GetId());

    wxAuiNotebookEvent File_Selection_Change(wxEVT_AUINOTEBOOK_PAGE_CLOSE,Aui_Notebook->GetId());

    Aui_Notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGED,Determine_Current_Page,Aui_Notebook->GetId());

    wxStyledTextEvent File_Change(wxEVT_STC_CHANGE,Aui_Notebook->GetId());

    Aui_Notebook->Bind(wxEVT_STC_CHANGE,Document_Change,wxID_ANY);

    wxAuiNotebookEvent File_Selection_Changing(wxEVT_AUINOTEBOOK_PAGE_CHANGING,Aui_Notebook->GetId());

    Aui_Notebook->Bind(wxEVT_AUINOTEBOOK_PAGE_CHANGING,Selection_Changing,wxID_ANY);


    wxAuiPaneInfo NoteBook_Widget_Shape;

    NoteBook_Widget_Shape.CloseButton(false);

    NoteBook_Widget_Shape.Dock();

    NoteBook_Widget_Shape.Centre();

    NoteBook_Widget_Shape.Show(true);

    NoteBook_Widget_Shape.MinSize(2000,2000);

    NoteBook_Widget_Shape.Resizable(true);

    this->Interface_Manager_Pointer->AddPane(Aui_Notebook,NoteBook_Widget_Shape);

    this->NoteBook_Window = NoteBook_Widget_Shape.window;

    wxSize Notebook_Best_Size = this->Interface_Manager_Pointer->GetPane(Aui_Notebook).best_size;

    this->Interface_Manager_Pointer->GetPane(Aui_Notebook).MaxSize(Notebook_Best_Size);

    this->Interface_Manager_Pointer->GetPane(Aui_Notebook).BestSize(Notebook_Best_Size);

    Aui_Notebook->Update();

    this->Interface_Manager_Pointer->Update();

    Frame->Centre();
}

NoteBook_Manager::~NoteBook_Manager(){

    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        for(int i=0;i<20;i++){

            if(NoteBook_Page_Data[i].Text_Ctrl != nullptr){

               delete NoteBook_Page_Data[i].Text_Ctrl;

               NoteBook_Page_Data[i].Text_Ctrl = nullptr;
            }
        }

        this->OnClose();
    }
}

void NoteBook_Manager::OnClose(){

     this->Detach_From_Aui_Manager();

     Aui_Notebook->Unbind(wxEVT_AUINOTEBOOK_PAGE_CLOSE,NoteBook_Page_Closed,Aui_Notebook->GetId());

     Aui_Notebook->Unbind(wxEVT_AUINOTEBOOK_PAGE_CHANGED,Determine_Current_Page,Aui_Notebook->GetId());

     Aui_Notebook->Unbind(wxEVT_STC_CHANGE,Document_Change,wxID_ANY);

     Aui_Notebook->Unbind(wxEVT_AUINOTEBOOK_PAGE_CHANGING,Selection_Changing,wxID_ANY);

     this->Clear_Dynamic_Memory();
}

void NoteBook_Manager::Clear_Dynamic_Memory()
{
     Aui_Notebook->DeleteAllPages();

     Aui_Notebook->DestroyChildren();

     Aui_Notebook->Destroy();

     delete this->Custom_TabArt_Pointer;

     delete this->Intro_File_Font;
}

void NoteBook_Manager::Detach_From_Aui_Manager()
{
     wxWindow * notebook_window = this->Interface_Manager_Pointer->GetPane(Aui_Notebook).window;

     if(notebook_window != NULL){

        this->Interface_Manager_Pointer->DetachPane(notebook_window);
     }
}

void NoteBook_Manager::Change_Cursor_Type()
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            NoteBook_Page_Data[i].Text_Ctrl->SetSTCCursor(2);
         }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::Load_Default_Cursor()
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            NoteBook_Page_Data[i].Text_Ctrl->SetSTCCursor(-1);
         }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::Set_Caret_Line_InVisible()
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            NoteBook_Page_Data[i].Text_Ctrl->SetCaretLineVisible(false);
         }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::Set_Caret_Line_Visible()
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            NoteBook_Page_Data[i].Text_Ctrl->SetCaretLineVisible(true);

            NoteBook_Page_Data[i].Text_Ctrl->SetCaretLineBackground(wxColour(220,220,220));
        }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::Use_Default_Caret()
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            NoteBook_Page_Data[i].Text_Ctrl->SetCaretStyle(1);

            NoteBook_Page_Data[i].Text_Ctrl->SetCaretWidth(1);

            NoteBook_Page_Data[i].Text_Ctrl->SetCaretForeground(wxColour(50,50,50));
         }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::Use_Block_Caret()
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            NoteBook_Page_Data[i].Text_Ctrl->SetCaretStyle(2);

            NoteBook_Page_Data[i].Text_Ctrl->SetCaretWidth(1);

            NoteBook_Page_Data[i].Text_Ctrl->SetCaretForeground(wxColour(150,150,150));
         }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::File_Save()
{
     wxString Current_Page_Text_Path = NoteBook_Page_Data[Current_Page_Record_Index].File_Path;

     NoteBook_Page_Data[Current_Page_Record_Index].Text_Ctrl->SaveFile(Current_Page_Text_Path,wxTEXT_TYPE_ANY);

     NoteBook_Page_Data[Current_Page_Record_Index].Document_Change_Condition = false;
}

void NoteBook_Manager::NonStatic_File_Save()
{
     NoteBook_Manager::File_Save();
}

void NoteBook_Manager::Add_New_File(wxString File_Path)
{
     bool Is_File_Open = this->Is_File_Open(File_Path);

     if(!Is_File_Open){

         int Index_Number = this->Get_Empty_Pointer_Index_Number();

         NoteBook_Page_Data[Index_Number].Text_Ctrl = new wxStyledTextCtrl(Aui_Notebook,wxID_ANY,wxDefaultPosition,wxSize(650,600));

         NoteBook_Page_Data[Index_Number].Text_Ctrl->SetVirtualSize(2000,5000);

         NoteBook_Page_Data[Index_Number].Window_ID = NoteBook_Page_Data[Index_Number].Text_Ctrl->GetId();

         NoteBook_Page_Data[Index_Number].File_Path = File_Path;

         NoteBook_Page_Data[Index_Number].Document_Change_Condition = false;

         NoteBook_Page_Data[Index_Number].Document_Change_In_File_Open = true;

         NoteBook_Page_Data[Index_Number].Is_Pointer_Free = false;

         this->Text_Style_Loader.Set_Lexer_Style(this->Default_Font,NoteBook_Page_Data[Index_Number].Text_Ctrl);

         this->Determine_File_Short_Name(File_Path);

         Aui_Notebook->AddPage(NoteBook_Page_Data[Index_Number].Text_Ctrl,this->File_Short_Name);

         Aui_Notebook->Update();

         NoteBook_Page_Data[Index_Number].Text_Ctrl->SetReadOnly(false);

         NoteBook_Page_Data[Index_Number].Text_Ctrl->LoadFile(File_Path);

         NoteBook_Page_Data[Index_Number].Text_Ctrl->ClearAll();

         NoteBook_Page_Data[Index_Number].Text_Ctrl->SaveFile(File_Path);

         this->Select_File(File_Path);
     }
     else{

          this->Select_File(File_Path);
     }
}

void NoteBook_Manager::Open_File(wxString File_Path)
{
     bool Is_File_Open = this->Is_File_Open(File_Path);

     if(!Is_File_Open){

         int Index_Number = this->Get_Empty_Pointer_Index_Number();

         NoteBook_Page_Data[Index_Number].Text_Ctrl = new wxStyledTextCtrl(Aui_Notebook,wxID_ANY,wxDefaultPosition,wxSize(650,600));

         NoteBook_Page_Data[Index_Number].Text_Ctrl->SetVirtualSize(2000,5000);

         NoteBook_Page_Data[Index_Number].Window_ID = NoteBook_Page_Data[Index_Number].Text_Ctrl->GetId();

         this->Text_Style_Loader.Set_Lexer_Style(this->Default_Font,NoteBook_Page_Data[Index_Number].Text_Ctrl);

         this->Determine_File_Short_Name(File_Path);

         NoteBook_Page_Data[Index_Number].File_Path = File_Path;

         NoteBook_Page_Data[Index_Number].Document_Change_Condition = false;

         NoteBook_Page_Data[Index_Number].Document_Change_In_File_Open = true;

         NoteBook_Page_Data[Index_Number].Is_Pointer_Free = false;

         Aui_Notebook->AddPage(NoteBook_Page_Data[Index_Number].Text_Ctrl,this->File_Short_Name);

         Aui_Notebook->SetSelection(Index_Number);

         Aui_Notebook->Update();

         NoteBook_Page_Data[Index_Number].Text_Ctrl->SetReadOnly(false);

         NoteBook_Page_Data[Index_Number].Text_Ctrl->LoadFile(File_Path);

         this->Select_File(File_Path);
     }
     else{

           this->Select_File(File_Path);
     }
}

void NoteBook_Manager::Set_Font(wxFont Font)
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            if( NoteBook_Page_Data[i].Window_ID != this->Introduction_Page_Id ){

                this->Text_Style_Loader.Set_Lexer_Style(Font,NoteBook_Page_Data[i].Text_Ctrl);
            }
         }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::Set_Lexer_Style(wxFont Default_Font)
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            if( NoteBook_Page_Data[i].Window_ID != this->Introduction_Page_Id ){

                this->Text_Style_Loader.Set_Lexer_Style(Default_Font,NoteBook_Page_Data[i].Text_Ctrl);
            }
          }
     }

    Aui_Notebook->SetSelection(Selection);

    Style_Change_Operation = false;
}

void NoteBook_Manager::Set_Style_Font(wxFont Font)
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            if( NoteBook_Page_Data[i].Window_ID != this->Introduction_Page_Id ){

                this->Text_Style_Loader.Set_Style_Font(Font,NoteBook_Page_Data[i].Text_Ctrl);
            }
         }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::Use_Bold_Styling()
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            if( NoteBook_Page_Data[i].Window_ID != this->Introduction_Page_Id ){

                this->Text_Style_Loader.Use_Bold_Styling(NoteBook_Page_Data[i].Text_Ctrl);
            }
         }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::Clear_Style()
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

         wxString File_Path = NoteBook_Page_Data[i].File_Path;

         bool is_this_file_open = this->Is_File_Open(File_Path);

         if(is_this_file_open){

            if( NoteBook_Page_Data[i].Window_ID != this->Introduction_Page_Id ){

                this->Text_Style_Loader.Clear_Text_Control_Style(NoteBook_Page_Data[i].Text_Ctrl,this->Default_Font);
            }
         }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

void NoteBook_Manager::Reload_Style()
{
     Style_Change_Operation = true;

     int Selection = Aui_Notebook->GetSelection();

     for(int i=0;i<20;i++){

        wxString File_Path = NoteBook_Page_Data[i].File_Path;

        bool is_this_file_open = this->Is_File_Open(File_Path);

        if(is_this_file_open){

           if( NoteBook_Page_Data[i].Window_ID != this->Introduction_Page_Id ){

              this->Text_Style_Loader.Reload_Text_Control_Style(NoteBook_Page_Data[i].Text_Ctrl,this->Default_Font);
           }
        }
     }

     Aui_Notebook->SetSelection(Selection);

     Style_Change_Operation = false;
}

wxStyledTextCtrl * NoteBook_Manager::Get_Selected_Text_Ctrl()
{
      return NoteBook_Page_Data[Current_Page_Record_Index].Text_Ctrl;
}

void NoteBook_Manager::Set_Selection(size_t page){

     Aui_Notebook->SetSelection(page);
}

void NoteBook_Manager::Document_Change(wxStyledTextEvent & event)
{
     int event_id = event.GetId();

     for(int i=0;i<20;i++){

         if(NoteBook_Page_Data[i].Window_ID == event_id){

            if(NoteBook_Page_Data[i].Document_Change_In_File_Open){

               NoteBook_Page_Data[i].Document_Change_In_File_Open = false;
            }
            else{

               NoteBook_Page_Data[i].Document_Change_Condition = true;
            }

            break;
         }
     }

     event.Skip(true);
}

void NoteBook_Manager::Determine_Current_Page(wxAuiNotebookEvent & event)
{
     wxWindow * window_pointer = Aui_Notebook->GetCurrentPage();

     int page_id = window_pointer->GetId();

     for(int i=0;i<20;i++){

         if(NoteBook_Page_Data[i].Window_ID == page_id){

            Current_Page_Record_Index = i;

            break;
         }
     }

     event.Skip(true);
}

void NoteBook_Manager::NoteBook_Page_Closed(wxAuiNotebookEvent & event)
{
     wxWindow * window_pointer = Aui_Notebook->GetCurrentPage();

     int closed_page_id = window_pointer->GetId();

     int index_number = 0;

     for(int i=0;i<20;i++){

         if(NoteBook_Page_Data[i].Window_ID == closed_page_id){

            index_number = i;

            break;
         }
     }

     bool Selected_File_Change_Condition = NoteBook_Page_Data[index_number].Document_Change_Condition;

     if(Selected_File_Change_Condition){

        wxString Message_Text = wxT(" File has changes\n Do you want to save!");

        wxMessageDialog * info_dial = new wxMessageDialog(NULL,Message_Text,wxT("Information"),wxYES_NO);

        if(info_dial->ShowModal() == wxID_YES){

           NoteBook_Page_Data[index_number].Text_Ctrl->SaveFile(NoteBook_Page_Data[index_number].File_Path,wxTEXT_TYPE_ANY);

           delete info_dial;
        }
     }

     NoteBook_Page_Data[index_number].Is_Pointer_Free = true;

     NoteBook_Page_Data[index_number].File_Path = wxT("");

     NoteBook_Page_Data[index_number].Document_Change_Condition = false;

     NoteBook_Page_Data[index_number].Document_Change_In_File_Open = false;

     NoteBook_Page_Data[index_number].Window_ID = 0;

     event.Skip(true);
}

wxAuiNotebook * NoteBook_Manager::Get_NoteBook_Pointer()
{
    return Aui_Notebook;
}

int NoteBook_Manager::Get_Empty_Pointer_Index_Number()
{
    this->Empty_Pointer_Index_Number = 0;

    for(int i=0;i<20;i++){

        bool is_pointer_free = NoteBook_Page_Data[i].Is_Pointer_Free;

        if(is_pointer_free){

           this->Empty_Pointer_Index_Number = i;

           break;
        }
    }

    return this->Empty_Pointer_Index_Number;
}

void NoteBook_Manager::Determine_File_Short_Name(wxString File_Long_Name)
{
     int Name_Size = 0;

     for(int k=File_Long_Name.length();k>0;k--){

         if(File_Long_Name[k] == '/'){

            break;
         }

         Name_Size++;
     }

     this->File_Short_Name = wxT(" ");

     for(int k=File_Long_Name.length() - Name_Size +1; k<File_Long_Name.length();k++){

         this->File_Short_Name = this->File_Short_Name + File_Long_Name[k];
     }

     this->File_Short_Name = this->File_Short_Name + wxT(" ");
}

bool NoteBook_Manager::Is_File_Open(wxString File_Path)
{

     this->File_Open_Status = false;

     for(int i=0;i<20;i++){

         if(File_Path != wxT("")){

            if(File_Path == NoteBook_Page_Data[i].File_Path){

               this->File_Open_Status = true;

               break;
            }
         }
     }

     return this->File_Open_Status;
}

wxString NoteBook_Manager::Get_Selected_Text_Ctrl_File_Path()
{

         return NoteBook_Page_Data[Current_Page_Record_Index].File_Path;
}

void NoteBook_Manager::Select_File(wxString File_Path)
{

     int File_Index_Number = 0;

     for(int i=0;i<20;i++){

        if(NoteBook_Page_Data[i].File_Path == File_Path){

           File_Index_Number = i;
        }
     }

     int Page_Number = 0;

     size_t page_count = Aui_Notebook->GetPageCount();

     for(int i=0;i<page_count;i++){

         wxWindow * page_window = Aui_Notebook->GetPage(i);

         int page_id = page_window->GetId();

         if(NoteBook_Page_Data[File_Index_Number].Window_ID == page_id){

             Page_Number = i;
         }
     }

     Aui_Notebook->SetSelection(Page_Number);
}


void NoteBook_Manager::Selection_Changing(wxAuiNotebookEvent & event)
{

     if(Style_Change_Operation){

         event.Veto();
     }
     else{

          event.Skip(true);
     }
}
