

add_library(gui_tools 

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Close_Button/Custom_Close_Button.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Close_Button/Custom_Close_Button.h



    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Notebook/Custom_Notebook.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Notebook/Custom_Notebook.h



    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TabArt/Custom_TabArt.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TabArt/Custom_TabArt.h    


    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TextCtrl/Custom_TextCtrl.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TextCtrl/Custom_TextCtrl.h  



    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Tree_View_Panel/Custom_Tree_View_Panel.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Tree_View_Panel/Custom_Tree_View_Panel.h  



    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Window/Custom_Window.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Window/Custom_Window.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxPanel/Custom_wxPanel.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxPanel/Custom_wxPanel.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxTreeCtrl/Custom_wxTreeCtrl.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxTreeCtrl/Custom_wxTreeCtrl.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers/Custom_DockArt.h

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers/Event_ID_Numbers.h

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers/Event_Table_Header.h

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers/wxDirTraverser_executer.h



    ${CMAKE_CURRENT_SOURCE_DIR}/Help_Page_Loader/Help_Page_Loader.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Help_Page_Loader/Help_Page_Loader.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/Intro_Page_Loader/Intro_Page_Loader.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Intro_Page_Loader/Intro_Page_Loader.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_event_controler/keyboard_event_controler.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_event_controler/keyboard_event_controler.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/MainFrame/MainFrame.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/MainFrame/MainFrame.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/Menu_Bar_Options/Menu_Bar_Options.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Menu_Bar_Options/Menu_Bar_Options.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/Process_Execution_Controller/Process_Execution_Controller.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Process_Execution_Controller/Process_Execution_Controller.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/Project_File_Selection_Dialog/Project_File_Selection_Dialog.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_File_Selection_Dialog/Project_File_Selection_Dialog.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Folder_Lister/Project_Folder_Lister.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Folder_Lister/Project_Folder_Lister.h  

        
    ${CMAKE_CURRENT_SOURCE_DIR}/Style_Loader/Style_Loader.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Style_Loader/Style_Loader.h  


    ${CMAKE_CURRENT_SOURCE_DIR}/ToolBar_Initializer/ToolBar_Initializer.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/ToolBar_Initializer/ToolBar_Initializer.h  

    
    ${CMAKE_CURRENT_SOURCE_DIR}/wx_Description_Record_Tools/wx_Description_Record_Tools.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/wx_Description_Record_Tools/wx_Description_Record_Tools.h  

)



target_include_directories(gui_tools PUBLIC


    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Close_Button

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Notebook

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TabArt

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_TextCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Tree_View_Panel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_Window

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxPanel

    ${CMAKE_CURRENT_SOURCE_DIR}/Custom_wxTreeCtrl

    ${CMAKE_CURRENT_SOURCE_DIR}/GUI.Headers

    ${CMAKE_CURRENT_SOURCE_DIR}/Help_Page_Loader
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Intro_Page_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/keyboard_event_controler

    ${CMAKE_CURRENT_SOURCE_DIR}/MainFrame
    
    ${CMAKE_CURRENT_SOURCE_DIR}/Menu_Bar_Options

    ${CMAKE_CURRENT_SOURCE_DIR}/Process_Execution_Controller

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_File_Selection_Dialog

    ${CMAKE_CURRENT_SOURCE_DIR}/Project_Folder_Lister
        
    ${CMAKE_CURRENT_SOURCE_DIR}/Style_Loader

    ${CMAKE_CURRENT_SOURCE_DIR}/ToolBar_Initializer

    ${CMAKE_CURRENT_SOURCE_DIR}/wx_Description_Record_Tools




    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/CharOperator

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/Compiler

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/Compiler_Descriptor_File_Reader

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/HeaderFileBuilder

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/StringOperator


    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/ClassNameReader

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/ClassSyntaxControl

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/FindSetPoints 

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/ListFileOrganizer

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/MethodInitializer

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/MethodProcessor    

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/MethodReader    

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/SyntaxController

    /home/ubuntu/wxWidgets-3.2.4/lib/wx/include/gtk3-unicode-3.2

    /home/ubuntu/wxWidgets-3.2.4/include

)


add_executable(pcynlitx ${CMAKE_CURRENT_SOURCE_DIR}/wxLauncher.cpp)

target_link_libraries(pcynlitx PUBLIC  gui_tools des_reader class_reader proc_init tools)


target_compile_options(gui_tools PUBLIC -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXGTK__)





