
TEST_DIRECTORY=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/TLV_ENCODER_PCYNLITX/Test.Binaries

if [ ! -e "$TEST_DIRECTORY" ]
then
  mkdir $TEST_DIRECTORY
fi

bash pcynlitx_tlv_test_builder.sh
