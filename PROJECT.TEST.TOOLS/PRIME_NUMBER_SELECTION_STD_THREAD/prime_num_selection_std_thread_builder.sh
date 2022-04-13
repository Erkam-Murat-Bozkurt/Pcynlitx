

PROJECT_HEADERS=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY
BASE_DIR=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/PRIME_NUMBER_SELECTION_STD_THREAD
TEST_DIRECTORY=$BASE_DIR/Test.Binaries


g++ -o prime_num_selection_std_thread -I$PROJECT_HEADERS -I$BASE_DIR -L$PROJECT_LIBRARY \
  $BASE_DIR/prime_num_selection_std_thread.cpp -include IntToCharTranslater.h -lpthread -lmptools

mv prime_num_selection_std_thread $TEST_DIRECTORY