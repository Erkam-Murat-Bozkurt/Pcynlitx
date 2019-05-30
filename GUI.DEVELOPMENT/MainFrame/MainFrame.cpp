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

#include "Event_Table_Header.h"

MainFrame::MainFrame() : wxFrame(NULL,wxID_ANY,"PCYNLITX",wxDefaultPosition,wxDefaultSize)
{
  this->Interface_Manager.SetManagedWindow(this);

  this->Dock_Art_Pointer = this->Interface_Manager.GetArtProvider();

  this->Dock_Art_Pointer = new Custom_DockArt();

  this->Interface_Manager.SetArtProvider(this->Dock_Art_Pointer);

  this->Interface_Manager.SetFlags(wxAUI_MGR_LIVE_RESIZE);

  this->SetSize(wxSize(950,700));

  this->SetMinSize(wxSize(900,650));

  this->Default_Font = new wxFont(9,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,"Noto Sans Mono");

  this->MB_Options = new Menu_Bar_Options();

  this->SetMenuBar(this->MB_Options->Get_MenuBar());

  this->Book_Manager = new NoteBook_Manager(this,&this->Interface_Manager,*(this->Default_Font));

  this->Dir_List_Manager = new Directory_List_Manager(this,&this->Interface_Manager,*(this->Default_Font));

  this->ToolBar_Widget.Initialize_ToolBar(this,this->Dock_Art_Pointer,&this->Interface_Manager);

  this->ToolBar_Widget.Get_ToolBar_Pointer()->Update();

  this->Interface_Manager.Update();

  this->tree_control = this->Dir_List_Manager->GetDataViewTreeCtrl();


  wxDataViewEvent File_Activation(wxEVT_DATAVIEW_ITEM_ACTIVATED,this->tree_control->GetId());

  wxDataViewEvent File_Name_Edit(wxEVT_DATAVIEW_ITEM_START_EDITING,this->tree_control->GetId());

  Connect(this->tree_control->GetId(),wxEVT_DATAVIEW_ITEM_ACTIVATED,wxDataViewEventHandler(MainFrame::FileSelect));

  Connect(this->tree_control->GetId(),wxEVT_DATAVIEW_ITEM_START_EDITING,wxDataViewEventHandler(MainFrame::FileNameEdit));

  wxStyledTextEvent Char_Add(wxEVT_STC_CHARADDED,wxID_ANY);

  Connect(wxID_ANY,wxEVT_STC_CHARADDED,wxStyledTextEventHandler(MainFrame::Auto_Indentation));

  this->Interface_Manager.Update();

  this->dir_control = new wxDir;

  this->Process_Controller.Receive_Main_Frame_Address(this);

  this->key_events_ctrl.Receive_Book_Manager(this->Book_Manager);

  this->is_project_file_selected = false;

  this->is_descriptor_file_ready_to_record = false;

  this->Font_Dialog = nullptr;

  this->Pr_File_Select_Dialog = nullptr;

  this->Descriptor_File_Path = wxT("");

  this->Run_Command = wxT("");

  this->Construction_Point = wxT("");

  this->Memory_Delete_Condition = false;
}

MainFrame::~MainFrame(){

     this->Interface_Manager.UnInit();

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Default_Font != nullptr){

            delete this->Default_Font;

            this->Default_Font = nullptr;
         }

         if(this->dir_control != nullptr){

            delete this->dir_control;

            this->dir_control = nullptr;
         }

         if(this->Dir_List_Manager != nullptr){

            delete this->Dir_List_Manager;

            this->Dir_List_Manager = nullptr;
         }
     }
}

void MainFrame::OnOpenFontDialog(wxCommandEvent & WXUNUSED(event)){

     wxFontData Data;

     this->Font_Dialog = new wxFontDialog(this,Data);

     if(this->Font_Dialog->ShowModal() == wxID_OK){

        wxFontData Return_Font_Data = this->Font_Dialog->GetFontData();

        wxFont Selected_Font = Return_Font_Data.GetChosenFont();

        this->Book_Manager->Set_Font(Selected_Font);
     }

     if(this->Font_Dialog != nullptr){

        delete this->Font_Dialog;
     }
}

