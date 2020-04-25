
BASE_DIRECTORY=~/PARSEC_STREAMCLUSTER_PCYNLITX
INCLUDE_DIRECTORY=~/PARSEC_STREAMCLUSTER_PCYNLITX/Thread_Server_Include_Directory
PCYNLITX_PROJECT_HEADERS=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PCYNLITX_LIBRARY_DIRECTORY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY

g++ -I$BASE_DIRECTORY -I$INCLUDE_DIRECTORY -I$PCYNLITX_PROJECT_HEADERS \
    -L$BASE_DIRECTORY -L$PCYNLITX_LIBRARY_DIRECTORY -o parsec_streamcluster_pcynlitx_tn64 \
     parsec_streamcluster_pcynlitx_tn64.cpp \
     address_holder.cpp -include address_holder.h  -include thread_argument.h \
    -include $PCYNLITX_PROJECT_HEADERS/Cpp_FileOperations.h \
    -include $PCYNLITX_PROJECT_HEADERS/IntToCharTranslater.h \
    -include $INCLUDE_DIRECTORY/MT_Library_Headers.h \
    -include $INCLUDE_DIRECTORY/Thread_Server.h \
    -include $INCLUDE_DIRECTORY/itds.h -include $INCLUDE_DIRECTORY/TM_Client.h \
    -include $INCLUDE_DIRECTORY/Thread_Manager.h -include $INCLUDE_DIRECTORY/Thread_Locker.h \
    -lThread_Server -lpthread -lmptools