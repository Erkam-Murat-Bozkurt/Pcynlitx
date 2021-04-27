
Custom_Close_Button_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_Close_Button_Snap

Custom_Window_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_Window_Snap

Custom_wxPanel_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_wxPanel_Snap

Custom_Tree_View_Panel_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_Tree_View_Panel_Snap

Intro_Page_Loader_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Intro_Page_Loader_Snap

ToolBar_Initializer_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/ToolBar_Initializer_Snap

Menu_Bar_Options_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Menu_Bar_Options_Snap

Custom_TabArt_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_TabArt_Snap

Custom_Notebook_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Custom_Notebook_Snap

keyboard_event_controler_snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/keyboard_event_controler_snap

Process_Execution_Controller_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Process_Execution_Controller_Snap

wx_Description_Record_Tools_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/wx_Description_Record_Tools_Snap

MainFrame_Snap_PATH=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/MainFrame_Snap


cd $Custom_Close_Button_Snap_PATH

Setup_GUI_Project

printf "\n"

printf "   #\e[3;36m A make file has been derived for Custom_Close_Button_Snap class .. \e[0m\n\n"

cd $Custom_Window_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Custom_Window_Snap class .. \e[0m\n\n"


cd $Custom_wxPanel_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Custom_wxPanel_Snap class .. \e[0m\n\n"


cd $Custom_Tree_View_Panel_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Custom_Tree_View_Panel_Snap class .. \e[0m\n\n"

cd $Intro_Page_Loader_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Intro_Page_Loader_Snap class .. \e[0m\n\n"

cd $ToolBar_Initializer_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for ToolBar_Initializer_Snap class \e[0m\n\n"

cd $Menu_Bar_Options_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Menu_Bar_Options_Snap class .. \e[0m\n\n"

cd $Custom_TabArt_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Custom_TabArt_Snap .. \e[0m\n\n"

cd $Custom_Notebook_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Custom_Notebook_Snap .. \e[0m\n\n"


cd $keyboard_event_controler_snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for keyboard_event_controler_snap .. \e[0m\n\n"


cd $Process_Execution_Controller_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for Process_Execution_Controller class .. \e[0m\n\n"


cd $wx_Description_Record_Tools_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for wx_Description_Record_Tools_Snap class .. \e[0m\n\n"


cd $MainFrame_Snap_PATH

Setup_GUI_Project

printf "   #\e[3;36m A make file has been derived for MainFrame_Snap class .. \e[0m\n\n"

cd ~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/GUI.Headers

Custom_DockArt_Path=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES/Custom_DockArt.h
Event_ID_Numbers_Path=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES/Event_ID_Numbers.h
Event_Table_Header_Path=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES/Event_Table_Header.h
Event_Table_Header_Snap_Path=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES/Event_Table_Header_Snap.h
wxDirTraverser_executer_Path=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES/wxDirTraverser_executer.h

if [ ! -e "$Custom_DockArt_Path" ]
then
  cp Custom_DockArt.h ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
fi

if [ ! -e "$Event_ID_Numbers_Path" ]
then
  cp Event_ID_Numbers.h ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
fi

if [ ! -e "$Event_Table_Header_Path" ]
then
  cp Event_Table_Header.h ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
fi

if [ ! -e "$Event_Table_Header_Snap_Path" ]
then
  cp Event_Table_Header_Snap.h ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
fi


if [ ! -e "$wxDirTraverser_executer_Path" ]
then
  cp wxDirTraverser_executer.h ~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
fi

printf "   # \e[1;7;36m GUI header Files has been copied to the Headers Location  .. \e[0m\n\n"


printf "   # \e[1;7;36m The make files for the Sub-Project has been derived .. \e[0m\n\n"