void MainFrame::OnOpen(wxCommandEvent & event)
{
     wxFileDialog * openFileDialog = new wxFileDialog(this);

     if (openFileDialog->ShowModal() == wxID_OK){

         wxString File_Path = openFileDialog->GetPath();

         this->Book_Manager->Open_File(File_Path);
     }

     delete openFileDialog;
}

void MainFrame::Close_Directory_Pane(wxAuiManagerEvent & event){

     this->Dir_List_Manager->RemoveProjectDirectory();

     this->Dir_List_Manager->Close_Directory_Pane();
}

void MainFrame::DirectoryOpen(wxCommandEvent & event){

     wxDirDialog dir_dialog(this, "Select a directory","",wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

     if(dir_dialog.ShowModal() == wxID_OK){

        wxString DirectoryPath = dir_dialog.GetPath();

        this->Dir_List_Manager->Load_Project_Directory(DirectoryPath);
     }
}

void MainFrame::File_Save(wxCommandEvent & event){

     NoteBook_Manager::File_Save();
}

void MainFrame::SelectProjectFile(wxCommandEvent & event){

     this->Pr_File_Select_Dialog = new Project_File_Selection_Dialog(this);

     if(this->Pr_File_Select_Dialog->Get_Project_File_Selection_Dialog()->ShowModal() == wxID_OK){

        this->Descriptor_File_Path = this->Pr_File_Select_Dialog->Get_File_Selection_Control()->GetPath();

        wxDir Dir_Ctrl;

        if(Dir_Ctrl.Exists(this->Descriptor_File_Path)){

           Dir_Ctrl.Open(this->Descriptor_File_Path);

           if(Dir_Ctrl.IsOpened()){

              wxMessageDialog * dial = new wxMessageDialog(NULL,wxT(" This is a directory!\n A file must be selected ."),wxT("Error Message"), wxOK);

              dial->ShowModal();

              return;
           }
        }

        this->Run_Command = wxT("");

        this->Run_Command = "/usr/bin/Pcynlitx_Kernel " + this->Descriptor_File_Path;

        int Descriptor_File_Name_Size = 0;

        int Descriptor_File_Path_Size = this->Descriptor_File_Path.length();

        wxString Selected_Project_Descriptor_File_Name = wxT("");

        for(int k = Descriptor_File_Path_Size; k > 0; k--){

            if(this->Descriptor_File_Path[k] == '/'){

                break;
            }

            Descriptor_File_Name_Size++;
        }

        for(int i=Descriptor_File_Name_Size-1;i>0;i--){

             Selected_Project_Descriptor_File_Name = Selected_Project_Descriptor_File_Name +

             this->Descriptor_File_Path[Descriptor_File_Path_Size -i];
        }

        wxString Project_Descriptor_File_Name = wxT("Project_Descriptor_File");

        bool Project_Descriptor_File_Name_Is_Correct = true;

        if(Selected_Project_Descriptor_File_Name != Project_Descriptor_File_Name){

           wxMessageDialog * dial = new wxMessageDialog(NULL,wxT(" Descriptor file name must be\"Project_Descriptor_File\" ..\n\n Different descriptor file names can not be\n recognized as descriptor file!\n\n Be sure that it is the correct file?"), wxT("Error Message"),wxOK);

           dial->ShowModal();

           Project_Descriptor_File_Name_Is_Correct = false;
        }

        if(Project_Descriptor_File_Name_Is_Correct){

           this->is_project_file_selected = true;

           this->Process_Controller.Set_Project_File_Select_Condition(this->is_project_file_selected);

           this->Process_Controller.Receive_Descriptor_File_Path(this->Descriptor_File_Path);

           this->Book_Manager->Open_File(this->Descriptor_File_Path);

           this->Description_Recorder.Receive_Text_Control(this->Book_Manager->Get_Selected_Text_Ctrl());

           this->Description_Recorder.Receive_Main_Frame_Address(this);

           this->Description_Recorder.Receive_Descriptor_File_Path(this->Descriptor_File_Path);
        }
        else{

           this->is_project_file_selected = false;
        }
     }

     this->Pr_File_Select_Dialog->Get_Project_File_Selection_Dialog()->Destroy();

     this->Description_Recorder.Receive_Project_File_Selection_Status(this->is_project_file_selected);
}

void MainFrame::ShowProjectFile(wxCommandEvent & event){

     if(this->is_project_file_selected){

        bool is_descriptor_file_open = false;

        for(int i=0;i<20;i++){

            wxString Path_Data =  NoteBook_Page_Data[i].File_Path;

            if(Path_Data == this->Descriptor_File_Path){

               is_descriptor_file_open = true;

               break;
            }
        }

        if(is_descriptor_file_open){

            this->Book_Manager->Select_File(this->Descriptor_File_Path);
        }
        else{

             this->Book_Manager->Open_File(this->Descriptor_File_Path);
        }

     }
     else{
            wxMessageDialog * dial = new wxMessageDialog(NULL,wxT("Descriptor file was not selected ..\nPlease select a descriptor file"),

            wxT("Info"), wxOK);

            if(dial->ShowModal()== wxOK){

               delete dial;
            }
     }
}

void MainFrame::FileNameEdit(wxDataViewEvent & event){

     event.Veto();
}

void MainFrame::FileSelect(wxDataViewEvent & event)
{
     wxDataViewItem Item = this->tree_control->GetSelection();

     wxString File_Path = this->Dir_List_Manager->GetItemPath(Item);

     if(this->dir_control->Exists(File_Path)){

         if(this->Dir_List_Manager->GetDataViewTreeCtrl()->IsExpanded(Item)){

           this->Dir_List_Manager->GetDataViewTreeCtrl()->Collapse(Item);
         }
         else{

               this->Dir_List_Manager->GetDataViewTreeCtrl()->Expand(Item);
         }
     }
     else{

          this->Book_Manager->Open_File(File_Path);
     }
}

void MainFrame::RunLibraryBuilder(wxCommandEvent & event){

     this->Process_Controller.RunLibraryBuilder(&(this->Dir_List_Manager));

     this->Construction_Point = wxT("");

     this->Construction_Point = this->Process_Controller.Get_Construction_Point();
}

void MainFrame::RunExeBuilder(wxCommandEvent & event){

     this->Process_Controller.RunExeBuilder(&(this->Dir_List_Manager));
}

void MainFrame::Process_End(wxProcessEvent & event){

     this->Process_Controller.Process_End(event.GetExitCode());
}

void MainFrame::OpenTerminal(wxCommandEvent & event){

     wxExecute(wxT("/usr/bin/x-terminal-emulator"),wxEXEC_ASYNC | wxEXEC_SHOW_CONSOLE);
}

void MainFrame::ShowAuthor(wxCommandEvent & event){

     wxMessageDialog * info_dial

     = new wxMessageDialog(NULL,wxT(" The developer of the platform:\n\n ERKAM MURAT BOZKURT M.Sc. Control Sysytem Engineering "), wxT("Information"),

     wxOK);

     if(info_dial->ShowModal() == ID_SHOW_AUTOR_INFO){

        delete info_dial;
     };
}

void MainFrame::ShowProjectFileLocation(wxCommandEvent & event){

     if(this->Descriptor_File_Path == wxT("")){

          wxMessageDialog * info_dial = new wxMessageDialog(NULL,wxT("Project file has not been selected yet!"),

                                        wxT("Information"), wxOK);

          if(info_dial->ShowModal() == ID_SHOW_PROJECT_DESCRIPTOR_FILE_LOCATION){

             delete info_dial;
          };
     }
     else{

          wxMessageDialog * info_dial = new wxMessageDialog(NULL,this->Descriptor_File_Path, wxT("Information"), wxOK);

          if(info_dial->ShowModal() == ID_SHOW_PROJECT_DESCRIPTOR_FILE_LOCATION){

             delete info_dial;
          };
     }
}

void MainFrame::ShowProjectDirectoryLocation(wxCommandEvent & event){

     if(this->Construction_Point == wxT("")){

         wxMessageDialog * info_dial = new wxMessageDialog(NULL,wxT("Project directory has not been determined !"),

                                       wxT("Information"), wxOK);

         if(info_dial->ShowModal() == ID_SHOW_PROJECT_DIRECTORY_LOCATION){

            delete info_dial;
         };
     }
     else{
            wxMessageDialog * info_dial = new wxMessageDialog(NULL,this->Construction_Point, wxT("Information"), wxOK);

            if(info_dial->ShowModal() == ID_SHOW_PROJECT_DIRECTORY_LOCATION){

               delete info_dial;
            };
     }
}

void MainFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
     Close(TRUE);
}

