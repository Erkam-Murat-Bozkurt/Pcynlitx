
Intro_Page_Loader_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Intro_Page_Loader

Project_Folder_Lister_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Project_Folder_Lister

Project_File_Selection_Dialog_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Project_File_Selection_Dialog

ToolBar_Initializer_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/ToolBar_Initializer

Menu_Bar_Options_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Menu_Bar_Options

Style_Loader_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Style_Loader

Directory_List_Manager_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Directory_List_Manager

NoteBook_Manager_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/NoteBook_Manager

wx_Description_Record_Tools_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/wx_Description_Record_Tools

keyboard_event_controler_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/keyboard_event_controler

Process_Execution_Controller_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Process_Execution_Controller

MainFrame_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/MainFrame

printf "\n \e[3;37;42m GUI.DEVELOPMENT MAKE FILE CONTRUCTION STARTED \e[0m \n\n"

cd $Intro_Page_Loader_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Intro_Page_Loader class .. \e[0m\n\n"

cd $Project_Folder_Lister_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Project_Folder_Lister class .. \e[0m\n\n"

cd $Project_File_Selection_Dialog_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Project_File_Selection_Dialog class .. \e[0m\n\n"

cd $ToolBar_Initializer_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for ToolBar_Initializer class \e[0m\n\n"

cd $Menu_Bar_Options_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Menu_Bar_Options class .. \e[0m\n\n"

cd $Style_Loader_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Style_Loader class .. \e[0m\n\n"

cd $Directory_List_Manager_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Directory_List_Manager class .. \e[0m\n\n"

cd $NoteBook_Manager_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for NoteBook_Manager .. \e[0m\n\n"

cd $wx_Description_Record_Tools_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for wx_Description_Record_Tools class .. \e[0m\n\n"

cd $keyboard_event_controler_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for keyboard_event_controler class .. \e[0m\n\n"

cd $Process_Execution_Controller_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Process_Execution_Controller class .. \e[0m\n\n"

cd $MainFrame_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for keyboard_event_controler class .. \e[0m\n\n"

cd ~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/GUI.Headers

Custom_DockArt_Path=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES/Custom_DockArt.h
Event_ID_Numbers_Path=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES/Event_ID_Numbers.h
Event_Table_Header_Path=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES/Event_Table_Header.h
wxDirTraverser_executer_Path=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES/wxDirTraverser_executer.h

if [ ! -e "$Custom_DockArt_Path" ]
then
  cp Custom_DockArt.h ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
fi

if [ ! -e "$Event_ID_Numbers_Path" ]
then
  cp Event_ID_Numbers.h ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
fi

if [ ! -e "$Event_Table_Headers_Path" ]
then
  cp Event_Table_Header.h ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
fi

if [ ! -e "$wxDirTraverser_executer_Path" ]
then
  cp wxDirTraverser_executer.h ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
fi

printf "   # \e[1;7;36m GUI header Files has been copied to the Headers Location  .. \e[0m\n\n"


printf "   # \e[1;7;36m The make files for the Sub-Project has been derived .. \e[0m\n\n"
