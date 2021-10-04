
TEST_DIRECTORY=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/PRIME_NUMBER_SELECTION_STD_THREAD/Test.Binaries

if [ ! -e "$TEST_DIRECTORY" ]
then
  mkdir $TEST_DIRECTORY
fi

bash prime_num_selection_std_thread_test_builder.sh

bash prime_num_selection_std_thread_builder.sh