void MainFrame::Show_Descriptions(wxCommandEvent & event){

     if(this->is_project_file_selected){

        this->Process_Controller.Show_Descriptions(this->Descriptor_File_Path);
     }
     else{
            wxMessageDialog * dial = new wxMessageDialog(NULL,wxT("Descriptor file was selected!\nPlease select descriptor file"),

            wxT("Info"), wxOK);

            dial->ShowModal();

            delete dial;

            return;
     }
}

void MainFrame::OpenEmptyProjectFile(wxCommandEvent & event){

     this->Process_Pointer = new wxProcess(wxPROCESS_DEFAULT);

     this->is_project_file_selected = false;

     wxDirDialog dir_dialog(this, "Select File Location", "",wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

     wxString DirectoryPath;

     if(dir_dialog.ShowModal() == wxID_OK){

        DirectoryPath = dir_dialog.GetPath();

        this->is_project_file_selected = true;
     }

     this->Description_Recorder.Receive_Project_File_Selection_Status(this->is_project_file_selected);

     this->Process_Controller.Set_Project_File_Select_Condition(this->is_project_file_selected);

     if(this->is_project_file_selected){

        this->Descriptor_File_Path = DirectoryPath + wxT("/Project_Descriptor_File");

        wxTextFile File_Manager(this->Descriptor_File_Path);

        if(File_Manager.Exists()){

           wxMessageDialog * info_dial

           = new wxMessageDialog(NULL,wxT(" There is already a descriptor file in that location.\n If you continue, the information in the descriptor\n file will be lost ! "),

           wxT("Information"), wxOK);

           info_dial->ShowModal();

           wxMessageDialog * exit_dial = new wxMessageDialog(NULL,wxT("Are you sure to continue?"), wxT("Question"),wxYES_NO);

           if(exit_dial->ShowModal() ==  wxID_NO){

              return;
           };
        }

        wxString File_Construction_Command = wxT("Empty_Process_Descriptor_File_Builder ") + DirectoryPath;

        this->Sub_Process_ID = wxExecute(File_Construction_Command,wxEXEC_SYNC,this->Process_Pointer);

        int exit_status = 0;

        this->Process_Pointer->OnTerminate(this->Sub_Process_ID,exit_status);

        this->Book_Manager->Open_File(this->Descriptor_File_Path);

        this->Run_Command = wxT("");

        this->Run_Command = "/usr/bin/Pcynlitx_Kernel " + this->Descriptor_File_Path;

        this->Description_Recorder.Receive_Descriptor_File_Path(this->Descriptor_File_Path);

        this->Process_Controller.Set_Project_File_Select_Condition(this->is_project_file_selected);

        this->Process_Controller.Receive_Descriptor_File_Path(this->Descriptor_File_Path);

        this->Description_Recorder.Receive_Text_Control(this->Book_Manager->Get_Selected_Text_Ctrl());

        this->Description_Recorder.Receive_Main_Frame_Address(this);
     }
}

void MainFrame::ShowLicense(wxCommandEvent & event){

     wxString Shell_Command = wxT("evince /usr/share/Pcynlitx/gpl_3_0.pdf");

     this->Launch_Pdf_Reader(Shell_Command);
}

void MainFrame::Show_Therms_of_use(wxCommandEvent & event){

     wxString Shell_Command = wxT("evince /usr/share/Pcynlitx/Therms_of_use.pdf");

     this->Launch_Pdf_Reader(Shell_Command);
}

void MainFrame::ShowHelp(wxCommandEvent & event){

     wxString Shell_Command = wxT("evince /usr/share/Pcynlitx/Technical_Introduction.pdf");

     this->Launch_Pdf_Reader(Shell_Command);
}

void MainFrame::Open_Tutorial(wxCommandEvent & event){

     wxString Shell_Command = wxT("evince /usr/share/Pcynlitx/GUI_Tutorial.pdf");

     this->Launch_Pdf_Reader(Shell_Command);
}

void MainFrame::Launch_Pdf_Reader(wxString Command){

     wxProcess * Local_Pointer = new wxProcess(this,wxID_ANY);

     wxExecute(Command,wxEXEC_ASYNC,Local_Pointer);
}

void MainFrame::Increase_Font_Size(wxCommandEvent & event){

     wxFont Font = this->Book_Manager->Get_Selected_Text_Ctrl()->StyleGetFont(wxSTC_C_REGEX);

     Font.SetPointSize(Font.GetPointSize()+1);

     this->Book_Manager->Set_Font(Font);

     if(this->is_bold_style_selected){

        this->Book_Manager->Use_Bold_Styling();
     }
}

void MainFrame::Decrease_Font_Size(wxCommandEvent & event){

     wxFont Font = this->Book_Manager->Get_Selected_Text_Ctrl()->StyleGetFont(wxSTC_C_REGEX);

     Font.SetPointSize(Font.GetPointSize()-1);

     this->Book_Manager->Set_Font(Font);

     if(this->is_bold_style_selected){

        this->Book_Manager->Use_Bold_Styling();
     }
}

void MainFrame::Use_Default_Font(wxCommandEvent & WXUNUSED(event)){

     this->Book_Manager->Set_Font(*this->Default_Font);
}

void MainFrame::Undo_Changes(wxCommandEvent & event){

     this->Book_Manager->Get_Selected_Text_Ctrl()->Undo();
}

void MainFrame::Redo_Changes(wxCommandEvent & event){

     this->Book_Manager->Get_Selected_Text_Ctrl()->Redo();
}

void MainFrame::Clear_Style(wxCommandEvent & event){

     this->is_bold_style_selected = false;

     this->Book_Manager->Clear_Style();
}

void MainFrame::Reload_Default_Style(wxCommandEvent & event){

     this->is_bold_style_selected = false;

     this->Book_Manager->Reload_Style();
}

void MainFrame::Clear_Text(wxCommandEvent & event){

     this->Book_Manager->Get_Selected_Text_Ctrl()->ClearAll();
}

void MainFrame::Change_Cursor_Type(wxCommandEvent & event){

     this->Book_Manager->Change_Cursor_Type();
}

void MainFrame::Load_Default_Cursor(wxCommandEvent & event){

     this->Book_Manager->Load_Default_Cursor();
}

void MainFrame::Set_Caret_Line_Visible(wxCommandEvent & event){

     this->Book_Manager->Set_Caret_Line_Visible();
}

void MainFrame::Set_Caret_Line_InVisible(wxCommandEvent & event){

     this->Book_Manager->Set_Caret_Line_InVisible();
}

void MainFrame::Use_Block_Caret(wxCommandEvent & event){

     this->Book_Manager->Use_Block_Caret();
}

void MainFrame::Use_Default_Caret(wxCommandEvent & event){

     this->Book_Manager->Use_Default_Caret();
}

void MainFrame::Use_Bold_Styling(wxCommandEvent & event){

     this->is_bold_style_selected = true;

     this->Book_Manager->Use_Bold_Styling();
}

void MainFrame::Save_File_As(wxCommandEvent & event){

     wxString File_Path;

     wxFileDialog * SaveDialog = new wxFileDialog(this,wxT("Save File As ?"), wxEmptyString, wxEmptyString,

                   wxT("Text files (*.txt)|*.txt|C++ Source Files (*.cpp)|*.cpp|C Source files (*.c)|*.c|C header files (*.h)|*.h"),

                   wxFD_OVERWRITE_PROMPT | wxFD_SAVE, wxDefaultPosition);

     if(SaveDialog->ShowModal() == wxID_OK) // If the user clicked "OK"
     {
        File_Path = SaveDialog->GetPath();

        this->Book_Manager->Get_Selected_Text_Ctrl()->SaveFile(File_Path);
     }

     SaveDialog->Destroy();
}

void MainFrame::New_File(wxCommandEvent & event){

     wxString File_Path;

     wxFileDialog * File_Dialog = new wxFileDialog(this,wxT("New File"), wxEmptyString, wxEmptyString,

                   wxT(""),

                   wxFD_OVERWRITE_PROMPT | wxFD_SAVE, wxDefaultPosition);

     if(File_Dialog->ShowModal() == wxID_OK) // If the user clicked "OK"
     {
        File_Path = File_Dialog->GetPath();

        wxTextFile File_Manager(File_Path);

        if(!File_Manager.Exists()){

           File_Manager.Create();
        }

        this->Book_Manager->Add_New_File(File_Path);
     }

     File_Dialog->Destroy();
}

void MainFrame::Re_Open_Project_Directory(wxCommandEvent & event){

     if(this->Construction_Point == wxT("")){

        wxMessageDialog * info_dial = new wxMessageDialog(NULL,

        wxT("Project directory has not been determined !  At first, Library must be constructed !"), wxT("Information"), wxOK);

        if(info_dial->ShowModal() == ID_RE_OPEN_PROJECT_DIRECTORY){

           delete info_dial;
        };
     }
     else{
            this->Dir_List_Manager->RemoveProjectDirectory();

            this->Dir_List_Manager->Load_Project_Directory(this->Construction_Point);
     }
}

void MainFrame::Enter_Header_File_Location(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Header_File_Location();
     }
}

