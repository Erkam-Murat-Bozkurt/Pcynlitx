
BASE_DIRECTORY=~/RODINIA_LUD_PCYNLITX
APP_SPEC_LIBRARY_HEADERS=$BASE_DIRECTORY/Thread_Server_Include_Directory
PROJECT_HEADERS=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY

g++ -I$BASE_DIRECTORY -I$APP_SPEC_LIBRARY_HEADERS -I$PROJECT_HEADERS \
    -L$BASE_DIRECTORY -L$PROJECT_LIBRARY \
    -o Input_File_Generator Input_File_Generator.cpp -include CFileOperations.h -lmptools
