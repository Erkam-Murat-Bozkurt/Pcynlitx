
g++ -std=c++14 -o std_thread_producer_consumer -I/home/erkam/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES \
-L/home/erkam/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY \
Producer_Consumer_Std_Thread.cpp Data_Receiver.cpp Producer_Consumer_Std_Thread.h -include Data_Receiver.h \
-include acess_sequence_data_types.h \
-lmptools -lpthread
