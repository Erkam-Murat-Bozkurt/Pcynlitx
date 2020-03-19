
g++ -std=c++14 -o std_thread_number_counter -I/home/erkam/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES \
-L/home/erkam/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY \
Multithreaded_Number_Counter_Std_Thread.cpp Data_Reader.cpp -include Data_Reader.h \
-include Cpp_FileOperations.h -include StringOperator.h -lmptools -lpthread
