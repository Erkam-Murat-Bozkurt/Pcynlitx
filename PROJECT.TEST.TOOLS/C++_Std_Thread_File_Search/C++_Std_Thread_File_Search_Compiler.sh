
g++ -std=c++14 -o C++_Std_Thread_File_Search -I/home/erkam/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES \
-L/home/erkam/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY \
C++_Std_Thread_File_Search.cpp C++_Std_Thread_File_Search.h -include StringOperator.h -include Cpp_FileOperations.h \
-include CFileOperations.h -lmptools -lpthread
