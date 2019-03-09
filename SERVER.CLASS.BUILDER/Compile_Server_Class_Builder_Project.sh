
Inter_Thread_Data_Structure_Builder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/Inter_Thread_Data_Structure_Builder

Thread_Locker_Header_File_Builder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/Thread_Locker_Header_File_Builder

Thread_Locker_Builder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/Thread_Locker_Builder

ThreadSynchronization_HeaderFileBuilder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/ThreadSynchronization_HeaderFileBuilder

ThreadSynchronization_Builder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/ThreadSynchronization_Builder

Synchronizer_Client_Header_Builder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/Synchronizer_Client_Header_Builder

Synchronizer_Client_Builder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/Synchronizer_Client_Builder

Process_Supervisor_Header_File_Builder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/Process_Supervisor_Header_File_Builder

Process_Supervisor_Builder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/Process_Supervisor_Builder

Main_File_Builder_PATH=~/PCYNLITX.PROJECT/SERVER.CLASS.BUILDER/Main_File_Builder

printf "\n  SERVER CLASS BUILDER PROJECT COMPILE PROCESS HAS BEEN STARTED  \n\n"

cd $Inter_Thread_Data_Structure_Builder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Inter_Thread_Data_Structure_Builder class has been compiled \n\n"


cd $Thread_Locker_Header_File_Builder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Thread_Locker_Header_File_Builder class has been compiled \n\n"


cd $Thread_Locker_Builder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Thread_Locker_Builder class has been compiled \n\n"


cd $ThreadSynchronization_HeaderFileBuilder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # ThreadSynchronization_HeaderFileBuilder class has been compiled \n\n"



cd $ThreadSynchronization_Builder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # ThreadSynchronization_Builder class has been compiled \n\n"


cd $Synchronizer_Client_Header_Builder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Synchronizer_Client_Header_Builder class has been compiled \n\n"


cd $Synchronizer_Client_Builder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Synchronizer_Client_Builder class has been compiled \n\n"


cd $Process_Supervisor_Header_File_Builder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Process_Supervisor_Header_File_Builder class has been compiled \n\n"


cd $Process_Supervisor_Builder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Process_Supervisor_Builder class has been compiled \n\n"


cd $Main_File_Builder_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Main_File_Builder class has been compiled \n\n"


printf "   # Sub-Project has been compiled \n\n"
