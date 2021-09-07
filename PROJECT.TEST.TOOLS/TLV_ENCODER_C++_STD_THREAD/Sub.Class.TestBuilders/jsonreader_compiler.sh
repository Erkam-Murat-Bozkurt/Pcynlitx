

PROJECT_HEADERS=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY
BASE_DIR=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_C++_STD_THREAD
TEST_DIR=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_C++_STD_THREAD/Test.Binaries
TEST_PROGRAMS=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_C++_STD_THREAD/Sub.Class.TestPrograms

g++ -o jsonreader_test -I$PROJECT_HEADERS -I$BASE_DIR -L$PROJECT_LIBRARY $TEST_PROGRAMS/jsonreader_test.cpp \
  $BASE_DIR/jsonreader.cpp $BASE_DIR/string_reader.cpp $BASE_DIR/data_extracter.cpp \
  -include jsonreader.h -include string_reader.h -include data_extracter.h \
  -include StringOperator.h -include CharOperator.h -include Cpp_FileOperations.h \
  -lmptools

mv jsonreader_test $TEST_DIR