void MainFrame::Enter_Source_File_Location(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Source_File_Location();
     }
}

void MainFrame::Enter_Library_Location(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Library_Location();
     }
}

void MainFrame::Enter_Header_File(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Header_File();
     }
}

void MainFrame::Enter_Source_File(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Source_File();
     }
}

void MainFrame::Enter_Library_Name(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Library_Name();
     }
}

void MainFrame::Enter_Namespace(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Namespace();
     }
}


void MainFrame::Enter_Construction_Point(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Construction_Point();
     }
}

void MainFrame::Enter_Thread_Function_Name(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Thread_Function_Name();
     }
}

void MainFrame::Enter_Exe_File_Name(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Exe_File_Name();
     }
}

void MainFrame::Enter_ITC_Class_Header_File_Name(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_ITC_Class_Header_File_Name();
     }
}

void MainFrame::Enter_IT_Data_Type_Header_File_Name(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_IT_Data_Type_Header_File_Name();
     }
}

void MainFrame::Enter_IT_Data_Type_Name(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

         this->Description_Recorder.Enter_IT_Data_Type_Name();
     }
}

void MainFrame::Enter_Thread_Number(wxCommandEvent & event){

     this->Description_Record_Data_Lose_Protection();

     if(this->is_descriptor_file_ready_to_record){

        this->Description_Recorder.Enter_Thread_Number();
     }
}

