

TEST_DIRECTORY=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_C++_STD_THREAD/Test.Binaries

if [ ! -e "$TEST_DIRECTORY" ]
then
  mkdir $TEST_DIRECTORY
fi

bash std_thread_tlv_encoder_builder.sh
bash std_thread_tlv_encoder_test_builder.sh
