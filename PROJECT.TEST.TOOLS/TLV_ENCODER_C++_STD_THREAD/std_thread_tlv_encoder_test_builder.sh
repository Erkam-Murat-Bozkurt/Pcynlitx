

PROJECT_HEADER_FILES=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY_DIRECTORY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY
TEST_DIR=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_C++_STD_THREAD/Test.Binaries

g++ -std=c++14 -o std_thread_tlv_encoder_test  -I$PROJECT_HEADER_FILES \
    -L$PROJECT_LIBRARY_DIRECTORY std_thread_tlv_encoder_test.cpp -include Cpp_FileOperations.h -lmptools

mv std_thread_tlv_encoder_test $TEST_DIR
