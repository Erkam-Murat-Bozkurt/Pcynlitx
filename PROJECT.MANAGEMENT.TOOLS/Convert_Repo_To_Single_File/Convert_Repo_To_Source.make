
DIR_OPS=/home/erkam/PCYNLITX.PROJECT/CLASS.DECLERATION.READER/Tools/DirectoryOperations
CPP_OPS=/home/erkam/PCYNLITX.PROJECT/CLASS.DECLERATION.READER/Tools/Cpp_FileOperations
CHAR_OPS=/home/erkam/PCYNLITX.PROJECT/CLASS.DECLERATION.READER/Tools/CharOperator
DOC_OPS=/home/erkam/PCYNLITX.PROJECT/CLASS.DECLERATION.READER/Tools/Document_Builder

VPATH = $(DIR_OPS) $(CPP_OPS) $(CHAR_OPS) $(DOC_OPS)

Convert_Repo_To_Source: Convert_Repo_To_Single_File_Main_File.cpp Convert_Repo_To_Single_File.cpp \
	Document_Builder.cpp DirectoryOperations.cpp CharOperator.cpp Cpp_FileOperations.cpp \
	Convert_Repo_To_Single_File.h DirectoryOperations.h CharOperator.h Cpp_FileOperations.h\

	g++ -std=c++17 -o Convert_Repo_To_Source -I$(DIR_OPS) -I$(CPP_OPS) -I$(DOC_OPS) -I$(CHAR_OPS) \
	 -L$(DOC_OPS) -L$(DIR_OPS) -L$(CPP_OPS) -L$(CHAR_OPS) \
		Convert_Repo_To_Single_File_Main_File.cpp Convert_Repo_To_Single_File.cpp \
		$(DOC_OPS)/Document_Builder.cpp $(DIR_OPS)/DirectoryOperations.cpp \
		$(CHAR_OPS)/CharOperator.cpp $(CPP_OPS)/Cpp_FileOperations.cpp \
		-include Convert_Repo_To_Single_File.h \
		-include $(DOC_OPS)/Document_Builder.h -include $(DIR_OPS)/DirectoryOperations.h \
		-include $(CHAR_OPS)/CharOperator.h \
		-include $(CPP_OPS)/Cpp_FileOperations.h
