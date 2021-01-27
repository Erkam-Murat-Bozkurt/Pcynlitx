
BASE_DIRECTORY=~/PCYNLITX.PROJECT/PROJECT.MANAGEMENT.TOOLS/Convert_Repo_To_Single_File
HEADER_FILES_DIRECTORY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.HEADER.FILES
LIBRARY_DIRECTORY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY
OBJECT_FILES_DIRECTORY=~/PCYNLITX.PROJECT.LIBRARY/PROJECT.LIBRARY/OBJECT.FILES


make -f Convert_Repo_To_Source.make > Compiler_Output

sudo mv Convert_Repo_To_Source /usr/bin


printf "\n\n  Convert_Repo_To_Source is ready :-)"

printf "\n\n  The Executing command: \"sudo cp Convert_Repo_To_Source /usr/bin\""

printf "\n\n"
