
cd ~/PCYNLITX.PROJECT

bash ReFactorProjectLibrary.sh

cd ~/PCYNLITX.SETUP.FILES

if [ ! -e "Project_Setup_Files.tar.gz" ]
then
  sudo rm -r Pcynlitx_Setup_Files.tar.gz
fi

if [ ! -e "Project_Setup_Files" ]
then
  sudo rm -r Pcynlitx_Setup_Files

  mkdir Pcynlitx_Setup_Files
fi

printf "\n   #\e[1;34m Project GUI compiling process has been started .. \e[0m\n\n"

cd ~/PCYNLITX.PROJECT/GUI.DEVELOPMENT

bash Run_Project_Binary_Files_Compiler.sh

bash Run_Project_File_Updater.sh

bash Run_GUI_Compiler.sh

printf "\n   #\e[1;34m Project GUI compiling process has been complated .. \e[0m\n\n"

cd ~/PCYNLITX.SETUP.FILES

tar -zcvf Pcynlitx_Setup_Files.tar.gz Pcynlitx_Setup_Files
