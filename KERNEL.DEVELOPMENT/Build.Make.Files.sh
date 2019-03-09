

Process_Supervisor_Factory_Data_Collector_PATH=~/PCYNLITX.PROJECT/KERNEL.DEVELOPMENT/Process_Supervisor_Factory_Data_Collector

Process_Supervisor_Factory_PATH=~/PCYNLITX.PROJECT/KERNEL.DEVELOPMENT/Process_Supervisor_Factory

printf "\n \e[3;37;42m KERNEL DEVELOPMENT PROJECT MAKE FILE CONSTRUCTION HAS BEEN STARTED \e[0m \n\n"

cd $Process_Supervisor_Factory_Data_Collector_PATH

Setup_Project

printf "   #\e[3;36m A make file has been derived for Process_Supervisor_Factory_Data_Collector class .. \e[0m\n\n"

cd $Process_Supervisor_Factory_PATH

Setup_Project

printf "   #\e[3;36m A make file has been derived for Process_Supervisor_Factory class .. \e[0m\n\n"

printf "   # \e[1;7;36m The make files for the Sub-Project has been derived .. \e[0m\n\n"
