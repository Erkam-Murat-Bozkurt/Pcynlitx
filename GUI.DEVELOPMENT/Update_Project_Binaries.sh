
printf "\n   #\e[1;34m Project binary files will be updated .. \e[0m\n\n"

cd ~/PCYNLITX.PROJECT/EXECUTABLE.FILE.BUILDER/MT_Project_Builder

make -f auto_make_file.make

cd ~/PCYNLITX.PROJECT/DESCRIPTOR.FILE.READER/Process_Supervisor_Descriptor_File_Reader

make -f auto_make_file.make

cd ~/PCYNLITX.PROJECT/DESCRIPTOR.FILE.WRITER/Empty_Process_Descriptor_File_Builder

make -f auto_make_file.make

cd ~/PCYNLITX.PROJECT/DESCRIPTOR.FILE.WRITER/Process_Descriptions_Recorder

make -f auto_make_file.make

cd ~/PCYNLITX.PROJECT/KERNEL.DEVELOPMENT/Process_Supervisor_Factory

make -f auto_make_file.make

cd ~/PCYNLITX.PROJECT/DESCRIPTOR.FILE.WRITER/Description_Printer

make -f auto_make_file.make

Library_Updater

cd ~/PCYNLITX.PROJECT/EXECUTABLE.FILE.BUILDER/MT_Project_Builder

Exe_Builder

sudo mv MT_Project_Builder.exe MT_Project_Builder

sudo cp MT_Project_Builder ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

sudo mv MT_Project_Builder /usr/bin

printf "   #\e[3;36m MT_Project_Builder binary has been updated .. \e[0m\n\n"

cd ~/PCYNLITX.PROJECT/DESCRIPTOR.FILE.READER/Process_Supervisor_Descriptor_File_Reader

Exe_Builder

sudo mv Process_Supervisor_Descriptor_File_Reader.exe Process_Supervisor_Descriptor_File_Reader

sudo cp Process_Supervisor_Descriptor_File_Reader ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

sudo mv Process_Supervisor_Descriptor_File_Reader /usr/bin

printf "   #\e[3;36m Process_Descriptor_File_Reader binary has been updated .. \e[0m\n\n"

cd ~/PCYNLITX.PROJECT/DESCRIPTOR.FILE.WRITER/Empty_Process_Descriptor_File_Builder

Exe_Builder

sudo mv Empty_Process_Descriptor_File_Builder.exe Empty_Process_Descriptor_File_Builder

sudo cp Empty_Process_Descriptor_File_Builder ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

sudo mv Empty_Process_Descriptor_File_Builder /usr/bin

printf "   #\e[3;36m Empty_Process_Descriptor_File_Builder binary has been updated .. \e[0m\n\n"

cd ~/PCYNLITX.PROJECT/DESCRIPTOR.FILE.WRITER/Process_Descriptions_Recorder

Exe_Builder

sudo mv Process_Descriptions_Recorder.exe Description_Recorder

sudo cp Description_Recorder ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

sudo mv Description_Recorder /usr/bin

printf "   #\e[3;36m Description_Recorder binary has been updated .. \e[0m\n\n"

cd ~/PCYNLITX.PROJECT/KERNEL.DEVELOPMENT/Process_Supervisor_Factory

Exe_Builder

sudo mv Process_Supervisor_Factory.exe Process_Supervisor_Factory

sudo cp Process_Supervisor_Factory ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

sudo mv Process_Supervisor_Factory /usr/bin

printf "   #\e[3;36m Process_Supervisor_Factory binary has been updated .. \e[0m\n\n"

cd ~/PCYNLITX.PROJECT/DESCRIPTOR.FILE.WRITER/Description_Printer

Exe_Builder

sudo mv Description_Printer.exe Description_Printer

sudo cp Description_Printer ~/PCYNLITX.SETUP.FILES/Pcynlitx_Setup_Files

sudo mv Description_Printer /usr/bin

printf "   #\e[3;36m Description_Printer binary has been updated .. \e[0m\n\n"

printf "\n   #\e[1;34m Project binary files has been updated .. \e[0m\n\n"
