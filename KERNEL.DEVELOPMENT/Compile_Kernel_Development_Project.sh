
Process_Supervisor_Factory_Data_Collector_PATH=~/PCYNLITX.PROJECT/KERNEL.DEVELOPMENT/Process_Supervisor_Factory_Data_Collector

Process_Supervisor_Factory_PATH=~/PCYNLITX.PROJECT/KERNEL.DEVELOPMENT/Process_Supervisor_Factory

printf "\n KERNEL DEVELOPMENT PROJECT COMPILE PROCESS HAS BEEN STARTED \n\n"


cd $Process_Supervisor_Factory_Data_Collector_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Process_Supervisor_Factory_Data_Collector class has been compiled \n\n"


cd $Process_Supervisor_Factory_PATH

make -f auto_make_file.make

bash Modification_Control_Script.sh

printf "   # Process_Supervisor_Factory class has been compiled \n\n"

printf "   # Sub-Project has been compiled \n\n"
