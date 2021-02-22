

DEBIAN_RELEASE_BIN_DIR=~/PCYNLITX.PROJECT.LIBRARY/PCYNLITX_RELEASE_PACKAGES/DEBIAN_RELEASE/pcynlitx_debian/usr/bin

UBUNTU_RELEASE_BIN_DIR=~/PCYNLITX.PROJECT.LIBRARY/PCYNLITX_RELEASE_PACKAGES/UBUNTU_RELEASE/pcynlitx_ubuntu/usr/bin

FEDORA_RELEASE_BIN_DIR=~/PCYNLITX.PROJECT.LIBRARY/PCYNLITX_RELEASE_PACKAGES/FEDORA_RELEASE/pcynlitx_fedora/usr/bin

GUI_DEVELOPMENT_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT

GUI_Headers_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/GUI.Headers/

Intro_Page_Loader_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Intro_Page_Loader_Snap

Help_Page_Loader_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Help_Page_Loader

Custom_Tree_View_Panel_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_Tree_View_Panel_Snap

Custom_wxPanel_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_wxPanel_Snap

Custom_wxTreeCtrl_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_wxTreeCtrl

Custom_Close_Button_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_Close_Button_Snap

Custom_Window_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_Window_Snap

Project_Folder_Lister_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Project_Folder_Lister

Project_File_Selection_Dialog_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Project_File_Selection_Dialog

ToolBar_Initializer_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/ToolBar_Initializer_Snap

Menu_Bar_Options_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Menu_Bar_Options

Style_Loader_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Style_Loader

Custom_TabArt_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_TabArt_Snap

Custom_Notebook_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_Notebook_Snap

Custom_TextCtrl_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_TextCtrl

wx_Description_Record_Tools_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/wx_Description_Record_Tools_Snap

keyboard_event_controler_snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/keyboard_event_controler_snap

Process_Execution_Controller_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Process_Execution_Controller_Snap

MainFrame_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/MainFrame_Snap

Custom_DockArt=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/GUI.Headers/Custom_DockArt.h

Event_ID_Numbers=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/GUI.Headers/Event_ID_Numbers.h

Event_Table_Header_Snap=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/GUI.Headers/Event_Table_Header_Snap.h


printf "\n GUI COMPILE PROCESS HAS BEEN STARTED \n\n"

sudo cp $Custom_DockArt ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES

sudo cp $Event_ID_Numbers ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES

sudo cp $Event_Table_Header_Snap ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES

cd $Intro_Page_Loader_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Intro_Page_Loader class has been compiled \n\n"


cd $Help_Page_Loader_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Help_Page_Loader class has been compiled \n\n"


cd $Custom_wxTreeCtrl_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Custom_wxTreeCtrl class has been compiled \n\n"


cd $Project_Folder_Lister_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Project_Folder_Lister class has been compiled \n\n"


cd $Custom_Window_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Custom_Window class has been compiled \n\n"



cd $Custom_Close_Button_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Custom_Close_Button class has been compiled \n\n"


cd $Custom_Tree_View_Panel_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Custom_Tree_View_Panel class has been compiled \n\n"


cd $Custom_wxPanel_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Custom_wxPanel_Snap class has been compiled \n\n"



cd $Project_File_Selection_Dialog_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Project_File_Selection_Dialog class has been compiled \n\n"


cd $ToolBar_Initializer_Snap_PATH

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

cd $Custom_TextCtrl_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Custom_TextCtrl class has been compiled \n\n"


cd $Custom_TabArt_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Custom_TextCtrl class has been compiled \n\n"


cd $Custom_Notebook_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Custom_NoteBook_Snap class has been compiled \n\n"


cd $wx_Description_Record_Tools_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # wx_Description_Record_Tools class has been compiled \n\n"


cd $keyboard_event_controler_snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # keyboard_event_controler_snap class has been compiled \n\n"


cd $Process_Execution_Controller_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Process_Execution_Controller class has been compiled \n\n"


cd $MainFrame_Snap_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # MainFrame class has been compiled \n\n"

Library_Updater

printf "   # PROJECT library libmptoos.a has been updated \n\n"

cd $GUI_DEVELOPMENT_PATH

make -f GUI_MakeFile_Snap.make

cp Pcynlitx $DEBIAN_RELEASE_BIN_DIR

cp Pcynlitx $UBUNTU_RELEASE_BIN_DIR

cp Pcynlitx $FEDORA_RELEASE_BIN_DIR
