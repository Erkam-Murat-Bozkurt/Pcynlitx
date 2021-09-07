

PROJECT_HEADERS=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
PROJECT_LIBRARY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY
BASE_DIR=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_C++_STD_THREAD
TEST_DIR=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_C++_STD_THREAD/Test.Binaries
TEST_PROGRAMS=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_C++_STD_THREAD/Test.Programs

g++ -o parallel_tlv_encoder -I$PROJECT_HEADERS -I$BASE_DIR -L$PROJECT_LIBRARY \
  $BASE_DIR/parallel_tlv_encoder.cpp $BASE_DIR/tlv_encoder.cpp $BASE_DIR/jsonreader.cpp \
  $BASE_DIR/string_reader.cpp $BASE_DIR/data_extracter.cpp \
  -include tlv_encoder.h -include jsonreader.h -include string_reader.h \
  -include data_extracter.h -include StringOperator.h -include CharOperator.h \
  -include Cpp_FileOperations.h -include IntToCharTranslater.h -lpthread -lmptools

mv parallel_tlv_encoder $TEST_DIR
