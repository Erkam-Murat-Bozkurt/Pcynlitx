

TEST_DIRECTORY=~/PCYNLITX.PROJECT/PROJECT.TEST.TOOLS/PRIME_NUMBER_SELECTION_PCYNLITX/Test.Binaries

if [ ! -e "$TEST_DIRECTORY" ]
then
  mkdir $TEST_DIRECTORY
fi

bash pcynlitx_prime_number_selection_test_builder.sh
