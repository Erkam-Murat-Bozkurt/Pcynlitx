
BASE_DIRECTORY=~/PCYNLITX_TLV_ENCODER_TEST
APP_SPEC_LIBRARY_HEADERS=$BASE_DIRECTORY/Thread_Server_Include_Directory
PROJECT_HEADERS=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY
TEST_DIRECTORY=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_PCYNLITX/Test.Binaries


Pcynlitx_Kernel ~/PCYNLITX_TLV_ENCODER_TEST/Project_Descriptor_File

printf "\n   #\e[1;34m The App-Specific library has been constructed  .. \e[0m\n\n"


g++ -I$BASE_DIRECTORY -I$APP_SPEC_LIBRARY_HEADERS -I$PROJECT_HEADERS \
    -L$BASE_DIRECTORY -L$PROJECT_LIBRARY \
    -o pcynlitx_tlv_encoder_tn4 pcynlitx_tlv_encoder_tn4.cpp \
     tlv_encoder.cpp data_extracter.cpp jsonreader.cpp string_reader.cpp \
    -include tlv_encoder.h -include jsonreader.h -include data_extracter.h -include string_reader.h \
    -include MT_Library_Headers.h -include TM_Client.h -include Thread_Manager.h \
    -include Thread_Server.h -include itds.h -include Thread_Locker.h \
    -include Cpp_FileOperations.h -include IntToCharTranslater.h \
    -lThread_Server -lmptools -lpthread

printf "\n   #\e[1;34m The binar file has been constructed  .. \e[0m\n\n"

mv pcynlitx_tlv_encoder_tn4 $TEST_DIRECTORY
