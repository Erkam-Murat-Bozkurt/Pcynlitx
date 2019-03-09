
include INCLUDE_PATHS_FOR_GUI_MAKE_FILE

wxWidgets_Include_Directories=$(shell echo `wx-config --cxxflags`)
wxWidgets_Libraries=$(shell echo `wx-config --libs std stc core base aui`)
Project_Library=-lmptools

Pcynlitx : wxLauncher.cpp MainFrame.o Process_Execution_Controller.o keyboard_event_controler.o \
							NoteBook_Manager.o Directory_List_Manager.o wx_Description_Record_Tools.o \
							Menu_Bar_Options.o ToolBar_Initializer.o Project_File_Selection_Dialog.o \
	            Project_Folder_Lister.o Style_Loader.o ClassSyntaxControl.o ClassNameReader.o \
							MainFrame.h Event_ID_Numbers.h Process_Execution_Controller.h keyboard_event_controler.h \
	            NoteBook_Manager.h Directory_List_Manager.h wx_Description_Record_Tools.h Menu_Bar_Options.h \
	            ToolBar_Initializer.h Project_File_Selection_Dialog.h Project_Folder_Lister.h Style_Loader.h \
              Custom_DockArt.h
	g++ -std=c++14 -o Pcynlitx $(wxWidgets_Include_Directories) -I$(ID) \
	     -L$(LD) wxLauncher.cpp $(OD)/MainFrame.o $(OD)/Process_Execution_Controller.o \
			   $(OD)/Directory_List_Manager.o $(OD)/Style_Loader.o $(OD)/wx_Description_Record_Tools.o \
			   $(OD)/keyboard_event_controler.o $(OD)/NoteBook_Manager.o $(OD)/Menu_Bar_Options.o \
			   $(OD)/ToolBar_Initializer.o $(OD)/Project_File_Selection_Dialog.o $(OD)/Project_Folder_Lister.o \
 			 -include MainFrame.h -include Process_Execution_Controller.h -include keyboard_event_controler.h \
       -include NoteBook_Manager.h -include Directory_List_Manager.h -include Style_Loader.h \
	     -include wx_Description_Record_Tools.h -include Menu_Bar_Options.h \
	     -include ToolBar_Initializer.h -include Project_File_Selection_Dialog.h -include Project_Folder_Lister.h \
	     -include Custom_DockArt.h -include Event_ID_Numbers.h $(wxWidgets_Libraries) $(Project_Library)
