
printf "\n   #\e[1;34m Project install files will be updated .. \e[0m\n\n"

cd ~/PCYNLITX.SETUP.FILES/Project_Files

cp pcynlitx.desktop ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

cp Intro_File ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

cp gpl_3_0.pdf ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

cp GUI_Tutorial.pdf ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

cp Therms_of_use.pdf ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

cp Technical_Introduction.pdf ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

cp README.txt ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files



sudo cp gpl_3_0.pdf /usr/share/Pcynlitx

sudo cp GUI_Tutorial.pdf /usr/share/Pcynlitx

sudo cp Technical_Introduction.pdf /usr/share/Pcynlitx

sudo cp Intro_File /usr/share/Pcynlitx

sudo cp Therms_of_use.pdf /usr/share/Pcynlitx

sudo cp pcynlitx.desktop /usr/share/applications


cd ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files/PNG_ICONS

sudo cp folder.png /usr/share/Pcynlitx/icons

sudo cp file.png /usr/share/Pcynlitx/icons

sudo cp file_save.png /usr/share/Pcynlitx/icons

sudo cp build_executable.png /usr/share/Pcynlitx/icons

sudo cp empty_project_file.png /usr/share/Pcynlitx/icons

sudo cp select_project_file.png /usr/share/Pcynlitx/icons

sudo cp help_documents.png /usr/share/Pcynlitx/icons

sudo cp open_terminal.png /usr/share/Pcynlitx/icons

sudo cp close.png /usr/share/Pcynlitx/icons

sudo cp open_tree_view.png /usr/share/Pcynlitx/icons

sudo cp archive.png /usr/share/Pcynlitx/icons

sudo cp print_descriptions.png /usr/share/Pcynlitx/icons

sudo cp pcynlitx.png /usr/share/Pcynlitx/icons


sudo chmod 0777 /usr/share/Pcynlitx/icons/folder.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/file.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/file_save.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/build_executable.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/empty_project_file.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/select_project_file.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/help_documents.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/open_terminal.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/close.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/open_tree_view.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/archive.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/print_descriptions.png

sudo chmod 0777 /usr/share/Pcynlitx/icons/pcynlitx.png

printf "\n   #\e[1;34m Pcynlitx install files has been updated .. \e[0m\n\n"
