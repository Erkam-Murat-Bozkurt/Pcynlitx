
PROJECT_HEADER_FILES=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY_DIRECTORY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY
TEST_DIRECTORY=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/PRIME_NUMBER_SELECTION_STD_THREAD/Test.Binaries

g++ -o prime_number_selection_std_thread_test -I$PROJECT_HEADER_FILES \
    -L$PROJECT_LIBRARY_DIRECTORY prime_num_selection_std_thread_test.cpp \
    -include Cpp_FileOperations.h -lmptools

mv prime_number_selection_std_thread_test $TEST_DIRECTORY