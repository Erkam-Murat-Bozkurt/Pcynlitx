


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


 int Elapsed_Time = 0;

 int num_threads = 0;


 void data_encoder(int thread_number);

 int main(int argc, char ** argv){

     if(argc < 2){

        std::cout << "\n\n usage: " << argv[0]

                  << " <data file path>";

        std::cout << "\n\n";

        exit(0);
     }

     num_threads = 256;


     encoder = new tlv_encoder [2*num_threads];

     reader  = new jsonreader [2*num_threads];

     // THE CONSTRUCTION OF ARTIFICIAL WORKLOAD


     std::thread threads[num_threads];

     struct rusage usage;

     struct timeval start, end;

     for(int i=0;i<num_threads;i++){

         reader[i].collect_json_data(argv[1]);
     }


     int return_value = getrusage(RUSAGE_SELF,&usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }

     start = usage.ru_utime;


     pcynlitx::Thread_Server Server;

     for(int i=0;i<256;i++){

         Server.Activate(i,data_encoder);
     }

     for(int i=0;i<256;i++){

         Server.Join(i);
     };


     return_value = getrusage(RUSAGE_SELF, &usage);

     if(return_value!= 0){

        std::cout << "\n The usage data can not be obtain..\n";

        return 0;
     }

     end = usage.ru_utime;

     Elapsed_Time = end.tv_sec - start.tv_sec;

     std::cout << Elapsed_Time << std::endl;

     return 0;
 }


 void data_encoder(pcynlitx::thds * thread_data){

      pcynlitx::TM_Client Manager(thread_data,"data_encoder");

      Manager.lock();

      int thread_number = Manager.Get_Thread_Number();

      Manager.unlock();


      // STARTING OF THE PARALLEL EXECUTION REGION

      encoder[thread_number].receive_data_length(reader[thread_number].getDataLength());

      encoder[thread_number].receive_dictionary_data(reader[thread_number].getDictionary());

      // THE END OF THE PARALLEL EXECUTION


      Manager.start_serial(0,256,thread_number);

      output_data_stream = output_data_stream

                          + encoder[thread_number].construct_data_stream();

      Manager.end_serial(0,256,thread_number);

      Manager.Exit();
 }