void MainFrame::Description_Record_Data_Lose_Protection(){

     if(this->is_project_file_selected){

        bool Is_Descriptor_File_Open = this->Book_Manager->Is_File_Open(this->Descriptor_File_Path);

        if(Is_Descriptor_File_Open){

             this->Book_Manager->Select_File(this->Descriptor_File_Path);

             this->Description_Recorder.Receive_Text_Control(this->Book_Manager->Get_Selected_Text_Ctrl());
        }
        else{

             this->Book_Manager->Open_File(this->Descriptor_File_Path);

             this->Description_Recorder.Receive_Text_Control(this->Book_Manager->Get_Selected_Text_Ctrl());
        }

        this->is_descriptor_file_ready_to_record = true;
     }
     else{

           wxMessageDialog * dial = new wxMessageDialog(NULL,wxT("Descriptor file was not selected ..\nPlease select a descriptor file"),

           wxT("Info"), wxOK);

           if(dial->ShowModal()== wxOK){

              delete dial;
           }
     }
}

void MainFrame::Size_Changed(wxSizeEvent & event){

     this->Interface_Manager.Update();
}

void MainFrame::KeyboardEvent(wxKeyEvent & event){

     event.Skip(true);

     event.StopPropagation();

     this->key_events_ctrl.Undo_Redo_Actions(this->Book_Manager->Get_Selected_Text_Ctrl(),event);

     this->key_events_ctrl.Tab_Indentation(this->Book_Manager->Get_Selected_Text_Ctrl(),event);
}

void MainFrame::Auto_Indentation(wxStyledTextEvent & event){

     event.Skip(true);

     event.StopPropagation();

     this->key_events_ctrl.Auto_Indentation(event,this->Book_Manager->Get_Selected_Text_Ctrl());
}
