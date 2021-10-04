

APP_SPEC_DIRECTORY=~/PRIME_NUMBER_SELECTION_TEST
APP_SPEC_LIBRARY_HEADERS=$APP_SPEC_DIRECTORY/Thread_Server_Include_Directory
PROJECT_HEADERS=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY
BASE_DIRECTORY=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/PRIME_NUMBER_SELECTION_PCYNLITX
TEST_DIRECTORY=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/PRIME_NUMBER_SELECTION_PCYNLITX/Test.Binaries


Pcynlitx_Kernel ~/PRIME_NUMBER_SELECTION_TEST/Project_Descriptor_File

printf "\n   #\e[1;34m The App-Specific library has been constructed  .. \e[0m\n\n"

g++ -I$BASE_DIRECTORY -I$APP_SPEC_DIRECTORY -I$APP_SPEC_LIBRARY_HEADERS -I$PROJECT_HEADERS \
    -L$APP_SPEC_DIRECTORY -L$PROJECT_LIBRARY -L$BASE_DIRECTORY \
    -o prime_num_selection_pcynlitx_th64 $BASE_DIRECTORY/prime_num_selection_pcynlitx_th64.cpp \
    -include MT_Library_Headers.h -include TM_Client.h -include Thread_Manager.h \
    -include Thread_Server.h -include itds.h -include Thread_Locker.h \
    -include Cpp_FileOperations.h -include IntToCharTranslater.h \
    -lThread_Server -lmptools -lpthread

printf "\n   #\e[1;34m The binar file has been constructed  .. \e[0m\n\n"

mv prime_num_selection_pcynlitx_th64 $TEST_DIRECTORY
