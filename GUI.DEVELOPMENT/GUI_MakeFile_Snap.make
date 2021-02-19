
include INCLUDE_PATHS_FOR_GUI_MAKE_FILE

wxWidgets_Include_Directories=$(shell echo `wx-config --cxxflags`)
wxWidgets_Libraries=$(shell echo `wx-config --libs std stc core base aui`)
Project_Library=-lmptools

Pcynlitx : wxLauncher_snap.cpp MainFrame_Snap.o Process_Execution_Controller_Snap.o keyboard_event_controler.o \
							Custom_Notebook.o Custom_TabArt_Snap.o Custom_Tree_View_Panel.o Custom_Close_Button_Snap.o \
							wx_Description_Record_Tools.o \
							Menu_Bar_Options.o ToolBar_Initializer_Snap.o Project_File_Selection_Dialog.o \
	            Project_Folder_Lister.o Style_Loader.o ClassSyntaxControl.o ClassNameReader.o \
							Intro_Page_Loader_Snap.o Help_Page_Loader.o Custom_TextCtrl.o Custom_Window_Snap.o Custom_wxPanel.o  \
							Custom_wxTreeCtrl.o MainFrame_Snap.h Event_ID_Numbers.h  \
	            Process_Execution_Controller_Snap.h keyboard_event_controler.h  \
	            Custom_Tree_View_Panel.h Custom_Close_Button_Snap.h Intro_Page_Loader_Snap.h Help_Page_Loader.h Custom_TextCtrl.h \
							wx_Description_Record_Tools.h Menu_Bar_Options.h ToolBar_Initializer_Snap.h \
							Project_File_Selection_Dialog.h Custom_Notebook.h Custom_TabArt_Snap.h \
							Project_Folder_Lister.h Style_Loader.h Custom_DockArt.h \
              Custom_wxPanel.h Custom_wxTreeCtrl.h Custom_Window_Snap.h
	g++ -std=c++14 -o Pcynlitx $(wxWidgets_Include_Directories) -I$(ID) \
	     -L$(LD) wxLauncher_snap.cpp $(OD)/MainFrame_Snap.o $(OD)/Process_Execution_Controller_Snap.o \
			   $(OD)/Custom_Tree_View_Panel.o $(OD)/Custom_Close_Button_Snap.o \
				 $(OD)/Style_Loader.o $(OD)/wx_Description_Record_Tools.o \
			   $(OD)/keyboard_event_controler.o $(OD)/Custom_Notebook.o $(OD)/Custom_TabArt_Snap.o $(OD)/Menu_Bar_Options.o \
			   $(OD)/ToolBar_Initializer_Snap.o $(OD)/Project_File_Selection_Dialog.o \
				 $(OD)/Project_Folder_Lister.o $(OD)/Intro_Page_Loader_Snap.o $(OD)/Help_Page_Loader.o $(OD)/Custom_TextCtrl.o \
				 $(OD)/Custom_Window_Snap.o $(OD)/Custom_wxPanel.o $(OD)/Custom_wxTreeCtrl.o  \
 			   -include MainFrame_Snap.h -include Process_Execution_Controller_Snap.h  \
       -include keyboard_event_controler.h -include Custom_Notebook.h \
			 -include Custom_Tree_View_Panel.h -include Custom_Close_Button_Snap.h \
			 -include Style_Loader.h -include wx_Description_Record_Tools.h \
	     -include Menu_Bar_Options.h -include ToolBar_Initializer_Snap.h \
	     -include Project_File_Selection_Dialog.h -include Project_Folder_Lister.h \
	     -include Custom_TabArt_Snap.h -include Custom_TextCtrl.h -include Custom_DockArt.h  \
			 -include Intro_Page_Loader_Snap.h -include Help_Page_Loader.h -include Custom_Window_Snap.h -include Custom_wxPanel.h \
			 -include Event_ID_Numbers.h -include Custom_wxTreeCtrl.h \
			  $(wxWidgets_Libraries) $(Project_Library)
