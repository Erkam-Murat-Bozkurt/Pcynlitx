INCLUDE_DIRECTORY=/home/erkam/parsec_fluidanimate_pcynlitx/Thread_Server_Include_Directory
BASE_DIRECTORY=/home/erkam/parsec_fluidanimate_pcynlitx

g++ -std=c++14 -I$INCLUDE_DIRECTORY -I$BASE_DIRECTORY -L/$BASE_DIRECTORY -o fluidanimate_pcynlitx cellpool.cpp cellpool.hpp fluid.hpp \
       fluidview.hpp parsec_barrier.cpp parsec_barrier.hpp main.cpp $BASE_DIRECTORY/data_holder.cpp \
      -include $BASE_DIRECTORY/data_holder.h -include $INCLUDE_DIRECTORY/MT_Library_Headers.h \
      -include $INCLUDE_DIRECTORY/Thread_Server.h -include $INCLUDE_DIRECTORY/itds.h \
     	-include $INCLUDE_DIRECTORY/TM_Client.h -include $INCLUDE_DIRECTORY/Thread_Manager.h \
     	-include $INCLUDE_DIRECTORY/Thread_Locker.h -include $INCLUDE_DIRECTORY/data_holder_Client.h \
     	-lThread_Server -lpthread -lglut