target_link_directories(gui_tools PUBLIC 


    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Descriptor_File_Data_Collector    

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Descriptor_File_Number_Processor

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Descriptor_File_Reader    

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Descriptor_File_Reader_Initializer

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Descriptor_File_Reader_Syntax_Controller

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Header_File_Descriptions_Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Include_Directory_Description_Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Inter_Thread_Class_Description_Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Inter_Thread_Data_Type_Description_Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Library_Descriptions_Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Main_File_Descriptions_Reader

    ${CMAKE_SOURCE_DIR}/DESCRIPTOR.FILE.READER/Source_File_Descriptions_Reader  


    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/DataBaseManagement/MemberFunctionReader

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/DataBaseManagement/MetaDataTranslater


    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ClassReader/DataBaseBuilder

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ClassReader/MethodInterpreter

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ClassReader/MethodListInterpreter

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ClassReader/MethodListReader

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ClassReader/MethodReceiver

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ClassReader/NameReader

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ClassReader/ParameterReader

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ClassReader/ParenthesReader

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ClassReader/ReturnTypeReader   

    

    ${CMAKE_SOURCE_DIR}/PROJECT.MANAGEMENT.TOOLS/Auto_Class_Compiler

    ${CMAKE_SOURCE_DIR}/PROJECT.MANAGEMENT.TOOLS/Convert_Repo_To_Single_File

    ${CMAKE_SOURCE_DIR}/PROJECT.MANAGEMENT.TOOLS/Included_Header_File_Names_Reader

    ${CMAKE_SOURCE_DIR}/PROJECT.MANAGEMENT.TOOLS/Library_Updater

    ${CMAKE_SOURCE_DIR}/PROJECT.MANAGEMENT.TOOLS/Make_File_Builder

    ${CMAKE_SOURCE_DIR}/PROJECT.MANAGEMENT.TOOLS/Test_Program_Builder


    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/Cpp_FileOperations

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/CharOperator

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/Compiler

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/Compiler_Descriptor_File_Reader

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/Custom_System_Interface

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/DirectoryOperations

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/HeaderFileBuilder

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/IntToCharTranslater

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/Tools/StringOperator


    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/ClassNameReader

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/ClassSyntaxControl

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/FindSetPoints 

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/ListFileOrganizer

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/MethodInitializer

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/MethodProcessor    

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/MethodReader    

    ${CMAKE_SOURCE_DIR}/CLASS.DECLERATION.READER/ProcessInitialization/SyntaxController

    /home/ubuntu/wxWidgets-3.2.4/lib

    /home/ubuntu/wxWidgets-3.2.4/lib/x86_64-linux-gnu 
)



target_link_libraries(pcynlitx PUBLIC gui_tools pthread 

    wx_gtk3u_core-3.2.so.0.2.2      wx_gtk3u_richtext-3.2.so.0.2.2
    wx_baseu-3.2.so                 wx_gtk3u_gl-3.2.so              wx_gtk3u_stc-3.2.so
    wx_baseu-3.2.so.0               wx_gtk3u_gl-3.2.so.0            wx_gtk3u_stc-3.2.so.0
    wx_baseu-3.2.so.0.2.2           wx_gtk3u_gl-3.2.so.0.2.2        wx_gtk3u_stc-3.2.so.0.2.2
    wx_baseu_net-3.2.so             wx_gtk3u_html-3.2.so            wx_gtk3u_xrc-3.2.so
    wx_baseu_net-3.2.so.0           wx_gtk3u_html-3.2.so.0          wx_gtk3u_xrc-3.2.so.0
    wx_baseu_net-3.2.so.0.2.2       wx_gtk3u_html-3.2.so.0.2.2      wx_gtk3u_xrc-3.2.so.0.2.2
    wx_baseu_xml-3.2.so             wx_gtk3u_propgrid-3.2.so        wxscintilla-3.2.a
    wx_baseu_xml-3.2.so.0           wx_gtk3u_propgrid-3.2.so.0      
    wx_baseu_xml-3.2.so.0.2.2       wx_gtk3u_propgrid-3.2.so.0.2.2  
    wx_gtk3u_adv-3.2.so             wx_gtk3u_qa-3.2.so              
    wx_gtk3u_adv-3.2.so.0           wx_gtk3u_qa-3.2.so.0           
    wx_gtk3u_adv-3.2.so.0.2.2       wx_gtk3u_qa-3.2.so.0.2.2       
    wx_gtk3u_aui-3.2.so             wx_gtk3u_ribbon-3.2.so         
    wx_gtk3u_aui-3.2.so.0           wx_gtk3u_ribbon-3.2.so.0        
    wx_gtk3u_aui-3.2.so.0.2.2       wx_gtk3u_ribbon-3.2.so.0.2.2    
    wx_gtk3u_core-3.2.so            wx_gtk3u_richtext-3.2.so
    wx_gtk3u_core-3.2.so.0          wx_gtk3u_richtext-3.2.so.0
)