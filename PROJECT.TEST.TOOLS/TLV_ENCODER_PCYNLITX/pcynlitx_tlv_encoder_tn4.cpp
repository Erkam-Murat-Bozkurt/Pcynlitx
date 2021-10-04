
 #include "MT_Library_Headers.h"
 #include <iostream>
 #include <string>
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <unistd.h>
 #include <thread>
 #include <iostream>
 #include <sstream>
 #include <cstring>
 #include "tlv_encoder.h"
 #include "jsonreader.h"
 #include "string_reader.h"


 std::string output_data_stream = "";

 tlv_encoder * encoder;

 jsonreader * reader;

 int Elapsed_Time_for_user = 0;

 int Elapsed_Time_for_sys = 0;

 int Elapsed_Time_for_total = 0;

 int num_threads = 0;


 //void data_encoder(int thread_number);

 int main(int argc, char ** argv){

     if(argc < 2){

        std::cout << "\n\n usage: " << argv[0]

                  << " <data file path>";

        std::cout << "\n\n";

        exit(0);
     }

     num_threads = 4;



     encoder = new tlv_encoder [2*num_threads];

     reader  = new jsonreader;

     reader->receive_thread_number(num_threads);

     reader->collect_json_data(argv[1]);


     struct rusage usage;

     struct timeval start_us, end_us, start_sys, end_sys;


     int return_value = getrusage(RUSAGE_SELF,&usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }

     start_us = usage.ru_utime;

     start_sys = usage.ru_stime;



     pcynlitx::Thread_Server Server;

     for(int i=0;i<num_threads;i++){

         Server.Activate(i,data_encoder);
     }

     for(int i=0;i<num_threads;i++){

         Server.Join(i);
     };


     return_value = getrusage(RUSAGE_SELF, &usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }


     end_us = usage.ru_utime;

     end_sys = usage.ru_stime;

     Elapsed_Time_for_user = end_us.tv_sec - start_us.tv_sec;

     Elapsed_Time_for_sys = end_sys.tv_sec - start_sys.tv_sec;


     Elapsed_Time_for_total = Elapsed_Time_for_user + Elapsed_Time_for_sys;

     std::cout << Elapsed_Time_for_total << std::endl;


     delete [] encoder;

     delete reader;


     return 0;
 }


 void data_encoder(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"data_encoder");

      Manager.lock();

      int thread_number = Manager.Get_Thread_Number();

      Manager.unlock();


      // STARTING OF THE PARALLEL EXECUTION REGION

      encoder[thread_number].receive_data_length(reader->get_thread_data_length(thread_number));

      encoder[thread_number].receive_dictionary_data(reader->getThreadDictionary(thread_number));

      std::string thread_data_stream = encoder[thread_number].construct_data_stream();

      // THE END OF THE PARALLEL EXECUTION


      Manager.start_serial(0,num_threads,thread_number);

      output_data_stream = output_data_stream + thread_data_stream;

      Manager.end_serial(0,num_threads,thread_number);

      Manager.Exit();
 }
