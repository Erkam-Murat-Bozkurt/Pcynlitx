
GUI_DEVELOPMENT_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT

GUI_Headers_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/GUI.Headers/

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


printf "\n GUI COMPILE PROCESS HAS BEEN STARTED \n\n"

cd $Intro_Page_Loader_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Intro_Page_Loader class has been compiled \n\n"

cd $Project_Folder_Lister_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Project_Folder_Lister class has been compiled \n\n"


cd $Project_File_Selection_Dialog_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Project_File_Selection_Dialog class has been compiled \n\n"


cd $ToolBar_Initializer_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # ToolBar_Initializer class has been compiled \n\n"



cd $Menu_Bar_Options_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Menu_Bar_Options class has been compiled \n\n"


cd $Style_Loader_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Style_Loader class has been compiled \n\n"


cd $Directory_List_Manager_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Directory_List_Manager class has been compiled \n\n"


cd $NoteBook_Manager_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # NoteBook_Manager class has been compiled \n\n"


cd $wx_Description_Record_Tools_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # wx_Description_Record_Tools class has been compiled \n\n"


cd $keyboard_event_controler_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # keyboard_event_controler class has been compiled \n\n"


cd $Process_Execution_Controller_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Process_Execution_Controller class has been compiled \n\n"


cd $MainFrame_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # MainFrame class has been compiled \n\n"

Library_Updater

printf "   # PROJECT library libmptoos.a has been updated \n\n"

cd $GUI_DEVELOPMENT_PATH

make -f GUI_MakeFile.make

cp Pcynlitx ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

sudo mv Pcynlitx /usr/bin
