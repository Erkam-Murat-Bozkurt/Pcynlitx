
printf "\n   #\e[1;34m Project install files will be updated .. \e[0m\n\n"

DESKTOP_FILE_LOCATION=~/PCYNLITX.PROJECT/PACKAGE.BUILD.TOOLS/Ubuntu_Packaging/usr/share/Pcynlitx/applications
INTRO_FILE_LOCATION=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Intro_Page_Loader/Intro_Page_Design
PNG_ICONS_LOCATION=~/PCYNLITX.PROJECT/GUI.DEVELOPMENT/Icon_Designs/Png_Files

sudo cp $INTRO_FILE_LOCATION/Intro_File.png /snap/pcynlitx/x1/usr/share/Pcynlitx

cd $PNG_ICONS_LOCATION

sudo cp folder.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp file.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp file_save.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp build_executable.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp empty_project_file.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp select_project_file.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp help_documents.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp open_terminal.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp close.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp close_tab.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp pane_close_icon.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp open_tree_view.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp archive.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp print_descriptions.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons

sudo cp pcynlitx.png /snap/pcynlitx/x1/usr/share/Pcynlitx/icons


sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/folder.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/file.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/file_save.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/build_executable.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/empty_project_file.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/select_project_file.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/help_documents.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/open_terminal.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/close.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/open_tree_view.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/archive.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/print_descriptions.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/icons/pcynlitx.png

sudo chmod 0777 /snap/pcynlitx/x1/usr/share/Pcynlitx/Intro_File.png

printf "\n   #\e[1;34m Pcynlitx install files has been updated .. \e[0m\n\n"
